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

#ifndef ANALYSIS_FUNCTION_H
#define ANALYSIS_FUNCTION_H

#include "includes.h"

#include <set>

struct FunctionDeclNode;
struct TreeListNode;
struct TypeNode;
struct WalkItem;

namespace Analysis
{
    void analyseFunction(FunctionDeclNode *node, const WalkItem &wi, WalkItem &wo);

    void getFunctionArgTypes(FunctionDeclNode *node,
                             std::vector<TypeNode*> &arr);

    void getFunctionParamsNonNullAttributes(FunctionDeclNode *node,
                                            std::set<int> &arr);

    TreeListNode *findFunctionDeclAttribute(FunctionDeclNode *node,
                                            const std::string &name);

    bool findTreeListPurpose(TreeListNode *list,
                             const std::string &name);
}

#endif // ANALYSIS_FUNCTION_H
