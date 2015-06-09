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

#include "analysis/expression.h"

#include "command.h"
#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/walkitem.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/indirect_ref.h"
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/pointerplus_expr.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

WalkItem analyseModifyExpr(ModifyExprNode *node, WalkItem wi)
{
    // need atleast one arg for check
    if (node->args.empty() || command == FindArgs)
        return wi;

    Node *arg = node->args[0];
    if (arg->nodeType == INDIRECT_REF)
    {
        IndirectRefNode *refNode = static_cast<IndirectRefNode*>(arg);
        // need atleast one arg for check
        if (refNode->args.empty())
            return wi;
        arg = refNode->args[0];
        if (arg->nodeType == PARM_DECL)
        {
            if (wi.checkNullVars.find(arg->label) != wi.checkNullVars.end())
            {
                Log::warn(findBackLocation(node),
                    "Using variable without check for NULL");
            }
        }
    }

    return wi;
}

WalkItem analysePointerPlusExpr(PointerPlusExprNode *node, WalkItem wi)
{
    // need atleast one arg for check
    if (node->args.empty() || command == FindArgs)
        return wi;

    Node *arg = node->args[0];
    if (arg->nodeType == PARM_DECL)
    {
        if (wi.checkNullVars.find(arg->label) != wi.checkNullVars.end())
        {
            Log::warn(findBackLocation(node),
                "Using variable without check for NULL");
        }
    }

    return wi;
}

WalkItem analyseAddrExpr(AddrExprNode *node, WalkItem wi)
{
    // need atleast one arg for check
    if (node->args.empty() || command == FindArgs)
        return wi;

    Node *arg = node->args[0];
    if (arg->nodeType == PARM_DECL)
    {
        if (wi.checkNullVars.find(arg->label) != wi.checkNullVars.end())
        {
            Log::warn(findBackLocation(node),
                "Using variable without check for NULL");
        }
    }

    return wi;
}

}
