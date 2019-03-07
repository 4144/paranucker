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
        str.append("'").append(it).append("',");
    }
    return str;
}

void reportCollections(Node *node,
                       const std::string &name,
                       const std::set<std::string>& col1,
                       const std::set<std::string>& col2)
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
    else convertCollection(checkedThenNullVars)
    else convertCollection(checkedThenNonNullVars)
    else convertCollection(checkedElseNullVars)
    else convertCollection(checkedElseNonNullVars)
    else
    {
        reportWrongCheck(node);
        return std::set<std::string>();
    }
}

std::set<std::string> getLinkedCollection(Node *node,
                                          const std::string &name,
                                          const std::string &var,
                                          WalkItem wi)
{
    if (name == "linkedVars")
    {
        return wi.linkedVars[var];
    }
    else if (name == "linkedReverseVars")
    {
        std::set<std::string> tmpSet;
        if (isIn(var, wi.linkedReverseVars))
            tmpSet.insert(wi.linkedReverseVars[var]);
        return tmpSet;
    }
    else
    {
        reportWrongCheck(node);
        return std::set<std::string>();
    }
}

std::set<std::string> splitArgs(std::string args,
                                const int startIndex)
{
    std::set<std::string> tokens;
    size_t idx = 0;
    int cnt = 0;
    while ((idx = args.find(" ")) != std::string::npos)
    {
        if (cnt >= startIndex)
            tokens.insert(args.substr(0, idx));
        args = args.substr(idx + 1);
        cnt ++;
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
    std::set<std::string> col1;
    std::set<std::string> col2;
    if (name == "linkedVars" || name == "linkedReverseVars")
    {
        const size_t idx = args[2].find(" ");
        std::string var;
        if (idx == std::string::npos)
        {
            var = args[2];
            args[2] = std::string();
        }
        else
        {
            var = args[2].substr(0, idx);
            args[2] = args[2].substr(idx + 1);
        }
        col1 = getLinkedCollection(node, name, var, wi);
        col2 = splitArgs(args[2], 0);
    }
    else
    {
        col1 = getCollection(node, name, wi);
        if (isIn("this", col1))
        {
            col1.erase("this");
        }
        col2 = splitArgs(args[2], 0);
    }
    if (args[0] == "=")
        checkStateEqual(node, name, col1, col2);
    else if (args[1] == "in")
        checkStateIn(node, name, col1, col2);
    else
        reportWrongCheck(node);
}

}
