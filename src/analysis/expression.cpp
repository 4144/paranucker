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

#include "analysis/expression.h"

#include "command.h"
#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/walkitem.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/eq_expr.h"
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/ne_expr.h"
#include "nodes/expr/pointerplus_expr.h"
#include "nodes/expr/return_expr.h"
#include "nodes/expr/truthandif_expr.h"
#include "nodes/expr/truthorif_expr.h"

#include "nodes/ref/indirect_ref.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

void analyseModifyExpr(ModifyExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need atleast one arg for check
    if (node->args.empty() || command == FindArgs)
        return;

    Node *arg = skipNop(node->args[0]);
    if (arg && arg->nodeType == INDIRECT_REF)
    {
        reportParmDeclNullPointer(node,
            static_cast<IndirectRefNode*>(arg)->ref,
            wi);
    }
}

void analysePointerPlusExpr(PointerPlusExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need atleast one arg for check
    if (node->args.empty() || command == FindArgs)
        return;

    reportParmDeclNullPointer(node, node->args[0], wi);
}

void analyseAddrExpr(AddrExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need atleast one arg for check
    if (node->args.empty() || command == FindArgs)
        return;

    reportParmDeclNullPointer(node, node->args[0], wi);
}

void analyseReturnExpr(ReturnExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    wo.isReturned = true;
}

void analyseNeExpr(NeExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    //Log::dumpWI(node, "NE in ", wo);
    // PARM_DECL?
    Node *node1 = skipNop(node->args[0]);
    // INTEGER_CST?
    Node *node2 = skipNop(node->args[1]);

    // if (var != 0)
    if (node1 &&
        node2 &&
        node1->nodeType == PARM_DECL &&
        node2->nodeType == INTEGER_CST &&
        wi.checkNullVars.find(node1->label) != wi.checkNullVars.end() &&
        node2->label == "0")
    {
        wo.checkedNonNullVars.insert(node1->label);
        wo.cleanExpr = true;
        wo.uselessExpr = false;
    }
    else
    {
        wo.cleanExpr = false;
        wo.uselessExpr = true;
    }
    //Log::dumpWI(node, "NE out ", wo);
}

void analyseEqExpr(EqExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    //Log::dumpWI(node, "EQ in ", wo);
    // PARM_DECL?
    Node *node1 = skipNop(node->args[0]);
    // INTEGER_CST?
    Node *node2 = skipNop(node->args[1]);
    // if (var == 0)
    if (node1 &&
        node2 &&
        node1->nodeType == PARM_DECL &&
        node2->nodeType == INTEGER_CST &&
        wi.checkNullVars.find(node1->label) != wi.checkNullVars.end() &&
        node2->label == "0")
    {
        wo.checkedNullVars.insert(node1->label);
        wo.cleanExpr = true;
        wo.uselessExpr = false;
    }
    else
    {
        wo.cleanExpr = false;
        wo.uselessExpr = true;
    }
    //Log::dumpWI(node, "EQ out ", wo);
}

void analyseTruthOrIfExpr(TruthOrIfExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    //Log::dumpWI(node, "wo in ", wo);
    WalkItem wo1 = wo;
    WalkItem wo2 = wo;
    walkTree(node->args[0], wi, wo1);
    walkTree(node->args[1], wi, wo2);
    //Log::dumpWI(node, "wo1 ", wo1);
    //Log::dumpWI(node, "wo2 ", wo2);
    if (wo1.cleanExpr)
    {
        mergeNullChecked(wo, wo1);
        //mergeNonNullChecked(wo, wo1);
    }
    if (wo2.cleanExpr)
    {
        mergeNullChecked(wo, wo2);
        //mergeNonNullChecked(wo, wo2);
    }
    // need check for cleanExpr?
    intersectNonNullChecked(wo, wo1, wo2);

    wo.cleanExpr = false;
    wo.stopWalking = true;
    wo.uselessExpr = wo1.uselessExpr || wo2.uselessExpr;
    //Log::dumpWI(node, "wo out ", wo);
}

void analyseTruthAndIfExpr(TruthAndIfExprNode *node, const WalkItem &wi, WalkItem &wo)
{
    // need two args for check
    if (node->args.size() < 2 || command == FindArgs)
        return;

    //Log::dumpWI(node, "wo in ", wo);
    WalkItem wo1 = wo;
    walkTree(node->args[0], wi, wo1);
    WalkItem wo2 = wo1;
    walkTree(node->args[1], wo1, wo2);
    //Log::dumpWI(node, "wo1 ", wo1);
    //Log::dumpWI(node, "wo2 ", wo2);

    wo.stopWalking = true;
    if (!wo1.uselessExpr && !wo2.uselessExpr)
    {   // need combine wo1 and wo2
        // for now empty simple merge, but must be compilated!
        if (wo1.checkedNullVars == wo2.checkedNullVars)
        {
            wo.checkedNullVars.insert(wo2.checkedNullVars.begin(),
                wo2.checkedNullVars.end());
        }
        if (wo1.checkedNonNullVars == wo2.checkedNonNullVars)
        {
            wo.checkedNonNullVars.insert(wo2.checkedNonNullVars.begin(),
                wo2.checkedNonNullVars.end());
        }
        //intersectChecked(wo, wo1, wo2);
    }
    wo.cleanExpr = false;
    wo.uselessExpr = wo1.uselessExpr || wo2.uselessExpr;
    //Log::dumpWI(node, "wo out ", wo);
}

}
