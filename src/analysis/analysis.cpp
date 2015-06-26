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

#include "analysis/analysis.h"

#include "command.h"
#include "logger.h"

#include "analysis/declaration.h"
#include "analysis/expression.h"
#include "analysis/function.h"
#include "analysis/ref.h"
#include "analysis/statement.h"
#include "analysis/walkitem.h"

#include "nodes/decl/function_decl.h"
#include "nodes/decl/var_decl.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/bind_expr.h"
#include "nodes/expr/compound_expr.h"
#include "nodes/expr/call_expr.h"
#include "nodes/expr/cleanuppoint_expr.h"
#include "nodes/expr/cond_expr.h"
#include "nodes/expr/decl_expr.h"
#include "nodes/expr/eq_expr.h"
#include "nodes/expr/init_expr.h"
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/ne_expr.h"
#include "nodes/expr/nonlvalue_expr.h"
#include "nodes/expr/nop_expr.h"
#include "nodes/expr/pointerplus_expr.h"
#include "nodes/expr/return_expr.h"
#include "nodes/expr/truthand_expr.h"
#include "nodes/expr/truthandif_expr.h"
#include "nodes/expr/truthor_expr.h"
#include "nodes/expr/truthorif_expr.h"

#include "nodes/ref/component_ref.h"

#include "nodes/stmt/if_stmt.h"

#include "localconsts.h"

