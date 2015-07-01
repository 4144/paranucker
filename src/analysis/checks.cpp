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

#include "analysis/checks.h"

#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/expression.h"
#include "analysis/reports.h"
#include "analysis/walkitem.h"

#include "nodes/cst/string_cst.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/call_expr.h"

#include <string>

#include "localconsts.h"

namespace Analysis
{

void getCallFunctionStringArgs(CallExprNode *node,
                               std::vector<std::string> &arr)
{
    FOR_EACH (it, node->args)
    {
        Node *arg = skipNop(it);
        if (arg == ADDR_EXPR)
        {
            AddrExprNode *addr = static_cast<AddrExprNode*>(arg);
            if (!addr->args.empty() && addr->args[0] == STRING_CST)
            {
                arr.push_back(addr->args[0]->label);
            }
        }
    }
}

std::string mergeCollection(const std::set<std::string> &col)
{
    std::string str;
    FOR_EACH(it, col)
    {
        str.append(it).append(",");
    }
    return str;
}

void reportCollections(Node *node,
                       const std::string &name,
                       std::set<std::string> col1,
                       std::set<std::string> col2)
{
    std::string str1 = mergeCollection(col1);
    std::string str2 = mergeCollection(col2);
    reportCollectionsDifferent(node, name, str1, str2);
}

void checkStateEqual(Node *node,
                     const std::string &name,
                     std::set<std::string> col1,
                     std::set<std::string> col2)
{
    FOR_EACH (it, col1)
    {
        if (isNotIn(it, col2))
        {
            reportCollections(node, name, col1, col2);
            return;
        }
    }
    FOR_EACH (it, col2)
    {
        if (isNotIn(it, col1))
        {
            reportCollections(node, name, col1, col2);
            return;
        }
    }
}

void checkStateIn(Node *node,
                  const std::string &name,
                  const std::set<std::string> &col1,
                  const std::set<std::string> &col2)
{
}

#define convertCollection(col) \
    if (name == #col) \
    { \
        return wi.col; \
    }

std::set<std::string> getCollection(Node *node,
                                    const std::string &name,
                                    const WalkItem &wi)
{
    convertCollection(needCheckNullVars)
    else convertCollection(knownVars)
    else convertCollection(knownNullVars)
    else convertCollection(knownNonNullVars)
    else convertCollection(removeNullVarsAll)
    else convertCollection(removeNullVars)
    else convertCollection(addNullVars)
    else convertCollection(checkedNullVars)
    else convertCollection(checkedNonNullVars)
    else
    {
        reportWrongCheck(node);
        return std::set<std::string>();
    }
}

std::set<std::string> splitArgs(std::string args)
{
    std::set<std::string> tokens;
    size_t idx = 0;
    while ((idx = args.find(" ")) != std::string::npos)
    {
        tokens.insert(args.substr(0, idx));
        args = args.substr(idx + 1);
    }
    if (!args.empty())
        tokens.insert(args);
    return tokens;
}

void checkState(CallExprNode *node, const WalkItem &wi)
{
    if (!node)
        return;

    std::vector<std::string> args;
    getCallFunctionStringArgs(node, args);
    if (args.size() != 3)
    {
        reportWrongCheck(node);
        return;
    }
    std::string name = args[1];
    std::set<std::string> col1 = getCollection(node, name, wi);
    std::set<std::string> col2 = splitArgs(args[2]);
    if (args[0] == "=")
        checkStateEqual(node, name, col1, col2);
    else if (args[1] == "in")
        checkStateIn(node, name, col1, col2);
    else
        reportWrongCheck(node);
}

}
