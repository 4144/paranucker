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

#include "includes/parserincludes.h"

parserDefine(CallExpr);

#include "parsers/base/expr.h"

#include "nodes/expr/call_expr.h"

#include "internal-fn.h"

namespace Generic
{

void parseCallExprNode(CallExprNode *node)
{
    fillType(node);
    fillExprLocation(node);
    Log::dump(node);

// not recommended
//    fillExprOperands(node);

    node->functionName = internal_fn_name(CALL_EXPR_IFN (node->gccNode));
    Log::dump(node, "- function: %s", node->functionName.c_str());
    const int argsCount = call_expr_nargs(node->gccNode);
    for (int f = 0; f < argsCount; f ++)
    {
        node->args.push_back(createParseNode(
            node,
            CALL_EXPR_ARG(node->gccNode, f),
            "arg"));
    }

    node->chain = createParseNode(
        node,
        CALL_EXPR_STATIC_CHAIN(node->gccNode),
        "chain");

    if (node->functionName == "LOAD_LANES")
        return;

    node->function = createParseNode(
        node,
        CALL_EXPR_FN(node->gccNode),
        "function");
}

}
