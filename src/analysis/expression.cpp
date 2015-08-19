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
#include "analysis/collections.h"
#include "analysis/checks.h"
#include "analysis/function.h"
#include "analysis/reports.h"
#include "analysis/statement.h"
#include "analysis/varitem.h"
#include "analysis/walkitem.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/aggrinit_expr.h"
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
#include "nodes/expr/trycatch_expr.h"

#include "nodes/decl/function_decl.h"
#include "nodes/decl/var_decl.h"

#include "nodes/ref/array_ref.h"
#include "nodes/ref/component_ref.h"
#include "nodes/ref/indirect_ref.h"
#include "nodes/ref/objtype_ref.h"

#include "nodes/type/array_type.h"
#include "nodes/type/method_type.h"
#include "nodes/type/reference_type.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

// return variable name if possible or empty string
VarItem getVariableName(Node *node)
{
    if (!node)
        return VarItem();

    node = skipNop(node);
    if (!node)
        return VarItem();

    if (node == PARM_DECL)
    {
        ParmDeclNode *decl = static_cast<ParmDeclNode*>(node);
        if (skipNop(decl->declType) != nullptr &&
            skipNop(decl->declType) != POINTER_TYPE)
        {
            return VarItem();
        }
        return VarItem(node->label);
    }
    if (node == VAR_DECL)
    {
        VarDeclNode *var = static_cast<VarDeclNode*>(node);
        if (skipNop(var->varType) != POINTER_TYPE)
            return VarItem();
        return VarItem(node->label);
    }
    else if (node == COMPONENT_REF)
    {
        return getComponentRefVariable(node);
    }
    return VarItem();
}

bool isPointerArg(Node *node)
{
    if (!node)
        return false;

    node = skipNop(node);
    if (!node)
        return false;
    if (node == PARM_DECL)
    {
        ParmDeclNode *decl = static_cast<ParmDeclNode*>(node);
        if (skipNop(decl->declType) == nullptr ||
            skipNop(decl->declType) == POINTER_TYPE)
        {
            return true;
        }
    }
    else if (node == VAR_DECL)
    {
        VarDeclNode *var = static_cast<VarDeclNode*>(node);
        if (skipNop(var->varType) == POINTER_TYPE)
            return true;
    }
    else if (node == COMPONENT_REF)
    {
        return true;
    }
    return false;
}

// return variable name in format object->field for component node
VarItem getComponentRefVariable(Node *node)
{
    VarItem str;
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
            FieldDeclNode *fieldDecl = static_cast<FieldDeclNode*>(field);
            if (fieldDecl->fieldType != POINTER_TYPE)
                return str;
            if (findTreeListPurpose(static_cast<TreeListNode*>(
                skipNop(fieldDecl->attribute)),
                "nonnullpointer"))
            {
                str.isNonNull = true;
            }
            IndirectRefNode *indirect = static_cast<IndirectRefNode*>(object);
            Node *ref = skipNop(indirect->ref);
            if (ref && !isValidVar(ref->label))
                return str;
            if (ref == PARM_DECL)
            {
                ParmDeclNode *parmDecl = static_cast<ParmDeclNode*>(ref);
                if (findTreeListPurpose(static_cast<TreeListNode*>(
                    skipNop(parmDecl->attribute)),
                    "nonnullpointer"))
                {
                    str.isNonNull = true;
                }
            }
            if (ref == VAR_DECL)
            {
                VarDeclNode *varDecl = static_cast<VarDeclNode*>(ref);
                if (findTreeListPurpose(static_cast<TreeListNode*>(
                    skipNop(varDecl->attribute)),
                    "nonnullpointer"))
                {
                    str.isNonNull = true;
                }
            }
            if (ref == PARM_DECL || ref == VAR_DECL)
            {
                if (!isValidVar(field->label))
                    return str;
                str.name.append(ref->label).append("->").append(field->label);
            }
        }
    }
    return str;
}

