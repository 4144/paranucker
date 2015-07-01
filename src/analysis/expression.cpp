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

#include "analysis/expression.h"

#include "command.h"
#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/function.h"
#include "analysis/statement.h"
#include "analysis/walkitem.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/bind_expr.h"
#include "nodes/expr/call_expr.h"
#include "nodes/expr/cleanuppoint_expr.h"
#include "nodes/expr/compound_expr.h"
#include "nodes/expr/cond_expr.h"
#include "nodes/expr/convert_expr.h"
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

#include "nodes/decl/function_decl.h"
#include "nodes/decl/var_decl.h"

#include "nodes/ref/array_ref.h"
#include "nodes/ref/component_ref.h"
#include "nodes/ref/indirect_ref.h"
#include "nodes/ref/objtype_ref.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

// return variable name if possible or empty string
std::string getVariableName(Node *node)
{
    if (!node)
        return "";

    node = skipNop(node);
    if (!node)
        return "";

    if (node == PARM_DECL || node == VAR_DECL)
        return node->label;
    else if (node == COMPONENT_REF)
        return getComponentRefVariable(node);
    return "";
}

// return variable name in format object->field for component node
std::string getComponentRefVariable(Node *node)
{
    std::string str;
    ComponentRefNode *const comp = static_cast<ComponentRefNode*>(skipNop(node));
    if (comp &&
        comp->object &&
        comp->field)
    {
        Node *object = skipNop(comp->object);
        Node *field = skipNop(comp->field);
        if (object == INDIRECT_REF &&
            field == FIELD_DECL)
        {
            IndirectRefNode *indirect = static_cast<IndirectRefNode*>(object);
            Node *ref = skipNop(indirect->ref);
            if (ref == PARM_DECL || ref == VAR_DECL)
            {
                str.append(ref->label).append("->").append(field->label);
            }
        }
    }
    return str;
}

void analyseModifyExpr(ModifyExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need atleast one arg for check
    if (node->args.empty() || checkCommand(FindArgs))
        return;

    Node *arg = skipNop(node->args[0]);
    if (arg)
    {
        std::string var1 = getVariableName(arg);
        std::string var2 = getVariableName(node->args[1]);

        if (arg == INDIRECT_REF)
        {
            // var2 not found in known checking pointer
            if (wi.needCheckNullVars.find(var2) == wi.needCheckNullVars.end() &&
                wi.knownVars.find(var2) == wi.knownVars.end())
            {
                wo.removeNullVars.insert(var1);
            }

            reportParmDeclNullPointer(node,
                static_cast<IndirectRefNode*>(arg)->ref,
                wi);
        }
        else if (!var1.empty() && !var2.empty())
        {
            if (wi.needCheckNullVars.find(var2) != wi.needCheckNullVars.end())
            {
                addNullVar(wo, var1);
                addLinkedVar(wo, var2, var1);
            }
            // var2 not found in known checking pointer
            else if (wi.needCheckNullVars.find(var2) == wi.needCheckNullVars.end() &&
                     wi.knownVars.find(var2) == wi.knownVars.end())
            {
                wo.removeNullVars.insert(var1);
            }
        }
    }
}

void analysePointerPlusExpr(PointerPlusExprNode *node,
                            const WalkItem &wi,
                            WalkItem &wo A_UNUSED)
{
    // need atleast one arg for check
    if (node->args.empty() || checkCommand(FindArgs))
        return;

    reportParmDeclNullPointer(node, node->args[0], wi);
}

void analyseAddrExpr(AddrExprNode *node,
                     const WalkItem &wi,
                     WalkItem &wo A_UNUSED)
{
    // need atleast one arg for check
    if (node->args.empty() || checkCommand(FindArgs))
        return;

    // do not report code like func1(ptr) or push_back(ptr)
    Node *node2 = skipBackNop(node->parent);
    if (node2)
    {
        while (node2 == ADDR_EXPR)
        {
            node2 = skipBackNop(node2->parent);
        }
        // found what some parent is function or method call
        if (node2 == CALL_EXPR)
        {
            return;
        }
    }

    reportParmDeclNullPointer(node, node->args[0], wi);
}

void analyseReturnExpr(ReturnExprNode *node A_UNUSED,
                       const WalkItem &wi A_UNUSED,
                       WalkItem &wo)
{
    wo.isReturned = true;
}

