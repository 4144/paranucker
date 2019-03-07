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

#include "analysis/expression.h"

#include "command.h"
#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/reports.h"
#include "analysis/varitem.h"
#include "analysis/walkitem.h"

#include "nodes/expr/addr_expr.h"
#include "nodes/expr/modify_expr.h"
#include "nodes/expr/pointerplus_expr.h"

#include "nodes/ref/array_ref.h"
#include "nodes/ref/component_ref.h"
#include "nodes/ref/indirect_ref.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

void analyseComponentRef(ComponentRefNode *node,
                         const WalkItem &wi,
                         WalkItem &wo A_UNUSED)
{
    // need atleast one arg for check
    if (!node->object || checkCommand(FindArgs))
        return;

/*
    Node *arg = skipNop(node->object);
    if (arg == INDIRECT_REF)
    {
        reportParmDeclNullPointer(node,
            static_cast<IndirectRefNode*>(arg)->ref,
            wi);
    }
*/
}

void analyseArrayRef(ArrayRefNode *node,
                     const WalkItem &wi,
                     WalkItem &wo A_UNUSED)
{
    // need atleast one arg for check
    if (node->args.empty() || checkCommand(FindArgs))
        return;

//    if (isIn("cell", wi.knownNonNullVars))
//        Log::log("cell ok1\n");
//    else
//        Log::log("cell not ok1\n");

//    Log::log("array start\n");
    FOR_EACH(it, node->args)
    {
        VarItem var = getVariableName(it);
        if (!var.isNonNull && isNotIn(var.name, wo.knownNonNullVars))
            reportParmDeclNullPointer(node, it, wi);
    }

//    if (isIn("cell", wi.knownNonNullVars))
//        Log::log("cell ok1\n");
//    else
//        Log::log("cell not ok1\n");

//    Log::log("array end\n");
}

}
