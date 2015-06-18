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
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/ne_expr.h"
#include "nodes/expr/pointerplus_expr.h"

#include "nodes/ref/indirect_ref.h"

#include "nodes/stmt/if_stmt.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

void analyseIfStmt(IfStmtNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need condition node
    if (!node->condition || command == FindArgs)
        return;

    Node *condNode = skipNop(node->condition);

    // for now for debug
    WalkItem wci = wi;
    WalkItem wco = wo;
    wci.isExpr = true;
    walkTree(condNode, wci, wco);
    Log::dumpWI(node, "wco ", wco);
    // for now for debug


    if (condNode->nodeType == EQ_EXPR)
    {   // if (... == ..)
        EqExprNode *eq = static_cast<EqExprNode*>(condNode);
        // need atleast two operands for EQ_EXPR node
        if (eq->args.size() < 2)
            return;

        // PARM_DECL?
        Node *node1 = skipNop(eq->args[0]);
        // INTEGER_CST?
        Node *node2 = skipNop(eq->args[1]);
        // if (var == 0)
        if (node1 &&
            node2 &&
            node1->nodeType == PARM_DECL &&
            node2->nodeType == INTEGER_CST &&
            wi.checkNullVars.find(node1->label) != wi.checkNullVars.end() &&
            node2->label == "0")
        {
            WalkItem wi2 = wi;
            // found check for parameter and 0.
            // walking to then branch
            walkTree(node->thenNode, wi2, wo);
            wo.removeNullVars.clear();
            const bool returned = wo.isReturned;
//            if (wo.isReturned)
//                Log::log("wo.isReturned 1\n");

            // From else branch remove variable what we just found.
            wi2 = wi;
            wi2.checkNullVars.erase(node1->label);
            walkTree(node->elseNode, wi2, wo);
            wo.removeNullVars.clear();
            wo.stopWalking = true;
//            if (wo.isReturned)
//                Log::log("wo.isReturned 2\n");
            wo.isReturned = false;

            if (returned)
            {
                //Log::log("add removeNullVars: %s\n", node1->label.c_str());
                // add variable for ignore for all parent nodes except special like IF_STMT
                wo.removeNullVars.insert(node1->label);
                wo.checkNullVars.erase(node1->label);
            }

            return;
        }
    }
    else if (condNode->nodeType == NE_EXPR)
    {   // if (... != ..)
        NeExprNode *ne = static_cast<NeExprNode*>(condNode);
        // need atleast two operands for NE_EXPR node
        if (ne->args.size() < 2)
            return;

        // PARM_DECL?
        Node *node1 = skipNop(ne->args[0]);
        // INTEGER_CST?
        Node *node2 = skipNop(ne->args[1]);
        // if (var != 0)
        if (node1 &&
            node2 &&
            node1->nodeType == PARM_DECL &&
            node2->nodeType == INTEGER_CST &&
            wi.checkNullVars.find(node1->label) != wi.checkNullVars.end() &&
            node2->label == "0")
        {
            // found check for parameter and 0.
            // walking to then branch
            WalkItem wi2 = wi;
            wi2.checkNullVars.erase(node1->label);
            // From then branch remove variable what we just found.
            walkTree(node->thenNode, wi2, wo);
//            if (wo.isReturned)
//                Log::log("wo.isReturned 3\n");
            wo.removeNullVars.clear();
            wi2 = wi;
            // walking else node with all variables
            walkTree(node->elseNode, wi2, wo);
//            if (wo.isReturned)
//                Log::log("wo.isReturned 4\n");
            wo.removeNullVars.clear();
            wo.stopWalking = true;

            if (wo.isReturned && node->elseNode)
            {
                //Log::log("add removeNullVars: %s\n", node1->label.c_str());
                // add variable for ignore for all parent nodes except special like IF_STMT
                wo.removeNullVars.insert(node1->label);
                wo.checkNullVars.erase(node1->label);
            }
            wo.isReturned = false;
            return;
        }
    }

    // default case
    walkTree(node->thenNode, wi, wo);
    walkTree(node->elseNode, wi, wo);
    wo.removeNullVars.clear();
//    if (wo.isReturned)
//        Log::log("wo.isReturned 5\n");
    wo.isReturned = false;
    wo.stopWalking = true;
}

}
