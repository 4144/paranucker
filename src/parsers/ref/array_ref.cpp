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

parserDefine(ArrayRef);

#include "parsers/base/ref.h"

#include "nodes/ref/array_ref.h"

#include "rtl.h"
#include "expr.h"

namespace Generic
{

void parseArrayRefNode(ArrayRefNode *node)
{
    fillType(node);
    fillRefLocation(node);
    Log::dump(node);

    node->lowBound = createParseNode(
        node,
        array_ref_low_bound(node->gccNode),
        "low bound");

    node->elementSize = createParseNode(
        node,
        array_ref_element_size(node->gccNode),
        "element size");

    fillRefOperands(node);

    // args 0 array
    // args 1 index
}

}
