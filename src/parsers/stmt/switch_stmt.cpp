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

parserDefine(SwitchStmt);

#include "parsers/base/expr.h"
#include "parsers/base/stmt.h"

#include "nodes/stmt/switch_stmt.h"

namespace Generic
{

void parseSwitchStmtNode(SwitchStmtNode *node)
{
    fillType(node);
    fillExprLocation(node);
    Log::dump(node);

#ifdef ENABLE_CPPLANG
    node->condition = createParseNode(
        node,
        SWITCH_STMT_COND(node->gccNode),
        "condition");

    node->body = createParseNode(
        node,
        SWITCH_STMT_BODY(node->gccNode),
        "body");

    node->type = createParseNode(
        node,
        SWITCH_STMT_TYPE(node->gccNode),
        "type");

    node->scope = createParseNode(
        node,
        SWITCH_STMT_SCOPE(node->gccNode),
        "scope");
#endif
}

}
