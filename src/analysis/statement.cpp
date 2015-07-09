/*
 *  Copyright (C) 2015  Andrei Karas
 *
 *  This file is part of Paranoid null checker.
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
#include "analysis/collections.h"
#include "analysis/reports.h"
#include "analysis/walkitem.h"

#include "nodes/expr/eq_expr.h"
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/ne_expr.h"
#include "nodes/expr/pointerplus_expr.h"

#include "nodes/ref/indirect_ref.h"

#include "nodes/stmt/if_stmt.h"
#include "nodes/stmt/while_stmt.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

void analyseCondition(Node *node,
                      Node *condNode,
                      Node *thenNode,
                      Node *elseNode,
                      const WalkItem &wi,
                      WalkItem &wo)
{
    condNode = skipNop(condNode);
    thenNode = skipNop(thenNode);
    elseNode = skipNop(elseNode);

    WalkItem wci = wi;
    WalkItem wco = wo;
    WalkItem wo2 = wo;
    WalkItem wo3 = wo;
    walkTree(condNode, wci, wco);
    Log::dumpWI(node, "wco ", wco);

    WalkItem wi2 = wi;
    if (wco.cleanExpr)
        removeNeedCheckNullVarsSetAll(wi2, wco.checkedThenNonNullVars);
    wi2.needCheckNullVars.insert(wco.checkedThenNullVars.begin(),
        wco.checkedThenNullVars.end());
    addKnownNullVarsWithLinked(wi2, wco, wco.checkedThenNullVars);
    addKnownNonNullVarsWithLinked(wi2, wco, wco.checkedThenNonNullVars);
    wi2.needCheckNullVars = wi2.knownVars;
    removeNeedCheckNullVarsSetAll(wi2, wi2.knownNonNullVars);
    wo2 = wi2;
    Log::dumpWI(node, "wi2 then ", wi2);

    reportParmDeclNullPointer(node,
        thenNode,
        wi2);
    walkTree(thenNode, wi2, wo2);
    Log::dumpWI(node, "wo2 then ", wo2);

    WalkItem wi3 = wi;
    if (wco.cleanExpr)
        removeNeedCheckNullVarsSetAll(wi3, wco.checkedElseNullVars);
    wi3.needCheckNullVars.insert(wco.checkedElseNonNullVars.begin(),
        wco.checkedElseNonNullVars.end());
    addKnownNullVarsWithLinked(wi3, wco, wco.checkedElseNullVars);
    addKnownNonNullVarsWithLinked(wi3, wco, wco.checkedElseNonNullVars);
    wi3.needCheckNullVars = wi3.knownVars;
    removeNeedCheckNullVarsSetAll(wi3, wi3.knownNonNullVars);

    wo3 = wi3;
    Log::dumpWI(node, "wi3 else ", wi3);

    reportParmDeclNullPointer(node,
        elseNode,
        wi3);
    walkTree(elseNode, wi3, wo3);
    Log::dumpWI(node, "wo3 else ", wo3);

    // probably condition wrong
    if (wo2.cleanExpr)
        mergeElseNullChecked(wo, wo2);
    // probably condition wrong
    if (wo3.cleanExpr)
        mergeElseNullChecked(wo, wo3);
    // need check for cleanExpr?
    intersectElseNonNullChecked(wo, wo2, wo3);

    if (wo2.isReturned)
    {
        // add variable for ignore for all parent nodes except special like IF_STMT
        FOR_EACH (it, wco.checkedElseNonNullVars)
        {
            wo.removeNullVarsAll.insert(it);
            removeNeedCheckNullVar(wo, it);
        }
        addKnownNonNullVarsWithLinked(wo, wco, wco.checkedElseNonNullVars);
        if (wco.cleanExpr)
        {
            addKnownNullVarsWithLinked(wo, wco, wco.checkedElseNullVars);
        }
    }
    else if (thenNode)
    {
        addNeedCheckNullVars2(wo2, wo);
    }
    if (wo3.isReturned)
    {
        // add variable for ignore for all parent nodes except special like IF_STMT
        FOR_EACH (it, wco.checkedThenNonNullVars)
        {
            wo.removeNullVarsAll.insert(it);
            removeNeedCheckNullVar(wo, it);
        }
        addKnownNonNullVarsWithLinked(wo, wco, wco.checkedThenNonNullVars);
        if (wco.cleanExpr)
        {
            addKnownNullVarsWithLinked(wo, wco, wco.checkedThenNullVars);
        }
    }
    else if (elseNode)
    {
        addNeedCheckNullVars2(wo3, wo);
    }
    if (wo2.isReturned && wo3.isReturned)
    {
        // add variable for ignore for all parent nodes except special like IF_STMT
        FOR_EACH (it, wo.knownVars)
        {
            wo.removeNullVarsAll.insert(it);
            wo.knownNullVars.erase(it);
            wo.knownNonNullVars.erase(it);
        }
    }

    wo.isReturned = false;
    wo.cleanExpr = true;
    wo.stopWalking = true;
    wo.uselessExpr = false;
}

void analyseIfStmt(IfStmtNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need condition node
    if (!node->condition || checkCommand(FindArgs))
        return;

    analyseCondition(node,
        node->condition,
        node->thenNode,
        node->elseNode,
        wi,
        wo);
}

void analyseWhileStmt(WhileStmtNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need condition node
    if (!node->condition || checkCommand(FindArgs))
        return;

    Node *condNode = skipNop(node->condition);
    Node *bodyNode = skipNop(node->body);
    if (!condNode)
        return;

    WalkItem wci = wi;
    WalkItem wco = wo;
    WalkItem wo2 = wo;

    walkTree(condNode, wci, wco);
    Log::dumpWI(node, "wco ", wco);

    WalkItem wi2 = wi;
    if (wco.cleanExpr)
        removeNeedCheckNullVarsSetAll(wi2, wco.checkedThenNonNullVars);
    addKnownNullVarsWithLinked(wi2, wco, wco.checkedThenNullVars);
    addKnownNonNullVarsWithLinked(wi2, wco, wco.checkedThenNonNullVars);
    wi2.needCheckNullVars = wi2.knownVars;
    enforceNeedCheckNullVars(wi2);
    removeNeedCheckNullVarsSetAll(wi2, wi2.knownNonNullVars);
    wo2 = wi2;
    Log::dumpWI(node, "wi2 body ", wi2);

    reportParmDeclNullPointer(node,
        bodyNode,
        wi2);
    walkTree(bodyNode, wi2, wo2);
    Log::dumpWI(node, "wo2 body ", wo2);

    if (wo2.cleanExpr)
        mergeElseNullChecked(wo, wo2);

    if (wo2.isReturned)
    {
        // add variable for ignore for all parent nodes except special like IF_STMT
        FOR_EACH (it, wco.checkedElseNonNullVars)
        {
            wo.removeNullVarsAll.insert(it);
            removeNeedCheckNullVar(wo, it);
        }
        addKnownNonNullVarsWithLinked(wo, wco, wco.checkedElseNonNullVars);
        if (wco.cleanExpr)
        {
            addKnownNullVarsWithLinked(wo, wco, wco.checkedElseNullVars);
        }
    }
    else if (bodyNode)
    {
        addNeedCheckNullVars2(wo2, wo);

        const Command oldCommand = command;
        disableCommand(DetectUseless);
        // after this wo2 changed for cond node
        addNeedCheckNullVars(wo2, wo2);
        wci = wo2;
        wco = wo2;
        walkTree(condNode, wci, wco);
        command = oldCommand;
        Log::dumpWI(node, "wco2 ", wco);
    }

    wo.isReturned = false;
    wo.cleanExpr = true;
    wo.stopWalking = true;
    wo.uselessExpr = false;
}

}