bool isValidVar(const VarItem &str)
{
    if (str.size() > 6 && str.name.substr(0, 6) == "_vptr.")
        return false;
    return true;
}

std::vector<VarItem> getComponentRefParts(Node *node)
{
    std::vector<VarItem> str;
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
            FieldDeclNode *fieldDecl = static_cast<FieldDeclNode*>(field);
            IndirectRefNode *indirect = static_cast<IndirectRefNode*>(object);
            bool isNonNull(false);
            if (findTreeListPurpose(static_cast<TreeListNode*>(
                skipNop(fieldDecl->attribute)),
                "nonnullpointer"))
            {
                isNonNull = true;
            }
            Node *ref = skipNop(indirect->ref);
            if (ref && !isValidVar(ref->label))
                return str;
            if (ref == PARM_DECL)
            {
                ParmDeclNode *parmDecl = static_cast<ParmDeclNode*>(ref);
                bool isNonNull2(false);
                if (findTreeListPurpose(static_cast<TreeListNode*>(
                    skipNop(parmDecl->attribute)),
                    "nonnullpointer"))
                {
                    isNonNull2 = true;
                }
                if (skipNop(parmDecl->declType) == nullptr ||
                    skipNop(parmDecl->declType) == POINTER_TYPE)
                {
                    str.push_back(VarItem(ref->label, isNonNull2));
                }
            }
            if (ref == VAR_DECL)
            {
                VarDeclNode *varDecl = static_cast<VarDeclNode*>(ref);
                bool isNonNull2(false);
                if (findTreeListPurpose(static_cast<TreeListNode*>(
                    skipNop(varDecl->attribute)),
                    "nonnullpointer"))
                {
                    isNonNull2 = true;
                }
                if (varDecl->varType == POINTER_TYPE)
                    str.push_back(VarItem(ref->label, isNonNull2));
            }
            if (ref == PARM_DECL || ref == VAR_DECL)
            {
                if (skipNop(fieldDecl->fieldType) != POINTER_TYPE)
                {
                    if (skipNop(fieldDecl->fieldType) != ARRAY_TYPE)
                        return str;
                    ArrayTypeNode *arr = static_cast<ArrayTypeNode*>(skipNop(fieldDecl->fieldType));
                    if (arr->elementType != POINTER_TYPE)
                        return str;
                }
                if (!isValidVar(field->label))
                    return str;
                str.push_back(VarItem(std::string(ref->label).append("->").append(field->label), isNonNull));
            }
        }
    }
    return str;
}

