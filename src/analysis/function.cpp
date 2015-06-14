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

#include "analysis/function.h"

#include "command.h"
#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/walkitem.h"

#include "nodes/decl/function_decl.h"

#include "nodes/list/tree_list.h"

#include "nodes/type/method_type.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

// put arg types into arr
void getFunctionArgTypes(FunctionDeclNode *node,
                         std::vector<TypeNode*> &arr)
{
    // function not have type
    if (!node->functionType)
        return;

    TreeListNode *types = nullptr;
    if (node->functionType->nodeType == FUNCTION_TYPE)
        types = static_cast<FunctionTypeNode*>(node->functionType)->argTypes;
    else if (node->functionType->nodeType == METHOD_TYPE)
        types = static_cast<MethodTypeNode*>(node->functionType)->argTypes;
    else
        return;

    // walk in TREE_LIST and get value nodes
    FOR_TREE_LIST2(list, types)
    {
        arr.push_back(static_cast<TypeNode*>(list->value));
    }
}

// find in TREE_LIST purpose with given label and get value
TreeListNode *findTreeListPurposeValue(TreeListNode *list,
                                       const std::string &name)
{
    FOR_TREE_LIST(list)
    {
        if (list->purpose && list->purpose->label == name)
        {
            return static_cast<TreeListNode*>(list->value);
        }
    }
    return nullptr;
}

void getFunctionParamsNonNullAttributes(FunctionDeclNode *node,
                                        std::set<int> &arr)
{
    // function not have type
    if (!node->functionType)
        return;
    TreeListNode *list = findTreeListPurposeValue(
        static_cast<TreeListNode*>(node->functionType->attribute),
        "nonnull");
    // no attribute nonnull
    if (!list)
        return;

    // get all labels from TREE_LIST and convert to int.
    // tree based on constants for attribute nonnull
    FOR_TREE_LIST(list)
    {
        if (list->value)
        {
            arr.insert(atoi(list->value->label.c_str()));
        }
    }
}

void analyseFunction(FunctionDeclNode *node, const WalkItem &wi, WalkItem &wo)
{
    // ignore external functions
    if (node->isExternal)
    {
        wo.stopWalking = true;
        return;
    }

    std::vector<TypeNode*> types;
    std::set<int> nonNull;
    WalkItem wi2 = wi;

    getFunctionArgTypes(node, types);
    getFunctionParamsNonNullAttributes(node, nonNull);
    // here need check is variables already present in wi2.checkNullVars

    if (command == Command::FindArgs)
        Log::log("%s: ", node->label.c_str());

    size_t sz = node->args.size();
    if (types.size() < sz)
        sz = types.size();
    for (int f = 0; f < sz; f ++)
    {
        const TypeNode *const type = types[f];
        if (!type || type->nodeType != POINTER_TYPE)
            continue;
        const ParmDeclNode *const name = node->args[f];
        if (nonNull.find(f + 1) == nonNull.end())
        {
            if (command == Command::FindArgs)
            {
                Log::log("%s %s, ",
                    type->nodeTypeName.c_str(),
                    name->label.c_str());
            }
            wi2.checkNullVars.insert(name->label);
        }
    }
    if (command == Command::FindArgs)
        Log::log("\n");

    if (!wi2.checkNullVars.empty())
    {
        walkTree(node->code, wi2, wo);
    }
    wo.stopWalking = true;
}

}
