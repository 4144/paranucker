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
    WalkItem wi;
    WalkItem wo;
    walkTree(node, wi, wo);
}

void walkTree(Node *node, const WalkItem &wi, WalkItem &wo)
{
    if (!node)
        return;

    WalkItem wi2 = wi;
    analyseNode(node, wi2, wo);

    if (wo.stopWalking)
    {
        wo.stopWalking = false;
        return;
    }

    WalkItem wo2 = wo;
    FOR_EACH (std::vector<Node*>::iterator, it, node->childs)
    {
        wi2 = wi;
        walkTree(*it, wi2, wo2);
        wo2.stopWalking = false;
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

void analyseNode(Node *node, const WalkItem &wi, WalkItem &wo)
{
    if (!node)
        return;

    if (command == Command::DumpNullPointers)
    {
        Log::log("%s %s: ",
            node->nodeTypeName.c_str(),
            node->label.c_str());
        FOR_EACH (std::set<std::string>::const_iterator,
                  it,
                  wi.checkNullVars)
        {
            Log::log("%s, ", (*it).c_str());
        }
        Log::log("\n");
    }

    wo = wi;
    // searching function declaration
    switch (node->nodeType)
    {
        case FUNCTION_DECL:
            analyseFunction(static_cast<FunctionDeclNode*>(node), wi, wo);
            break;
        case ADDR_EXPR:
            analyseAddrExpr(static_cast<AddrExprNode*>(node), wi, wo);
            break;
        case MODIFY_EXPR:
            analyseModifyExpr(static_cast<ModifyExprNode*>(node), wi, wo);
            break;
        case POINTER_PLUS_EXPR:
            analysePointerPlusExpr(static_cast<PointerPlusExprNode*>(node), wi, wo);
            break;
        case VAR_DECL:
            analyseVarDecl(static_cast<VarDeclNode*>(node), wi, wo);
            break;
        case IF_STMT:
            analyseIfStmt(static_cast<IfStmtNode*>(node), wi, wo);
            break;
        default:
            break;
    }
}

}
