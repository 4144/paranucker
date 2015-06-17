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

parserDefine(ComponentRef);

#include "parsers/base/ref.h"

#include "nodes/decl/field_decl.h"

#include "nodes/ref/component_ref.h"

namespace Generic
{

void parseComponentRefNode(ComponentRefNode *node)
{
    fillType(node);
    fillRefLocation(node);
    Log::dump(node);

    node->object = getRefOperand(node, 0, "object");
    node->field = static_cast<FieldDeclNode*>(
        getRefOperand(node, 1, "field"));

    // args 0 object
    // args 1 FIELD_DECL of member
    // args 2 offset, better use component_ref_field_offset
}

}
