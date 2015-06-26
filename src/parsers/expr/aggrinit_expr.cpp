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

#include "includes/parserincludes.h"

parserDefine(AggrInitExpr);

#include "parsers/base/expr.h"

#include "nodes/expr/aggrinit_expr.h"

namespace Generic
{

void parseAggrInitExprNode(AggrInitExprNode *node)
{
    fillType(node);
    fillExprLocation(node);
    Log::dump(node);

    //fillExprOperands(node);

#ifdef ENABLE_CXXLANG
    node->function = createParseNode(
        node,
        AGGR_INIT_EXPR_FN(node->gccNode),
        "function");
    node->slot = createParseNode(
        node,
        AGGR_INIT_EXPR_SLOT(node->gccNode),
        "slot");
    const int sz = aggr_init_expr_nargs(node->gccNode);
    for (int f = 0; f < sz; f ++)
    {
        node->args.push_back(createParseNode(
            node,
            AGGR_INIT_EXPR_ARG(node->gccNode, f),
            "arg"));
    }
#endif
}

}
