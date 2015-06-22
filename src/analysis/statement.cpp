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

    WalkItem wci = wi;
    WalkItem wco = wo;
    walkTree(condNode, wci, wco);
    Log::dumpWI(node, "wco ", wco);

    WalkItem wi2 = wi;
    FOR_EACH (std::set<std::string>::const_iterator,
              it,
              wco.checkedNonNullVars)
    {
        wi2.checkNullVars.erase(*it);
    }
    std::set<std::string> tmpRemove = wo.removeNullVars;
    std::set<std::string> tmpAdd = wo.addNullVars;
    walkTree(node->thenNode, wi2, wo);

    wo.removeNullVars.clear();
    wo.addNullVars.clear();
    const bool returned = wo.isReturned;
    wo.isReturned = false;

    wi2 = wi;
    FOR_EACH (std::set<std::string>::const_iterator,
              it,
              wco.checkedNullVars)
    {
        wi2.checkNullVars.erase(*it);
    }
    walkTree(node->elseNode, wi2, wo);

    wo.removeNullVars = tmpRemove;
    wo.addNullVars = tmpAdd;

//    if (returned && wco.cleanExpr && !wco.uselessExpr)
    if (returned && !wco.uselessExpr)
    {
        // add variable for ignore for all parent nodes except special like IF_STMT
        FOR_EACH (std::set<std::string>::const_iterator,
                  it,
                  wco.checkedNullVars)
        {
            wo.removeNullVars.insert(*it);
            wo.checkNullVars.erase(*it);
        }
    }
//    if (wo.isReturned && wco.cleanExpr && !wco.uselessExpr)
    if (wo.isReturned && !wco.uselessExpr)
    {
        // add variable for ignore for all parent nodes except special like IF_STMT
        FOR_EACH (std::set<std::string>::const_iterator,
                  it,
                  wco.checkedNonNullVars)
        {
            wo.removeNullVars.insert(*it);
            wo.checkNullVars.erase(*it);
        }
    }

    // special case where all branches is ended.
    if (returned && wo.isReturned)
    {
        FOR_EACH (std::set<std::string>::const_iterator,
                  it,
                  wo.checkNullVars)
        {
            wo.removeNullVars.insert(*it);
        }
    }

    wo.stopWalking = true;
    wo.isReturned = false;
}

}
