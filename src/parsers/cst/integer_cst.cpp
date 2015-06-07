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

#include "includes/parserincludes.h"

#include "stringutils.h"

parserDefine(IntegerCst);

#include "nodes/cst/integer_cst.h"

#include <stdio.h>
#include <stdlib.h>

namespace Generic
{

void parseIntegerCstNode(IntegerCstNode *node)
{
    fillType(node);
    if (!tree_fits_shwi_p(node->gccNode))
    {
        node->noLabel = true;
        return;
    }
    if (tree_int_cst_sgn(node->gccNode) < 0)
    {
        node->label = "-";
        node->label.append(toString(-(unsigned HOST_WIDE_INT)
            tree_to_shwi(node->gccNode)));
    }
    else
    {
        node->label.append(toString(tree_to_shwi(node->gccNode)));
    }
    Log::log(node);
}

}
