/*
 *  Copyright (C) 2015  Andrei Karas
 *
 *  This file is part of AstDumper.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "analysis/expression.h"

#include "command.h"
#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/statement.h"
#include "analysis/walkitem.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/bind_expr.h"
#include "nodes/expr/call_expr.h"
#include "nodes/expr/compound_expr.h"
#include "nodes/expr/cond_expr.h"
#include "nodes/expr/decl_expr.h"
#include "nodes/expr/eq_expr.h"
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/ne_expr.h"
#include "nodes/expr/nop_expr.h"
#include "nodes/expr/pointerplus_expr.h"
#include "nodes/expr/return_expr.h"
#include "nodes/expr/truthand_expr.h"
#include "nodes/expr/truthandif_expr.h"
#include "nodes/expr/truthor_expr.h"
#include "nodes/expr/truthorif_expr.h"

#include "nodes/decl/function_decl.h"
#include "nodes/decl/var_decl.h"

#include "nodes/ref/indirect_ref.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

void analyseModifyExpr(ModifyExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need atleast one arg for check
    if (node->args.empty() || command == FindArgs)
        return;

    Node *arg = skipNop(node->args[0]);
    if (arg && arg->nodeType == INDIRECT_REF)
    {
        reportParmDeclNullPointer(node,
            static_cast<IndirectRefNode*>(arg)->ref,
            wi);
    }
}

void analysePointerPlusExpr(PointerPlusExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need atleast one arg for check
    if (node->args.empty() || command == FindArgs)
        return;

    reportParmDeclNullPointer(node, node->args[0], wi);
}

void analyseAddrExpr(AddrExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need atleast one arg for check
    if (node->args.empty() || command == FindArgs)
        return;

    // do not report code like func1(ptr) or push_back(ptr)
    Node *node2 = skipBackNop(node->parent);
    if (node2)
    {
        while (node2 && node2->nodeType == ADDR_EXPR)
        {
            node2 = skipBackNop(node2->parent);
        }
        // found what some parent is function or method call
        if (node2 && node2->nodeType == CALL_EXPR)
        {
            return;
        }
    }

    reportParmDeclNullPointer(node, node->args[0], wi);
}

void analyseReturnExpr(ReturnExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    wo.isReturned = true;
}

void analyseNeExpr(NeExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

//    Log::dumpWI(node, "NE in ", wo);
    // PARM_DECL or VAR_DECL?
    Node *node1 = skipNop(node->args[0]);
    // INTEGER_CST?
    Node *node2 = skipNop(node->args[1]);

    // if (var != 0)
    if (node1 &&
        node2 &&
        (node1->nodeType == PARM_DECL || node1->nodeType == VAR_DECL) &&
        node2->nodeType == INTEGER_CST &&
        wi.checkNullVars.find(node1->label) != wi.checkNullVars.end() &&
        node2->label == "0")
    {
        wo.checkedNonNullVars.insert(node1->label);
        wo.cleanExpr = true;
        wo.uselessExpr = false;
    }
    else
    {
        wo.cleanExpr = false;
        wo.uselessExpr = true;
    }
    Log::dumpWI(node, "NE out ", wo);
}

void analyseEqExpr(EqExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    Log::dumpWI(node, "EQ in ", wo);
    // PARM_DECL or VAR_DECL ?
    Node *node1 = skipNop(node->args[0]);
    // INTEGER_CST?
    Node *node2 = skipNop(node->args[1]);
    // if (var == 0)
    if (node1 &&
        node2 &&
        (node1->nodeType == PARM_DECL || node1->nodeType == VAR_DECL) &&
        node2->nodeType == INTEGER_CST &&
        wi.checkNullVars.find(node1->label) != wi.checkNullVars.end() &&
        node2->label == "0")
    {
        wo.checkedNullVars.insert(node1->label);
        wo.cleanExpr = true;
        wo.uselessExpr = false;
    }
    else
    {
        wo.cleanExpr = false;
        wo.uselessExpr = true;
    }
    Log::dumpWI(node, "EQ out ", wo);
}

void analyseOrCondition(Node *node, Node *node1, Node *node2, const WalkItem &wi, WalkItem &wo)
{
    Log::dumpWI(node, "wo in ", wo);
    WalkItem wo1 = wo;
    WalkItem wo2 = wo;
    walkTree(node1, wi, wo1);
    Log::dumpWI(node, "wo1 ", wo1);
    WalkItem wi2 = wi;
    removeCheckNullVarsSet(wi2, wo1.checkedNullVars);
    wi2.checkNullVars.insert(wo1.checkedNonNullVars.begin(),
        wo1.checkedNonNullVars.end());
    Log::dumpWI(node, "wi2 ", wi2);
    walkTree(node2, wi2, wo2);
    Log::dumpWI(node, "wo2 ", wo2);
    // probably condition wrong
    if (wo1.cleanExpr)
        mergeNullChecked(wo, wo1);
    // probably condition wrong
    if (wo2.cleanExpr)
        mergeNullChecked(wo, wo2);
    // need check for cleanExpr?
    intersectNonNullChecked(wo, wo1, wo2);

    wo.cleanExpr = true;
    wo.stopWalking = true;
    wo.uselessExpr = false;
    Log::dumpWI(node, "wo out ", wo);
}

void analyseAndCondition(Node *node, Node *node1, Node *node2, const WalkItem &wi, WalkItem &wo)
{
    Log::dumpWI(node, "wo in ", wo);
    WalkItem wo1 = wo;
    WalkItem wo2 = wo;
    walkTree(node1, wi, wo1);
    Log::dumpWI(node, "wo1 ", wo1);
    WalkItem wi2 = wi;
    removeCheckNullVarsSet(wi2, wo1.checkedNonNullVars);
    wi2.checkNullVars.insert(wo1.checkedNullVars.begin(),
        wo1.checkedNullVars.end());
    Log::dumpWI(node, "wi2 ", wi2);
    walkTree(node2, wi2, wo2);
    Log::dumpWI(node, "wo2 ", wo2);

    wo.stopWalking = true;
    // probably condition wrong
    if (!wo1.uselessExpr && !wo2.uselessExpr)
    {   // need combine wo1 and wo2
        intersectNullChecked(wo, wo1, wo2);
    }
    if (!wo1.uselessExpr)
    {
        mergeNonNullChecked(wo, wo1);
    }
    if (!wo2.uselessExpr)
    {
        mergeNonNullChecked(wo, wo2);
    }
    wo.cleanExpr = wo1.cleanExpr && wo2.cleanExpr;
    wo.uselessExpr = wo1.uselessExpr && wo2.uselessExpr;
    Log::dumpWI(node, "wo out ", wo);
}

void analyseTruthOrIfExpr(TruthOrIfExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    analyseOrCondition(node, node->args[0], node->args[1], wi, wo);
}

void analyseTruthOrExpr(TruthOrExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    analyseOrCondition(node, node->args[0], node->args[1], wi, wo);
}

void analyseTruthAndIfExpr(TruthAndIfExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    analyseAndCondition(node, node->args[0], node->args[1], wi, wo);
}

void analyseTruthAndExpr(TruthAndExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    analyseAndCondition(node, node->args[0], node->args[1], wi, wo);
}

// args[0]  condition
// args[1]  true expr
// args[2]  false expr
void analyseCondExpr(CondExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need tree args for check
    if (node->args.size() < 3 || command == FindArgs)
        return;

    analyseCondition(node,
        node->args[0],
        node->args[1],
        node->args[2],
        wi,
        wo);
}

// expression like this (expr1, expr2, ..., exprn). Only have sense exprn.
void analyseCompoundExpr(CompoundExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need one arg for check
    if (node->args.size() < 1 || command == FindArgs)
        return;

    Log::dumpWI(node, "wo in ", wo);

    const size_t sz = node->args.size();
    // walking and ignoring results for all args except last
    for (size_t f = 0; f < sz - 1; f ++)
    {
        WalkItem wo1 = wo;
        walkTree(node->args[f], wi, wo1);
        Log::dumpWI(node, "wo1 ", wo1);
    }
    WalkItem wo2 = wo;
    walkTree(node->args[sz - 1], wi, wo2);
    Log::dumpWI(node, "wo2 ", wo2);

    // probably condition wrong
    if (wo2.cleanExpr)
    {
        mergeNullChecked(wo, wo2);
        mergeNonNullChecked(wo, wo2);
    }

    //wo.removeNullVars.clear();

    wo.cleanExpr = true;
    wo.stopWalking = true;
    wo.uselessExpr = false;
    Log::dumpWI(node, "wo out ", wo);
}

// type var1 = var2;
void analyseBindExpr(BindExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    const size_t sz = node->args.size();
    if (sz < 1 || command == FindArgs)
        return;

    Log::dumpWI(node, "wo in ", wo);
    WalkItem wi2 = wi;
    walkTree(node->args[1], wi2, wo);
    wi2 = wo;
    Log::dumpWI(node, "wi2 ", wi2);
    walkTree(node->args[0], wi2, wo);
    if (sz > 2)
    {
        wi2 = wo;
        Log::dumpWI(node, "wi2 ", wi2);
        walkTree(node->args[2], wi2, wo);
    }

    Node *node1 = skipNop(node->args[0]);
    if (node1 &&
        node1->nodeType == VAR_DECL)
    {
        VarDeclNode *varDecl = static_cast<VarDeclNode*>(node1);
        Node *initial = skipNop(varDecl->initial);
        if (checkForReport(initial, wi))
        {
            wo.addNullVars.insert(varDecl->label);
            addLinkedVar(wo, initial->label, varDecl->label);
        }
    }
    wo.stopWalking = true;
    Log::dumpWI(node, "wo out ", wo);
}

// type var1 = var2;
void analyseDeclExpr(DeclExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need one arg for check
    if (node->args.empty() || command == FindArgs)
        return;

    Node *node1 = skipNop(node->args[0]);

    if (node1 &&
        node1->nodeType == VAR_DECL)
    {
        VarDeclNode *varDecl = static_cast<VarDeclNode*>(node1);
        Node *initial = skipNop(varDecl->initial);
        if (checkForReport(initial, wi))
        {
            wo.addNullVars.insert(varDecl->label);
            addLinkedVar(wo, initial->label, varDecl->label);
        }
    }
}

void analyseNopExpr(NopExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need one arg for check
    if (node->args.empty())
        return;

    walkTree(node->args[0], wi, wo);
    wo.stopWalking = true;
}

void analyseCallExpr(CallExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    WalkItem wo2 = wo;
    Log::dumpWI(node, "wo in ", wo);
    walkTree(node->chain, wi, wo2);
    Log::dumpWI(node, "wo chain ", wo2);
    wo2 = wo;
    bool enableCheck(true);
    if (node->function)
    {
        walkTree(node->function, wi, wo2);
        Log::dumpWI(node, "wo function ", wo2);
        if (node->function->nodeType == ADDR_EXPR)
        {
            AddrExprNode *addrNode = static_cast<AddrExprNode*>(node->function);
            if (!addrNode->args.empty())
            {
                if (addrNode->args[0]->nodeType == FUNCTION_DECL)
                {
                    FunctionDeclNode *declNode = static_cast<FunctionDeclNode*>(
                        addrNode->args[0]);
                    if (declNode->functionType &&
                        declNode->functionType->nodeType == FUNCTION_TYPE)
                    {
                        enableCheck = false;
                    }
                }
            }
        }
    }
    FOR_EACH (std::vector<Node*>::const_iterator, it, node->args)
    {
        wo2 = wo;
        Node *node2 = skipNop(*it);
        if (enableCheck)
        {
            reportParmDeclNullPointer(node, node2, wi);
            enableCheck = false;
        }
        walkTree(node2, wi, wo2);
        Log::dumpWI(node, "wo arg ", wo2);
    }
    wo.stopWalking = true;
}

}