namespace Analysis
{

// remove check null vars.
void removeCheckNullVars(WalkItem &wi)
{
    removeCheckNullVarsSet(wi, wi.removeNullVars);
}

void addCheckNullVars(WalkItem &wi, WalkItem &wo)
{
    FOR_EACH (std::set<std::string>::const_iterator, it, wi.addNullVars)
    {
        wo.checkNullVars.insert(*it);
    }
}

void removeCheckNullVar(WalkItem &wi, std::string str)
{
    // found var for deletion
    if (wi.checkNullVars.find(str) != wi.checkNullVars.end())
    {
        wi.checkNullVars.erase(str);
    }
    if (wi.addNullVars.find(str) != wi.addNullVars.end())
    {
        wi.addNullVars.erase(str);
    }
    StringMapSet::const_iterator it2 = wi.linkedVars.find(str);
    if (it2 != wi.linkedVars.end())
    {
        const StringSet &linked = (*it2).second;
        FOR_EACH (StringSet::const_iterator, it3, linked)
        {
            if (wi.checkNullVars.find(*it3) != wi.checkNullVars.end())
            {
                wi.checkNullVars.erase(*it3);
            }
            if (wi.addNullVars.find(*it3) != wi.addNullVars.end())
            {
                wi.addNullVars.erase(*it3);
            }
        }
        //wi.linkedVars.erase(str);
    }
}

void removeCheckNullVarsSet(WalkItem &wi, std::set<std::string> &vars)
{
    FOR_EACH (std::set<std::string>::const_iterator, it, vars)
    {
        // remove var if need
        removeCheckNullVar(wi, *it);
        // if need remove some linked var, search it parent,
        // and remove all linked vars for this parent
        StringMap::const_iterator it3 = wi.linkedReverseVars.find(*it);
        if (it3 != wi.linkedReverseVars.end())
        {
            const std::string parent = (*it3).second;
            //wi.linkedVars.erase(parent);
            removeCheckNullVar(wi, parent);
        }
    }
}

void addLinkedVar(WalkItem &wi,
                  const std::string &parent,
                  const std::string &var)
{
    if (wi.linkedVars.find(parent) == wi.linkedVars.end())
        wi.linkedVars[parent] = std::set<std::string>();
    wi.linkedVars[parent].insert(var);
    wi.linkedReverseVars[var] = parent;
}

void startWalkTree(Node *node)
{
    WalkItem wi;
    WalkItem wo;
    walkTree(node, wi, wo);
}

void walkTree(Node *node, const WalkItem &wi, WalkItem &wo)
{
    if (!node)
        return;

    node = skipNop(node);

    WalkItem wi2 = wi;
    analyseNode(node, wi2, wo);
    removeCheckNullVars(wi2);
    addCheckNullVars(wo, wo);
    addCheckNullVars(wo, wi2);
    addCheckNullVars(wi2, wi2);
    wi2.linkedVars = wo.linkedVars;
    wi2.linkedReverseVars = wo.linkedReverseVars;
    wi2.addNullVars = wo.addNullVars;

    const bool isReturned = wo.isReturned;
    if (wo.stopWalking)
    {
        wo.stopWalking = false;
        return;
    }

    WalkItem wo2 = wo;
    if (command != Command::DumpNullPointers)
        Log::dumpWI(node, "walkTree 2 wo2 ", wo2);

    FOR_EACH (std::vector<Node*>::iterator, it, node->childs)
    {
        walkTree(*it, wi2, wo2);
        wi2.removeNullVars = wo2.removeNullVars;
        wi2.addNullVars = wo2.addNullVars;
        addCheckNullVars(wi2, wi2);
        wo2.checkNullVars = wi2.checkNullVars;
        wi2.isReturned = wi2.isReturned || wo2.isReturned;
        wi2.linkedVars = wo2.linkedVars;
        wi2.linkedReverseVars = wo2.linkedReverseVars;
        wo2.stopWalking = false;
    }
    wo.removeNullVars = wi2.removeNullVars;
    wo.addNullVars = wi2.addNullVars;
    wo.isReturned = wo.isReturned || isReturned || wo2.isReturned;
    wo.linkedVars = wi2.linkedVars;
    wo.linkedReverseVars = wi2.linkedReverseVars;

    if (command != Command::DumpNullPointers)
        Log::dumpWI(node, "walkTree out wo ", wo);

//    Log::dumpAttr(node, 2, wo.isReturned);
}

int findBackLocation(Node *node)
{
    location_t loc = 0;
    while(node && !loc)
    {
        loc = node->location;
        node = node->parent;
    }
    return loc;
}

bool checkForReport(Node *node,
                    const WalkItem &wi)
{
    node = skipNop(node);
    return node &&
        (node == PARM_DECL || node == VAR_DECL) &&
        wi.checkNullVars.find(node->label) != wi.checkNullVars.end();
}

void reportParmDeclNullPointer(Node *mainNode,
                               Node *node,
                               const WalkItem &wi)
{
    node = skipNop(node);
    if (node)
    {
        if (!node->label.empty())
        {
            if (node == PARM_DECL)
            {
                if (wi.checkNullVars.find(node->label) != wi.checkNullVars.end())
                {
                    Log::warn(findBackLocation(mainNode),
                        "Using parameter '%s' without checking for null pointer",
                        node->label);
                }
            }
            else if (node == VAR_DECL)
            {
                if (wi.checkNullVars.find(node->label) != wi.checkNullVars.end())
                {
                    Log::warn(findBackLocation(mainNode),
                        "Using variable '%s' without checking for null pointer",
                        node->label);
                }
            }
        }
        else if (node == COMPONENT_REF)
        {
            std::string var = getComponentRefVariable(node);
            if (wi.checkNullVars.find(var) != wi.checkNullVars.end())
            {
                Log::warn(findBackLocation(mainNode),
                    "Using field '%s' without checking for null pointer",
                    var);
            }
        }
    }
}

Node *skipNop(Node *node)
{
    while (node &&
           (node == NOP_EXPR || node == NON_LVALUE_EXPR))
    {
        NopExprNode *nop = static_cast<NopExprNode*>(node);
        if (nop && !nop->args.empty())
            node = nop->args[0];
        else
            return nop;
    }
    return node;
}

Node *skipBackNop(Node *node)
{
    while (node && node == NOP_EXPR)
    {
        node = node->parent;
    }
    return node;
}

void mergeNullChecked(WalkItem &wi1, WalkItem &wi2)
{
    wi1.checkedNullVars.insert(wi2.checkedNullVars.begin(),
        wi2.checkedNullVars.end());
}

void mergeNonNullChecked(WalkItem &wi1, WalkItem &wi2)
{
    wi1.checkedNonNullVars.insert(wi2.checkedNonNullVars.begin(),
        wi2.checkedNonNullVars.end());
}

void intersectNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2)
{
    FOR_EACH (std::set<std::string>::const_iterator,
              it,
              wi1.checkedNullVars)
    {
        if (wi2.checkedNullVars.find(*it) != wi2.checkedNullVars.end())
            wi.checkedNullVars.insert(*it);
    }
}

void intersectNonNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2)
{
    FOR_EACH (std::set<std::string>::const_iterator,
              it,
              wi1.checkedNonNullVars)
    {
        if (wi2.checkedNonNullVars.find(*it) != wi2.checkedNonNullVars.end())
            wi.checkedNonNullVars.insert(*it);
    }
}

