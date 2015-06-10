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

#include "analysis/statement.h"

#include "command.h"
#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/walkitem.h"

#include "nodes/expr/eq_expr.h"
#include "nodes/expr/indirect_ref.h"
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/pointerplus_expr.h"

#include "nodes/stmt/if_stmt.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

WalkItem analyseIfStmt(IfStmtNode *node, WalkItem wi)
{
    // need condition node
    if (!node->condition || command == FindArgs)
        return wi;

    if (node->condition->nodeType == EQ_EXPR)
    {
        EqExprNode *eq = static_cast<EqExprNode*>(node->condition);
        // need atleast two operands for EQ_EXPR node
        if (eq->args.size() < 2)
            return wi;

        // PARM_DECL?
        Node *node1 = eq->args[0];
        // INTEGER_CST?
        Node *node2 = eq->args[1];
        // if (var == const)
        if (node1->nodeType == PARM_DECL &&
            node2->nodeType == INTEGER_CST &&
            wi.checkNullVars.find(node1->label) != wi.checkNullVars.end() &&
            node2->label == "0")
        {
            // found check for parameter and 0.
            // walking to then branch
            walkTree(node->thenNode, wi);
            // From else branch remove variable what we just found.
            wi.checkNullVars.erase(node1->label);
            walkTree(node->elseNode, wi);
            wi.stopWalking = true;

            // need aslo on parent remove variable too
            // probably wi should have pointer to parent
            return wi;
        }
    }

    return wi;
}

}
