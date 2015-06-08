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

parserDefine(IfStmt);

#include "parsers/base/stmt.h"

#include "nodes/stmt/if_stmt.h"

namespace Generic
{

void parseIfStmtNode(IfStmtNode *node)
{
    fillType(node);
    Log::dump(node);

    node->condition = createParseNode(
        node,
        IF_COND(node->gccNode),
        "condition");

    node->thenNode = createParseNode(
        node,
        THEN_CLAUSE(node->gccNode),
        "then");
    node->elseNode = createParseNode(
        node,
        ELSE_CLAUSE(node->gccNode),
        "else");
    node->score = createParseNode(
        node,
        IF_SCOPE(node->gccNode),
        "score");
}

}
