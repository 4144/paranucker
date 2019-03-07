/*
 *  Copyright (C) 2015  Andrei Karas
 *
 *  This file is part of Paranoid null checker.
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

#include "analysis/collections.h"
#include "analysis/cst.h"
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
#include "nodes/expr/goto_expr.h"
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

#include "nodes/ref/array_ref.h"
#include "nodes/ref/component_ref.h"

#include "nodes/stmt/break_stmt.h"
#include "nodes/stmt/continue_stmt.h"
#include "nodes/stmt/if_stmt.h"
#include "nodes/stmt/while_stmt.h"

#include "localconsts.h"

namespace Analysis
{

void startWalkTree(Node *node)
{
    WalkItem wi;
    WalkItem wo;
    walkTree(node, wi, wo);
}

// main walk tree function
void walkTree(Node *node, const WalkItem &wi, WalkItem &wo)
{
    if (!node)
        return;

    node = skipNop(node);
    if (!node)
        return;

    WalkItem wi2 = wi;
    // analyse node and after copy all properties from wo to wi2
    analyseNode(node, wi2, wo);
    addNeedCheckNullVars(wo, wo);
    addNeedCheckNullVars(wo, wi2);
    if (wo.stopWalking)
    {
        wo.stopWalking = false;
        return;
    }

    wi2 = wo;

    addNeedCheckNullVars(wi2, wi2);
    removeNeedCheckNullVarsSetAll(wi2, wi2.removeNullVarsAll);
    removeNeedCheckNullVarsSet(wi2, wi2.removeNullVars);

    const bool isReturned = wo.isReturned;
    const bool isContinued = wo.isContinued;

    WalkItem wo2 = wo;
    if (command != Command::DumpNullPointers)
        Log::dumpWI(node, "walkTree 2 wo2 ", wo2);

    // walk to all child nodes.
    // wi2 combining output from node and previous childs
    FOR_EACH (it, node->childs)
    {
        walkTree(it, wi2, wo2);
        wi2.removeNullVarsAll = wo2.removeNullVarsAll;
        wi2.removeNullVars = wo2.removeNullVars;
        wi2.addNullVars = wo2.addNullVars;
        addNeedCheckNullVars(wi2, wi2);
        wo2.needCheckNullVars = wi2.needCheckNullVars;
        wi2.knownVars = wo2.knownVars;
        wi2.knownNullVars = wo2.knownNullVars;
        wi2.knownNonNullVars = wo2.knownNonNullVars;
        wi2.isReturned = wi2.isReturned || wo2.isReturned;
        wi2.isContinued = wi2.isContinued || wo2.isContinued;
        wi2.linkedVars = wo2.linkedVars;
        wi2.linkedReverseVars = wo2.linkedReverseVars;
        wo2.stopWalking = false;
    }
    // copy properties from wi2 to wo
    wo.removeNullVarsAll = wi2.removeNullVarsAll;
    wo.removeNullVars = wi2.removeNullVars;
    wo.addNullVars = wi2.addNullVars;
    wo.isReturned = wo.isReturned || isReturned || wo2.isReturned;
    wo.isContinued = wo.isContinued || isContinued || wo2.isContinued;
    wo.linkedVars = wi2.linkedVars;
    wo.linkedReverseVars = wi2.linkedReverseVars;
    wo.knownVars = wo2.knownVars;
    wo.knownNullVars = wo2.knownNullVars;
    wo.knownNonNullVars = wo2.knownNonNullVars;

    if (command != Command::DumpNullPointers)
        Log::dumpWI(node, "walkTree out wo ", wo);
}

// search location for node or first parent
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

// skip all child nodes and return non nop child
Node *skipNop(Node *node)
{
    while (node == NOP_EXPR ||
           node == NON_LVALUE_EXPR ||
           node == CLEANUP_POINT_EXPR)
    {
        NopExprNode *nop = static_cast<NopExprNode*>(node);
        if (nop && !nop->args.empty())
            node = nop->args[0];
        else
            return nop;
    }
    return node;
}

// skip all parent nop nodes and return first non nop parent
Node *skipBackNop(Node *node)
{
    while (node == NOP_EXPR ||
           node == NON_LVALUE_EXPR ||
           node == CLEANUP_POINT_EXPR)
    {
        node = node->parent;
    }
    return node;
}

void analyseNode(Node *node, const WalkItem &wi, WalkItem &wo)
{
    if (!node)
        return;

    if (checkCommand(DumpNullPointers))
    {
        Log::log("%s %s: ",
            node->nodeTypeName.c_str(),
            node->label.c_str());
        FOR_EACH (it, wi.needCheckNullVars)
        {
            Log::log("%s, ", it.c_str());
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
    if (node != IF_STMT && node != WHILE_STMT)
    {
        removeNeedCheckNullVarsSetAll(wi2, wi2.removeNullVarsAll);
    }
    removeNeedCheckNullVarsSet(wi2, wi2.removeNullVars);

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
        case GOTO_EXPR:
            analyseGotoExpr(static_cast<GotoExprNode*>(node), wi2, wo);
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
        case BREAK_STMT:
            analyseBreakStmt(static_cast<BreakStmtNode*>(node), wi2, wo);
            break;
        case IF_STMT:
            analyseIfStmt(static_cast<IfStmtNode*>(node), wi2, wo);
            break;
        case WHILE_STMT:
            analyseWhileStmt(static_cast<WhileStmtNode*>(node), wi2, wo);
            break;
        case CONTINUE_STMT:
            analyseContinueStmt(static_cast<ContinueStmtNode*>(node), wi2, wo);
            break;
        case ARRAY_REF:
            analyseArrayRef(static_cast<ArrayRefNode*>(node), wi2, wo);
            break;
        case COMPONENT_REF:
            analyseComponentRef(static_cast<ComponentRefNode*>(node), wi2, wo);
            break;
        case INTEGER_CST:
            analyseIntegerCst(static_cast<IntegerCstNode*>(node), wi2, wo);
            break;
        default:
            break;
    }
    if (command != Command::DumpNullPointers)
        Log::dumpWI(node, "analyseNode out ", wo);
}

}
