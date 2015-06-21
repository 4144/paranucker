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
#include "analysis/walkitem.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/compound_expr.h"
#include "nodes/expr/cond_expr.h"
#include "nodes/expr/eq_expr.h"
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/ne_expr.h"
#include "nodes/expr/pointerplus_expr.h"
#include "nodes/expr/return_expr.h"
#include "nodes/expr/truthandif_expr.h"
#include "nodes/expr/truthorif_expr.h"

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
    // PARM_DECL?
    Node *node1 = skipNop(node->args[0]);
    // INTEGER_CST?
    Node *node2 = skipNop(node->args[1]);

    // if (var != 0)
    if (node1 &&
        node2 &&
        node1->nodeType == PARM_DECL &&
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
    // PARM_DECL?
    Node *node1 = skipNop(node->args[0]);
    // INTEGER_CST?
    Node *node2 = skipNop(node->args[1]);
    // if (var == 0)
    if (node1 &&
        node2 &&
        node1->nodeType == PARM_DECL &&
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

void analyseTruthOrIfExpr(TruthOrIfExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    Log::dumpWI(node, "wo in ", wo);
    WalkItem wo1 = wo;
    WalkItem wo2 = wo;
    walkTree(node->args[0], wi, wo1);
    Log::dumpWI(node, "wo1 ", wo1);
    WalkItem wi2 = wi;
    removeCheckNullVarsSet(wi2, wo1.checkedNullVars);
    wi2.checkNullVars.insert(wo1.checkedNonNullVars.begin(),
        wo1.checkedNonNullVars.end());
    Log::dumpWI(node, "wi2 ", wi2);
    walkTree(node->args[1], wi2, wo2);
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

void analyseTruthAndIfExpr(TruthAndIfExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    Log::dumpWI(node, "wo in ", wo);
    WalkItem wo1 = wo;
    WalkItem wo2 = wo;
    walkTree(node->args[0], wi, wo1);
    Log::dumpWI(node, "wo1 ", wo1);
    WalkItem wi2 = wi;
    removeCheckNullVarsSet(wi2, wo1.checkedNonNullVars);
    wi2.checkNullVars.insert(wo1.checkedNullVars.begin(),
        wo1.checkedNullVars.end());
    Log::dumpWI(node, "wi2 ", wi2);
    walkTree(node->args[1], wi2, wo2);
    Log::dumpWI(node, "wo2 ", wo2);

    wo.stopWalking = true;
    // probably condition wrong
    if (!wo1.uselessExpr && !wo2.uselessExpr)
    {   // need combine wo1 and wo2
        intersectNullChecked(wo, wo1, wo2);
        mergeNonNullChecked(wo, wo1);
        mergeNonNullChecked(wo, wo2);
    }
    wo.cleanExpr = wo1.cleanExpr && wo2.cleanExpr;
    wo.uselessExpr = wo1.uselessExpr || wo2.uselessExpr;
    Log::dumpWI(node, "wo out ", wo);
}

// args[0]  condition
// args[1]  true expr
// args[2]  false expr
void analyseCondExpr(CondExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need tree args for check
    if (node->args.size() < 3 || command == FindArgs)
        return;

    Log::dumpWI(node, "wo in ", wo);
    WalkItem wo1 = wo;
    WalkItem wo2 = wo;
    WalkItem wo3 = wo;

    // walk condition
    walkTree(node->args[0], wi, wo1);
    Log::dumpWI(node, "wo1 ", wo1);
    WalkItem wi2 = wi;
    removeCheckNullVarsSet(wi2, wo1.checkedNonNullVars);
    wi2.checkNullVars.insert(wo1.checkedNullVars.begin(),
        wo1.checkedNullVars.end());
    Log::dumpWI(node, "wi2 ", wi2);

    reportParmDeclNullPointer(node,
        node->args[1],
        wi2);
    // walk true expr
    walkTree(node->args[1], wi2, wo2);
    Log::dumpWI(node, "wo2 ", wo2);
    WalkItem wi3 = wi;
    removeCheckNullVarsSet(wi3, wo1.checkedNullVars);
    wi3.checkNullVars.insert(wo1.checkedNonNullVars.begin(),
        wo1.checkedNonNullVars.end());
    Log::dumpWI(node, "wi3 ", wi3);

    reportParmDeclNullPointer(node,
        node->args[2],
        wi3);
    // walk true expr
    walkTree(node->args[2], wi3, wo3);
    Log::dumpWI(node, "wo3 ", wo3);

    // probably condition wrong
    if (wo2.cleanExpr)
        mergeNullChecked(wo, wo2);
    // probably condition wrong
    if (wo3.cleanExpr)
        mergeNullChecked(wo, wo3);
    // need check for cleanExpr?
    intersectNonNullChecked(wo, wo2, wo3);

    //wo.removeNullVars.clear();

    if (wo2.isReturned)
    {
        // add variable for ignore for all parent nodes except special like IF_STMT
        FOR_EACH (std::set<std::string>::const_iterator,
                  it,
                  wo1.checkedNullVars)
        {
            wo.removeNullVars.insert(*it);
            wo.checkNullVars.erase(*it);
        }
    }
    if (wo3.isReturned)
    {
        // add variable for ignore for all parent nodes except special like IF_STMT
        FOR_EACH (std::set<std::string>::const_iterator,
                  it,
                  wo1.checkedNonNullVars)
        {
            wo.removeNullVars.insert(*it);
            wo.checkNullVars.erase(*it);
        }
    }

    if (wo2.isReturned && wo3.isReturned)
    {
        // add variable for ignore for all parent nodes except special like IF_STMT
        FOR_EACH (std::set<std::string>::const_iterator,
                  it,
                  wo.checkNullVars)
        {
            wo.removeNullVars.insert(*it);
        }
    }

    wo.isReturned = false;
    wo.cleanExpr = true;
    wo.stopWalking = true;
    wo.uselessExpr = false;
    Log::dumpWI(node, "wo out ", wo);
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

}