void analyseNode(Node *node, const WalkItem &wi, WalkItem &wo)
{
    if (!node)
        return;

    if (command == Command::DumpNullPointers)
    {
        Log::log("%s %s: ",
            node->nodeTypeName.c_str(),
            node->label.c_str());
        FOR_EACH (std::set<std::string>::const_iterator,
                  it,
                  wi.checkNullVars)
        {
            Log::log("%s, ", (*it).c_str());
        }
        Log::log("\n");
    }
    else
    {
        Log::dumpWI(node, "analyseNode wi in ", wi);
    }

    WalkItem wi2 = wi;
    wo = wi;

    // remove check for vars what was requested from some childs.
    // Except IF_STMT. Removing handled inside analyse function.
    if (node != IF_STMT)
    {
        removeCheckNullVars(wi2);
//        addCheckNullVars(wi2);
    }

    if (command != Command::DumpNullPointers)
        Log::dumpWI(node, "analyseNode wi2 ", wi2);

    // searching function declaration
    switch (node->nodeType)
    {
        case FUNCTION_DECL:
            analyseFunction(static_cast<FunctionDeclNode*>(node), wi2, wo);
            break;
        case ADDR_EXPR:
            analyseAddrExpr(static_cast<AddrExprNode*>(node), wi2, wo);
            break;
        case BIND_EXPR:
            analyseBindExpr(static_cast<BindExprNode*>(node), wi2, wo);
            break;
        case DECL_EXPR:
            analyseDeclExpr(static_cast<DeclExprNode*>(node), wi2, wo);
            break;
        case INIT_EXPR:
            analyseInitExpr(static_cast<InitExprNode*>(node), wi2, wo);
            break;
        case MODIFY_EXPR:
            analyseModifyExpr(static_cast<ModifyExprNode*>(node), wi2, wo);
            break;
        case NE_EXPR:
            analyseNeExpr(static_cast<NeExprNode*>(node), wi2, wo);
            break;
        case EQ_EXPR:
            analyseEqExpr(static_cast<EqExprNode*>(node), wi2, wo);
            break;
        case CALL_EXPR:
            analyseCallExpr(static_cast<CallExprNode*>(node), wi2, wo);
            break;
        case CLEANUP_POINT_EXPR:
            analyseCleanupPointExpr(static_cast<CleanupPointExprNode*>(node), wi2, wo);
            break;
        case COND_EXPR:
            analyseCondExpr(static_cast<CondExprNode*>(node), wi2, wo);
            break;
        case COMPOUND_EXPR:
            analyseCompoundExpr(static_cast<CompoundExprNode*>(node), wi2, wo);
            break;
        case NOP_EXPR:
            analyseNopExpr(static_cast<NopExprNode*>(node), wi2, wo);
            break;
        case TRUTH_ORIF_EXPR:
            analyseTruthOrIfExpr(static_cast<TruthOrIfExprNode*>(node), wi2, wo);
            break;
        case TRUTH_OR_EXPR:
            analyseTruthOrExpr(static_cast<TruthOrExprNode*>(node), wi2, wo);
            break;
        case TRUTH_ANDIF_EXPR:
            analyseTruthAndIfExpr(static_cast<TruthAndIfExprNode*>(node), wi2, wo);
            break;
        case TRUTH_AND_EXPR:
            analyseTruthAndExpr(static_cast<TruthAndExprNode*>(node), wi2, wo);
            break;
        case RETURN_EXPR:
            analyseReturnExpr(static_cast<ReturnExprNode*>(node), wi2, wo);
            break;
        case POINTER_PLUS_EXPR:
            analysePointerPlusExpr(static_cast<PointerPlusExprNode*>(node), wi2, wo);
            break;
        case NON_LVALUE_EXPR:
            analyseNonLvalueExpr(static_cast<NonLvalueExprNode*>(node), wi2, wo);
            break;
        case VAR_DECL:
            analyseVarDecl(static_cast<VarDeclNode*>(node), wi2, wo);
            break;
        case IF_STMT:
            analyseIfStmt(static_cast<IfStmtNode*>(node), wi2, wo);
            break;
        case COMPONENT_REF:
            analyseComponentRef(static_cast<ComponentRefNode*>(node), wi2, wo);
            break;
        default:
            break;
    }
    if (command != Command::DumpNullPointers)
        Log::dumpWI(node, "analyseNode out ", wo);
}

}
