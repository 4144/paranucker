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

#include "analysis/declaration.h"

#include "command.h"
#include "logger.h"

#include "analysis/analysis.h"
#include "analysis/walkitem.h"

#include "nodes/decl/var_decl.h"

#include <set>

#include "localconsts.h"

namespace Analysis
{

WalkItem analyseVarDecl(VarDeclNode *node, WalkItem wi)
{
    // need atleast one arg for check
    if (!node->initial || command == FindArgs)
        return wi;

    Node *initial = node->initial;
    if (initial->nodeType == PARM_DECL)
    {
        if (wi.checkNullVars.find(initial->label) != wi.checkNullVars.end())
        {
            Log::warn(findBackLocation(node),
                "Using variable without check for NULL");
        }
    }

    return wi;
}

}