void analyseNeExpr(NeExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || checkCommand(FindArgs))
        return;

    // PARM_DECL or VAR_DECL?
    Node *node1 = skipNop(node->args[0]);
    // INTEGER_CST?
    Node *node2 = skipNop(node->args[1]);

    std::string var = getVariableName(node1);
    // if (var != 0)
    if (!var.empty() &&
        node2 == INTEGER_CST &&
        node2->label == "0")
    {
        if (wi.needCheckNullVars.find(var) != wi.needCheckNullVars.end())
        {
            wo.checkedNonNullVars.insert(var);
            wo.knownNonNullVars.insert(var);
            wo.cleanExpr = true;
            wo.uselessExpr = false;
            return;
        }
        else if (wi.knownNonNullVars.find(var) != wi.knownNonNullVars.end())
        {
            bool doReport(true);
            // exception for delete operator. it check for var != 0 before really delete
            node1 = skipBackNop(node->parent);
            if (node1 == COND_EXPR)
            {
                CondExprNode *cond = static_cast<CondExprNode*>(node1);
                if (cond->args.size() >= 2 &&
                    skipNop(cond->args[0]) == NE_EXPR)
                {
                    if (skipNop(cond->args[1]) == COMPOUND_EXPR)
                    {
                        CompoundExprNode *compound = static_cast<CompoundExprNode*>(
                            skipNop(cond->args[1]));
                        if (compound &&
                            compound->args.size() == 2 &&
                            compound->args[0] == CALL_EXPR &&
                            compound->args[1] == CALL_EXPR)
                        {
                            CallExprNode *call = static_cast<CallExprNode*>(
                                skipNop(compound->args[1]));
                            if (call && call->function == ADDR_EXPR)
                            {
                                AddrExprNode *addr = static_cast<AddrExprNode*>(
                                    skipNop(call->function));
                                if (addr &&
                                    !addr->args.empty() &&
                                    skipNop(addr->args[0]) == FUNCTION_DECL &&
                                    skipNop(addr->args[0])->label == "operator delete")
                                {
                                    doReport = false;
                                }
                            }
                        }
                    }
                    else if (!cond->args.empty() &&
                             skipNop(cond->args[1]) == CALL_EXPR)
                    {
                        CallExprNode *call = static_cast<CallExprNode*>(
                            skipNop(cond->args[1]));
                        if (call && skipNop(call->function) == OBJ_TYPE_REF)
                        {
                            ObjTypeRefNode *typeRef = static_cast<ObjTypeRefNode*>(
                                skipNop(call->function));
                            if (typeRef &&
                                !typeRef->args.empty() &&
                                skipNop(typeRef->args[0]) == INDIRECT_REF)
                            {
                                IndirectRefNode *indirect = static_cast<IndirectRefNode*>(
                                    skipNop(typeRef->args[0]));
                                if (indirect &&
                                    skipNop(indirect->ref) == POINTER_PLUS_EXPR)
                                {
                                    PointerPlusExprNode *plusExpr = static_cast<PointerPlusExprNode*>(
                                        skipNop(indirect->ref));
                                    if (plusExpr &&
                                        !plusExpr->args.empty() &&
                                        skipNop(plusExpr->args[0]) == COMPONENT_REF)
                                    {
                                        ComponentRefNode *comp = static_cast<ComponentRefNode*>(
                                            skipNop(plusExpr->args[0]));
                                        if (comp &&
                                            skipNop(comp->object) == INDIRECT_REF &&
                                            skipNop(comp->field) == FIELD_DECL)
                                        {
                                            std::string label = skipNop(comp->field)->label;
                                            if (label.size() > 6 && label.substr(0, 6) == "_vptr.")
                                                doReport = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (doReport)
                reportUselessCheck(node, var);
        }
    }
    wo.cleanExpr = false;
    wo.uselessExpr = true;
}

void analyseEqExpr(EqExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || checkCommand(FindArgs))
        return;

    // PARM_DECL or VAR_DECL ?
    Node *node1 = skipNop(node->args[0]);
    // INTEGER_CST?
    Node *node2 = skipNop(node->args[1]);
    std::string var = getVariableName(node1);
    // if (var == 0)
    if (!var.empty() &&
        node2 == INTEGER_CST &&
        node2->label == "0")
    {
        if (wi.needCheckNullVars.find(var) != wi.needCheckNullVars.end())
        {
            wo.checkedNullVars.insert(var);
            wo.knownNullVars.insert(var);
            wo.cleanExpr = true;
            wo.uselessExpr = false;
            if (wi.knownNullVars.find(var) != wi.knownNullVars.end())
            {
                reportUselessCheck(node, var);
            }
            return;
        }
        else if (wi.knownNullVars.find(var) != wi.knownNullVars.end())
        {
            reportUselessCheck(node, var);
        }
    }
    wo.cleanExpr = false;
    wo.uselessExpr = true;
}

void analyseOrCondition(Node *node, Node *node1, Node *node2, const WalkItem &wi, WalkItem &wo)
{
    WalkItem wo1 = wo;
    WalkItem wo2 = wo;
    walkTree(node1, wi, wo1);
    Log::dumpWI(node, "wo1 ", wo1);
    WalkItem wi2 = wi;
    removeNeedCheckNullVarsSetAll(wi2, wo1.checkedNullVars);
    wi2.needCheckNullVars.insert(wo1.checkedNonNullVars.begin(),
        wo1.checkedNonNullVars.end());
    wi2.knownVars.insert(wo1.checkedNonNullVars.begin(),
        wo1.checkedNonNullVars.end());
    wi2.knownVars.insert(wo1.checkedNullVars.begin(),
        wo1.checkedNullVars.end());
    Log::dumpWI(node, "wi2 ", wi2);
    walkTree(node2, wi2, wo2);
    Log::dumpWI(node, "wo2 ", wo2);
    // probably condition wrong
    if (wo1.cleanExpr)
        mergeNullChecked(wo, wo1);
    // probably condition wrong
    if (wo2.cleanExpr)
        mergeNullChecked(wo, wo2);
    intersectNonNullChecked(wo, wo1, wo2);

    // need intersect knownNull/knownNonNull

    wo.cleanExpr = true;
    wo.stopWalking = true;
    wo.uselessExpr = false;
}

void analyseAndCondition(Node *node, Node *node1, Node *node2, const WalkItem &wi, WalkItem &wo)
{
    WalkItem wo1 = wo;
    WalkItem wo2 = wo;
    walkTree(node1, wi, wo1);
    Log::dumpWI(node, "wo1 ", wo1);
    WalkItem wi2 = wi;
    removeNeedCheckNullVarsSetAll(wi2, wo1.checkedNonNullVars);
    wi2.needCheckNullVars.insert(wo1.checkedNullVars.begin(),
        wo1.checkedNullVars.end());
    wi2.knownNullVars.insert(wo1.checkedNullVars.begin(),
        wo1.checkedNullVars.end());
    wi2.knownNonNullVars.insert(wo1.checkedNonNullVars.begin(),
        wo1.checkedNonNullVars.end());
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
    wo.knownNullVars.insert(wo1.knownNullVars.begin(),
        wo1.knownNullVars.end());
    wo.knownNullVars.insert(wo2.knownNullVars.begin(),
        wo2.knownNullVars.end());
    wo.knownNonNullVars.insert(wo1.knownNonNullVars.begin(),
        wo1.knownNonNullVars.end());
    wo.knownNonNullVars.insert(wo2.knownNonNullVars.begin(),
        wo2.knownNonNullVars.end());
    wo.cleanExpr = wo1.cleanExpr && wo2.cleanExpr;
    wo.uselessExpr = wo1.uselessExpr && wo2.uselessExpr;
}

void analyseTruthOrIfExpr(TruthOrIfExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || checkCommand(FindArgs))
        return;

    analyseOrCondition(node, node->args[0], node->args[1], wi, wo);
}

void analyseTruthOrExpr(TruthOrExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || checkCommand(FindArgs))
        return;

    analyseOrCondition(node, node->args[0], node->args[1], wi, wo);
}

void analyseTruthAndIfExpr(TruthAndIfExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || checkCommand(FindArgs))
        return;

    analyseAndCondition(node, node->args[0], node->args[1], wi, wo);
}

void analyseTruthAndExpr(TruthAndExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || checkCommand(FindArgs))
        return;

    analyseAndCondition(node, node->args[0], node->args[1], wi, wo);
}

// args[0]  condition
// args[1]  true expr
// args[2]  false expr
void analyseCondExpr(CondExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need tree args for check
    if (node->args.size() < 3 || checkCommand(FindArgs))
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
    if (node->args.size() < 1 || checkCommand(FindArgs))
        return;

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

    wo.cleanExpr = true;
    wo.stopWalking = true;
    wo.uselessExpr = false;
}

// type var1 = var2;
void analyseBindExpr(BindExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    const size_t sz = node->args.size();
    if (sz < 1 || checkCommand(FindArgs))
        return;

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

    handleSetVarDecl(node->args[0], wi, wo);
    wo.stopWalking = true;
}

// type var1 = var2;
void analyseDeclExpr(DeclExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need one arg for check
    if (node->args.empty() || checkCommand(FindArgs))
        return;

    handleSetVarDecl(node->args[0], wi, wo);
}

void analyseNopExpr(NopExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need one arg for check
    if (node->args.empty())
        return;

    walkTree(node->args[0], wi, wo);
    wo.stopWalking = true;
}

void analyseNonLvalueExpr(NonLvalueExprNode *node, const WalkItem &wi, WalkItem &wo)
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
    walkTree(node->chain, wi, wo2);
    Log::dumpWI(node, "wo chain ", wo2);
    wo2 = wo;
    bool enableCheck(true);
    std::set<int> nullAttrs;
    if (node->function)
    {
        walkTree(node->function, wi, wo2);
        Node *function = skipNop(node->function);
        Log::dumpWI(node, "wo function ", wo2);
        if (function == ADDR_EXPR)
        {
            AddrExprNode *addrNode = static_cast<AddrExprNode*>(function);
            if (!addrNode->args.empty())
            {
                Node *decl = skipNop(addrNode->args[0]);
                if (decl == FUNCTION_DECL)
                {
                    function = decl;
                    FunctionDeclNode *declNode = static_cast<FunctionDeclNode*>(
                        decl);
                    if (declNode->functionType == FUNCTION_TYPE)
                    {
                        enableCheck = false;
                    }
                }
            }
        }
        else if (node->function == VAR_DECL)
        {
            enableCheck = false;
        }
        else
        {
            if (function == ARRAY_REF)
            {
                ArrayRefNode *arrRef = static_cast<ArrayRefNode*>(function);
                if (!arrRef->args.empty() &&
                    (arrRef->args[0] == COMPONENT_REF || VAR_DECL))
                {
                    function = arrRef->args[0];
                }
            }
            if (function == CONVERT_EXPR)
            {
                ConvertExprNode *convExpr = static_cast<ConvertExprNode*>(function);
                if (!convExpr->args.empty())
                    function = convExpr->args[0];
            }
            reportParmDeclNullPointer(node, function, wi);
            if (!getVariableName(function).empty())
                enableCheck = false;
        }
        if (function == FUNCTION_DECL)
        {
            getFunctionParamsNonNullAttributes(
                static_cast<FunctionDeclNode*>(function),
                nullAttrs);
        }
    }
    int param = 1;
    FOR_EACH (it, node->args)
    {
        wo2 = wo;
        Node *node2 = skipNop(it);
        if (enableCheck)
        {
            reportParmDeclNullPointer(node, node2, wi);
            enableCheck = false;
        }
        else
        {
            if (nullAttrs.find(param) != nullAttrs.end())
                reportParmDeclAttrNullPointer(node, node2, wi);
        }
        walkTree(node2, wi, wo2);
        Log::dumpWI(node, "wo arg ", wo2);
        param ++;
    }
    wo.stopWalking = true;
}

void analyseCleanupPointExpr(CleanupPointExprNode* node, const WalkItem &wi, WalkItem &wo)
{
    WalkItem wo2 = wo;
    FOR_EACH (it, node->args)
    {
        wo2 = wo;
        Node *node2 = skipNop(it);
        reportParmDeclNullPointer(node, node2, wi);
        walkTree(node2, wi, wo2);
        Log::dumpWI(node, "wo arg ", wo2);
    }
    wo = wo2;
    wo.stopWalking = true;
}

void handleSetVarDecl(Node *node,
                      const WalkItem &wi,
                      WalkItem &wo)
{
    node = skipNop(node);
    if (node == VAR_DECL)
    {
        VarDeclNode *varDecl = static_cast<VarDeclNode*>(node);
        Node *initial = skipNop(varDecl->initial);
        handleSetVar(varDecl, initial, wi, wo);
    }
}

void handleSetVar(Node *node1,
                  Node *node2,
                  const WalkItem &wi,
                  WalkItem &wo)
{
    // var1 = var2
    const std::string var1 = getVariableName(node1);
    const std::string var2 = getVariableName(node2);
    if (var1.empty() || var2.empty())
        return;
    if (wi.needCheckNullVars.find(var2) == wi.needCheckNullVars.end())
        return;
    addNullVar(wo, var1);
    addLinkedVar(wo, var2, var1);
}

// field = var
void analyseInitExpr(InitExprNode* node,
                     const WalkItem &wi,
                     WalkItem &wo)
{
    // need one arg for check
    if (node->args.size() < 2 || checkCommand(FindArgs))
        return;

    handleSetVar(node->args[0], node->args[1], wi, wo);
}

}
