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

void analyseVarDecl(VarDeclNode *node A_UNUSED,
                    const WalkItem &wi A_UNUSED,
                    WalkItem &wo A_UNUSED)
{
    // need atleast one arg for check
    if (command == FindArgs)
        return;

//    reportParmDeclNullPointer(node, node->initial, wi);
    return;
}

}
