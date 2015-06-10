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

#include "analysis/analysis.h"

#include "command.h"
#include "logger.h"

#include "analysis/declaration.h"
#include "analysis/expression.h"
#include "analysis/function.h"
#include "analysis/statement.h"
#include "analysis/walkitem.h"

#include "nodes/decl/function_decl.h"
#include "nodes/decl/var_decl.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/pointerplus_expr.h"

#include "nodes/stmt/if_stmt.h"

#include "localconsts.h"

namespace Analysis
{

void startWalkTree(Node *node)
{
    walkTree(node, WalkItem());
}

void walkTree(Node *node, WalkItem wi)
{
    if (!node)
        return;

    wi = analyseNode(node, wi);

    if (wi.stopWalking)
        return;

    FOR_EACH (std::vector<Node*>::iterator, it, node->childs)
    {
        walkTree(*it, wi);
    }
}

int findBackLocation(Node *node)
{
    location_t loc = 0;
    while(node && !loc)
    {
        loc = node->location;
        node = node->parent;
    }
    return loc;
}

WalkItem analyseNode(Node *node, WalkItem wi)
{
    if (!node)
        return wi;

    if (command == Command::DumpNullPointers)
    {
        Log::log("%s %s\n",
            node->nodeTypeName.c_str(),
            node->label.c_str());
    }

    // searching function declaration
    switch (node->nodeType)
    {
        case FUNCTION_DECL:
            return analyseFunction(static_cast<FunctionDeclNode*>(node), wi);
        case ADDR_EXPR:
            return analyseAddrExpr(static_cast<AddrExprNode*>(node), wi);
        case MODIFY_EXPR:
            return analyseModifyExpr(static_cast<ModifyExprNode*>(node), wi);
        case POINTER_PLUS_EXPR:
            return analysePointerPlusExpr(static_cast<PointerPlusExprNode*>(node), wi);
        case VAR_DECL:
            return analyseVarDecl(static_cast<VarDeclNode*>(node), wi);
        case IF_STMT:
            return analyseIfStmt(static_cast<IfStmtNode*>(node), wi);
        default:
            break;
    }
    return wi;
}

}
