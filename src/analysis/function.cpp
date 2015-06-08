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

#include "nodes/decl/function_decl.h"

#include "nodes/list/tree_list.h"

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

    // walk in TREE_LIST and get value nodes
    FOR_TREE_LIST2(list, node->functionType->argTypes)
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

void analyseFunction(FunctionDeclNode *node)
{
    // ignore external functions
    if (node->isExternal)
        return;

    std::vector<TypeNode*> types;
    std::set<int> nonNull;
    std::set<std::string> checkNames;

    getFunctionArgTypes(node, types);
    getFunctionParamsNonNullAttributes(node, nonNull);
    if (command == Command::FindArgs)
    {
        Log::log("%s: ", node->label.c_str());
        const int sz = node->args.size();
        for (int f = 0; f < sz; f ++)
        {
            const TypeNode *const type = types[f];
            if (type->nodeType != POINTER_TYPE)
                continue;
            const ParmDeclNode *const name = node->args[f];
            if (nonNull.find(f + 1) == nonNull.end())
            {
                Log::log("%s %s, ",
                    type->nodeTypeName.c_str(),
                    name->label.c_str());
                checkNames.insert(name->label);
            }
        }
        Log::log("\n");
    }
}

}
