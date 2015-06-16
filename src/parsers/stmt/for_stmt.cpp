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

parserDefine(ForStmt);

#include "parsers/base/expr.h"
#include "parsers/base/stmt.h"

#include "nodes/stmt/for_stmt.h"

namespace Generic
{

void parseForStmtNode(ForStmtNode *node)
{
    fillType(node);
    fillExprLocation(node);
    Log::dump(node);

    node->init = static_cast<StmtNode*>(createParseNode(
        node,
        FOR_INIT_STMT(node->gccNode),
        "init"));

    node->expression = static_cast<ExprNode*>(createParseNode(
        node,
        FOR_EXPR(node->gccNode),
        "expression"));

    node->condition = static_cast<ExprNode*>(createParseNode(
        node,
        FOR_COND(node->gccNode),
        "condition"));

    node->body = static_cast<StmtNode*>(createParseNode(
        node,
        FOR_BODY(node->gccNode),
        "body"));
}

}
