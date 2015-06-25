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

parserDefine(TryBlock);

#include "parsers/base/expr.h"

#include "nodes/block/try_block.h"

namespace Generic
{

void parseTryBlockNode(TryBlockNode *node)
{
    fillType(node);
    fillExprLocation(node);
    Log::dump(node);

#ifdef ENABLE_CXXLANG
    setPrintField(node, CLEANUP_P, isClean);

    node->body = createParseNode(
        node,
        TRY_STMTS(node->gccNode),
        "body");

    node->handler = createParseNode(
        node,
        TRY_HANDLERS(node->gccNode),
        "handler");
#endif
}

}