std::vector<VarItem> getComponentRefLeftParts(Node *node)
{
    std::vector<VarItem> str;
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
            FieldDeclNode *fieldDecl = static_cast<FieldDeclNode*>(field);
            bool isNonNull(false);
//            if (fieldDecl->fieldType != POINTER_TYPE)
//                return str;
            IndirectRefNode *indirect = static_cast<IndirectRefNode*>(object);
            Node *ref = skipNop(indirect->ref);
            if (ref && !isValidVar(ref->label))
                return str;
            if (ref == PARM_DECL)
            {
                ParmDeclNode *parmDecl = static_cast<ParmDeclNode*>(ref);
                if (findTreeListPurpose(static_cast<TreeListNode*>(
                    skipNop(parmDecl->attribute)),
                    "nonnullpointer"))
                {
                    isNonNull = true;
                }
                if (skipNop(parmDecl->declType) != nullptr &&
                    skipNop(parmDecl->declType) != POINTER_TYPE)
                {
                    return str;
                }
            }
            if (ref == VAR_DECL)
            {
                VarDeclNode *varDecl = static_cast<VarDeclNode*>(ref);
                if (findTreeListPurpose(static_cast<TreeListNode*>(
                    skipNop(varDecl->attribute)),
                    "nonnullpointer"))
                {
                    isNonNull = true;
                }
                if (varDecl->varType != POINTER_TYPE)
                    return str;
            }
            if (ref == PARM_DECL || ref == VAR_DECL)
            {
                str.push_back(VarItem(ref->label, isNonNull));
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
        VarItem var1 = getVariableName(arg);
        VarItem var2 = getVariableName(node->args[1]);
        //Log::log("analyseModifyExpr vars: %s, %s\n", var1.name.c_str(), var2.name.c_str());

        Node *arg0 = arg;
        if (arg == COMPONENT_REF)
        {
            ComponentRefNode *comp = static_cast<ComponentRefNode*>(arg);
            if (skipNop(comp->object) == INDIRECT_REF)
                arg0 = skipNop(comp->object);

            if (arg0 == INDIRECT_REF && !var1.isNonNull)
            {
                // var2 not found in known checking pointer
                reportParmDeclNullPointer(node,
                    static_cast<IndirectRefNode*>(arg0)->ref,
                    wi);
            }
        }
        if (arg == INDIRECT_REF)
        {
            if (!var1.isNonNull)
            {
                // var2 not found in known checking pointer
                reportParmDeclNullPointer(node,
                    static_cast<IndirectRefNode*>(arg)->ref,
                    wi);

                if (!var1.empty() &&
                    isNotIn(var2.name, wi.needCheckNullVars) &&
                    isNotIn(var2.name, wi.knownVars))
                {
                    removeVar(wo, var1.name);
                }
            }
        }
        else if (!var1.empty())
        {
            if (var2.empty())
            {   // have var1 only (var1 = UNKNOWN or var1 = function(...))

                if (node->args.size() < 2)
                    return;
                Node *arg1 = skipNop(node->args[1]);
                walkTree(arg, wi, wo);
                walkTree(arg1, wi, wo);
                wo.stopWalking = true;

                bool handled(false);
                handled = handleSetVarToFunction(var1, arg, arg1, wo);
                // have var1 only (var1 = UNKNOWN)
                if (!var1.isNonNull && !handled)
                    removeVar(wo, var1.name);
            }
            else
            {   // have var1 and var2 (var1 = var2)
                if (isIn(var2.name, wi.knownVars))
                {
                    addLinkedVar(wo, var2.name, var1.name);
                }
                // var2 not found in known checking pointer
                else if (!var1.isNonNull &&
                         isNotIn(var2.name, wi.needCheckNullVars) &&
                         isNotIn(var2.name, wi.knownVars))
                {
                    removeVar(wo, var1.name);
                }
            }
        }
        else
        {
            if (var1.empty() || !var1.isNonNull)
                reportParmDeclLeftNullPointer(node, node->args[0], wi);
            if (var2.empty() || !var2.isNonNull)
                reportParmDeclLeftNullPointer(node, node->args[1], wi);
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

    VarItem var = getVariableName(node->args[0]);
    if (!var.empty())
    {
        if (!var.isNonNull &&
            isNotIn(var.name, wi.knownNonNullVars))
        {
            reportParmDeclNullPointer(node, node->args[0], wi);
        }
        else if (var.isNonNull)
        {
            addNonNullVar(wo, var.name);
        }
        else
        {
            addUnknownVar(wo, var.name);
        }
    }
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

    VarItem var = getVariableName(node->args[0]);
    if (skipNop(node->args[0]) == VAR_DECL)
    {
        // do not report if found &ptr
        if (!var.empty())
            return;
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
    // integer 0?
    Node *node2 = skipNop(node->args[1]);

    reportParmDeclLeftNullPointer(node, node1, wi);
    reportParmDeclLeftNullPointer(node, node2, wi);

    WalkItem wo2 = wo;
    walkTree(node2, wi, wo2);

    VarItem var = getVariableName(node1);
    // if (var != 0)
    if (!var.empty() &&
        wo2.isNum &&
        wo2.num == 0)
    {
        if (isIn(var.name, wi.needCheckNullVars) ||
            isNotIn(var.name, wi.knownVars))
        {
            wo.checkedThenNonNullVars.insert(var.name);
            wo.checkedElseNullVars.insert(var.name);
            wo.knownNonNullVars.insert(var.name);
            wo.knownVars.insert(var.name);
            wo.cleanExpr = true;
            wo.uselessExpr = false;
            return;
        }
        else if (isIn(var.name, wi.knownNonNullVars) ||
                 isIn(var.name, wi.knownNullVars))
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

            wo.checkedThenNonNullVars.insert(var.name);
            wo.checkedElseNullVars.insert(var.name);
            wo.cleanExpr = true;
            wo.uselessExpr = false;
            if (doReport)
                reportUselessCheck(node, var.name);
            return;
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
    // integer 0?
    Node *node2 = skipNop(node->args[1]);

    reportParmDeclLeftNullPointer(node, node1, wi);
    reportParmDeclLeftNullPointer(node, node2, wi);

    WalkItem wo2 = wo;
    walkTree(node2, wi, wo2);

    VarItem var = getVariableName(node1);
    // if (var == 0)
    if (!var.empty() &&
        wo2.isNum &&
        wo2.num == 0)
    {
        if (isIn(var.name, wi.needCheckNullVars) ||
            isNotIn(var.name, wi.knownVars))
        {
            wo.checkedThenNullVars.insert(var.name);
            wo.checkedElseNonNullVars.insert(var.name);
            wo.knownNullVars.insert(var.name);
            wo.knownVars.insert(var.name);
            wo.cleanExpr = true;
            wo.uselessExpr = false;
            if (isIn(var.name, wi.knownNullVars) ||
                isIn(var.name, wi.knownNonNullVars))
            {
                reportUselessCheck(node, var.name);
            }
            return;
        }
        else if (isIn(var.name, wi.knownNullVars) ||
                 isIn(var.name, wi.knownNonNullVars))
        {
            wo.checkedThenNullVars.insert(var.name);
            wo.checkedElseNonNullVars.insert(var.name);
            reportUselessCheck(node, var.name);
            wo.cleanExpr = true;
            wo.uselessExpr = false;
            return;
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
    removeNeedCheckNullVarsSetAll(wi2, wo1.checkedElseNonNullVars);
    wi2.needCheckNullVars.insert(wo1.checkedElseNullVars.begin(),
        wo1.checkedElseNullVars.end());
    wi2.knownVars.insert(wo1.checkedElseNonNullVars.begin(),
        wo1.checkedElseNonNullVars.end());
    wi2.knownVars.insert(wo1.checkedElseNullVars.begin(),
        wo1.checkedElseNullVars.end());
    Log::dumpWI(node, "wi2 ", wi2);
    walkTree(node2, wi2, wo2);
    Log::dumpWI(node, "wo2 ", wo2);
    intersectThenNonNullChecked(wo, wo1, wo2);
    intersectThenNullChecked(wo, wo1, wo2);

    if (!wo1.uselessExpr && !wo2.uselessExpr)
    {   // need combine wo1 and wo2
        intersectElseNullChecked(wo, wo1, wo2);
    }
    if (!wo1.uselessExpr)
    {
        mergeElseNullChecked(wo, wo1);
        mergeElseNonNullChecked(wo, wo1);
    }
    if (!wo2.uselessExpr)
    {
        mergeElseNullChecked(wo, wo2);
        mergeElseNonNullChecked(wo, wo2);
    }

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
    removeNeedCheckNullVarsSetAll(wi2, wo1.checkedThenNonNullVars);
    wi2.needCheckNullVars.insert(wo1.checkedThenNullVars.begin(),
        wo1.checkedThenNullVars.end());
    wi2.knownNullVars.insert(wo1.checkedThenNullVars.begin(),
        wo1.checkedThenNullVars.end());
    wi2.knownNonNullVars.insert(wo1.checkedThenNonNullVars.begin(),
        wo1.checkedThenNonNullVars.end());
    Log::dumpWI(node, "wi2 ", wi2);
    walkTree(node2, wi2, wo2);
    Log::dumpWI(node, "wo2 ", wo2);

    wo.stopWalking = true;
    // probably condition wrong
//    if (!wo1.uselessExpr && !wo2.uselessExpr)
//    {   // need combine wo1 and wo2
//        intersectThenNullChecked(wo, wo1, wo2);
//    }
//    if (!wo1.uselessExpr)
    {
        mergeThenNonNullChecked(wo, wo1);
        mergeThenNullChecked(wo, wo1);
    }
//    if (!wo2.uselessExpr)
    {
        mergeThenNonNullChecked(wo, wo2);
        mergeThenNullChecked(wo, wo2);
    }
    wo.knownNullVars.insert(wo1.knownNullVars.begin(),
        wo1.knownNullVars.end());
    wo.knownNullVars.insert(wo2.knownNullVars.begin(),
        wo2.knownNullVars.end());
    wo.knownNonNullVars.insert(wo1.knownNonNullVars.begin(),
        wo1.knownNonNullVars.end());
    wo.knownNonNullVars.insert(wo2.knownNonNullVars.begin(),
        wo2.knownNonNullVars.end());

    intersectElseNonNullChecked(wo, wo1, wo2);
    intersectElseNullChecked(wo, wo1, wo2);

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

    // copy number value from last COMPOUND_EXPR child node
    wo.isNum = wo2.isNum;
    wo.num = wo2.num;

    // probably condition wrong
    if (wo2.cleanExpr)
    {
        mergeThenNullChecked(wo, wo2);
        mergeThenNonNullChecked(wo, wo2);
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
//    Log::log("start args 1\n");
    walkTree(node->args[1], wi2, wo);
//    Log::log("end args 1\n");
    wi2 = wo;
    Log::dumpWI(node, "wi2 ", wi2);
//    Log::log("start args 0\n");
    walkTree(node->args[0], wi2, wo);
//    Log::log("end args 0\n");
    if (sz > 2)
    {
        wi2 = wo;
        Log::dumpWI(node, "wi2 ", wi2);
//        Log::log("start args 2\n");
        walkTree(node->args[2], wi2, wo);
//        Log::log("end args 2\n");
    }

    handleSetVarDecl(node->args[0], wi2, wo);
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
    if (checkCommand(FindArgs))
        return;

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
                    if (declNode->label == "paranuckerInternalTest")
                    {
                        checkState(node, wi);
                        wo.stopWalking = true;
                        return;
                    }
                    if (skipNop(declNode->functionType) == FUNCTION_TYPE)
                    {
                        enableCheck = false;
                    }
                }
            }
        }
        else if (function == VAR_DECL)
        {
            enableCheck = false;
        }
        else
        {
            if (function == ARRAY_REF)
            {
                ArrayRefNode *arrRef = static_cast<ArrayRefNode*>(function);
                if (!arrRef->args.empty() &&
                    (skipNop(arrRef->args[0]) == COMPONENT_REF ||
                    skipNop(arrRef->args[0]) == VAR_DECL))
                {
                    function = arrRef->args[0];
                }
            }
            if (function == CONVERT_EXPR)
            {
                ConvertExprNode *convExpr = static_cast<ConvertExprNode*>(function);
                if (!convExpr->args.empty())
                    function = skipNop(convExpr->args[0]);
                if (function == PARM_DECL)
                {
                    ParmDeclNode *parm = static_cast<ParmDeclNode*>(function);
                    if (skipNop(parm->declType) == REFERENCE_TYPE)
                    {
                        ReferenceTypeNode *ref = static_cast<ReferenceTypeNode*>(
                            skipNop(parm->declType));
                        if (ref->nestedType == FUNCTION_TYPE)
                            enableCheck = false;
                    }
                }
            }
            VarItem var = getVariableName(function);
            if (!var.isNonNull)
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

        VarItem var = getVariableName(node2);
        if (enableCheck)
        {
            if (!var.isNonNull)
                reportParmDeclNullPointer(node, node2, wi);
            enableCheck = false;
        }
        else
        {
            reportParmDeclLeftNullPointer(node, node2, wi);
            if (isIn(param, nullAttrs))
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
        VarItem var = getVariableName(node2);
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
        if (skipNop(varDecl->varType) == POINTER_TYPE)
        {
            Node *initial = skipNop(varDecl->initial);
            handleSetVar(varDecl, initial, wi, wo);
        }
    }
}

bool handleSetVarToFunctionBack(const VarItem &var,
                                Node *node2,
                                WalkItem &wo)
{
    WalkItem wo2 = wo;
    walkTree(node2, wo, wo2);

    if (wo2.isNum)
    {
        if (!var.isNonNull)
        {
            if (wo2.num == 0)
                addNullVar(wo, var.name);
            else
                addNonNullVar(wo, var.name);
        }
        return true;
    }
    return false;
}

bool handleSetVarToFunction(const VarItem &var,
                            Node *node1,
                            Node *node2,
                            WalkItem &wo)
{
    //if (node1)
    //    Log::log("node1=%s\n", node1->nodeTypeName.c_str());
    //if (node2)
    //    Log::log("node2=%s\n", node2->nodeTypeName.c_str());
    if (var.isNonNull)
        return false;
    node1 = skipNop(node1);
    node2 = skipNop(node2);

    reportParmDeclLeftNullPointer(node1, node1, wo);
    reportParmDeclNullPointer(node2, node2, wo);

    if (!isPointerArg(node1))
        return handleSetVarToFunctionBack(var, node2, wo);

    if (node2 == nullptr)
    {   // type *var;
        if (!var.isNonNull && isNotIn(var.name, wo.knownVars))
            addUnknownVar(wo, var.name);
        return true;
    }

    if (node2 == ADDR_EXPR)
    {
        if (node1 == VAR_DECL)
        {
            // var = &expr;
            VarDeclNode *varDecl = static_cast<VarDeclNode*>(node1);
            if (skipNop(varDecl->varType) == POINTER_TYPE)
            {
                addNonNullVar(wo, var.name);
                return true;
            }
        }
        AddrExprNode *addr = static_cast<AddrExprNode*>(node2);
        if (!addr->args.empty() && skipNop(addr->args[0]) == VAR_DECL)
        {
            if (!var.isNonNull)
            {
                VarDeclNode *varDecl = static_cast<VarDeclNode*>(skipNop(addr->args[0]));
                if (skipNop(varDecl->varType) != POINTER_TYPE)
                    addNonNullVar(wo, var.name);
                else
                    addUnknownVar(wo, var.name);
            }
            return true;
        }
    }

    if (node2 != CALL_EXPR)
    {
        if (node2 != COMPOUND_EXPR)
            return handleSetVarToFunctionBack(var, node2, wo);
        CompoundExprNode *comp = static_cast<CompoundExprNode*>(node2);
        if (comp->args.empty())
            return handleSetVarToFunctionBack(var, node2, wo);
        node2 = skipNop(comp->args[comp->args.size() - 1]);
        if (node2 != COMPOUND_EXPR)
            return handleSetVarToFunctionBack(var, node2, wo);
        comp = static_cast<CompoundExprNode*>(node2);
        if (comp->args.empty())
            return handleSetVarToFunctionBack(var, node2, wo);
        if(comp->args.size() > 1 &&
           skipNop(comp->args[0]) == TARGET_EXPR &&
           skipNop(comp->args[1]) == COMPOUND_EXPR)
        {
            comp = static_cast<CompoundExprNode*>(skipNop(comp->args[1]));
        }
        if (skipNop(comp->args[0]) == TRY_CATCH_EXPR)
        {
            TryCatchExprNode *tryCatch = static_cast<TryCatchExprNode*>(skipNop(comp->args[0]));
            if (tryCatch->args.empty())
                return handleSetVarToFunctionBack(var, node2, wo);
            node2 = tryCatch->args[0];
        }
        else
        {
            node2 = comp->args[0];
        }

        if (skipNop(node2) == INIT_EXPR)
        {
            InitExprNode *init = static_cast<InitExprNode*>(skipNop(node2));
            if (!init || init->args.size() < 2)
                return handleSetVarToFunctionBack(var, node2, wo);
            node2 = init->args[1];
        }
        node2 = skipNop(node2);
        if (node2 == CONSTRUCTOR)
        {
            addNonNullVar(wo, var.name);
            return true;
        }
        if (node2 != CALL_EXPR && node2 != AGGR_INIT_EXPR)
            return handleSetVarToFunctionBack(var, node2, wo);
    }

    AddrExprNode *addr = nullptr;
    if (node2 == CALL_EXPR)
    {
        CallExprNode *call = static_cast<CallExprNode*>(node2);
        if (!call || skipNop(call->function) != ADDR_EXPR)
            return handleSetVarToFunctionBack(var, node2, wo);
        addr = static_cast<AddrExprNode*>(skipNop(call->function));
    }
    else if (node2 == AGGR_INIT_EXPR)
    {
        AggrInitExprNode *aggr = static_cast<AggrInitExprNode*>(node2);
        if (skipNop(aggr->function) != ADDR_EXPR)
            return handleSetVarToFunctionBack(var, node2, wo);
        addr = static_cast<AddrExprNode*>(skipNop(aggr->function));
    }

    if (!addr ||
        addr->args.empty() ||
        skipNop(addr->args[0]) != FUNCTION_DECL)
    {
        return false;
    }
    FunctionDeclNode *func = static_cast<FunctionDeclNode*>(skipNop(addr->args[0]));
    removeVar(wo, var.name);

    if (func->label != "__comp_ctor ")
    {
        if (!func->functionType)
            return false;
        Node *returnType;
        if (skipNop(func->functionType) == FUNCTION_TYPE)
            returnType = static_cast<FunctionTypeNode*>(skipNop(func->functionType))->returnType;
        else if (skipNop(func->functionType) == METHOD_TYPE)
            returnType = static_cast<MethodTypeNode*>(skipNop(func->functionType))->returnType;
        else
            return false;
        returnType = skipNop(returnType);
        if (returnType != POINTER_TYPE)
            return false;
    }

    //Log::log("func->label='%s'\n", func->label.c_str());
    if (findTreeListPurpose(static_cast<TreeListNode*>(func->functionType->attribute),
        "returns_nonnull") ||
        func->label == "operator new" ||
        func->label == "operator new []" ||
        func->label == "__comp_ctor ")
    {   // function have attribute returns_nonnull. This mean result cant be null
        addNonNullVar(wo, var.name);
        //Log::log("add non null var: %s\n", var.name.c_str());
    }
    else
    {   // function not have attribute returns_nonnull. This mean result can be null
        addUnknownVar(wo, var.name);
        //Log::log("add unknown var: %s\n", var.name.c_str());
    }
    return true;
}

void handleSetVar(Node *node1,
                  Node *node2,
                  const WalkItem &wi,
                  WalkItem &wo)
{
    // var1 = var2
    const VarItem var1 = getVariableName(node1);
    const VarItem var2 = getVariableName(node2);
    //Log::log("handleSetVar vars: %s, %s\n", var1.name.c_str(), var2.name.c_str());
    if (var1.empty())
        return;
    if (var2.empty())
    {
        node2 = skipNop(node2);
        handleSetVarToFunction(var1, node1, node2, wo);
        return;
    }
    else
    {
        if (isIn(var2.name, wi.knownVars))
            addLinkedVar(wo, var2.name, var1.name);
        else if (!var1.isNonNull)
            addUnknownVar(wo, var1.name);
    }
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
    reportParmDeclLeftNullPointer(node, node->args[0], wi);
    reportParmDeclLeftNullPointer(node, node->args[1], wi);
}

}
