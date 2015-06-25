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

parserDefine(VecInitExpr);

#include "parsers/base/expr.h"

#include "nodes/expr/vecinit_expr.h"

namespace Generic
{

void parseVecInitExprNode(VecInitExprNode *node)
{
    fillType(node);
    fillExprLocation(node);
    Log::dump(node);

#ifdef ENABLE_CXXLANG
    setPrintField(node, VEC_INIT_EXPR_IS_CONSTEXPR, isConstExpr);
#endif

    fillExprOperands(node);

    // args 0 slot
    // args 1 init
}

}
