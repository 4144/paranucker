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

// walking TREE_LIST and getting all types
void getTypesFromTreeList(TreeListNode *list,
                          std::vector<TypeNode*> &arr)
{
    while (list)
    {
        arr.push_back(static_cast<TypeNode*>(list->value));
        list = static_cast<TreeListNode*>(list->chain);
    }
}

// put arg types into arr
void getFunctionArgTypes(FunctionDeclNode *node,
                         std::vector<TypeNode*> &arr)
{
    // function not have type
    if (!node->functionType)
        return;
    getTypesFromTreeList(node->functionType->argTypes, arr);
}

TreeListNode *findTreeListPurposeValue(TreeListNode *list,
                                       const std::string &name)
{
    while (list)
    {
        if (list->purpose->label == name)
        {
            return static_cast<TreeListNode*>(list->value);
        }
        list = static_cast<TreeListNode*>(list->chain);
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
    while (list)
    {
        if (list->value)
        {
            arr.insert(atoi(list->value->label.c_str()));
        }
        list = static_cast<TreeListNode*>(list->chain);
    }
}

void analyseFunction(FunctionDeclNode *node)
{
    // ignore external functions
    if (node->isExternal)
        return;

    std::vector<TypeNode*> types;
    std::set<int> nonNull;

    getFunctionArgTypes(node, types);
    getFunctionParamsNonNullAttributes(node, nonNull);
    if (command == Command::FindArgs)
    {
        Log::log("%s: ", node->label.c_str());
        const int sz = node->args.size();
        for (int f = 0; f < sz; f ++)
        {
            const TypeNode *const type = types[f];
            const ParmDeclNode *const name = node->args[f];
            if (nonNull.find(f + 1) != nonNull.end())
            {
                Log::log("%s %s nonnull, ",
                    type->nodeTypeName.c_str(),
                    name->label.c_str());
            }
            else
            {
                Log::log("%s %s, ",
                    type->nodeTypeName.c_str(),
                    name->label.c_str());
            }
        }
        Log::log("\n");
    }
}

}
