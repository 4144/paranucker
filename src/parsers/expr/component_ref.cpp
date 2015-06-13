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

#include "parsers/base/expr.h"

#include "nodes/decl/field_decl.h"

#include "nodes/expr/component_ref.h"

namespace Generic
{

void parseComponentRefNode(ComponentRefNode *node)
{
    fillType(node);
    Log::dump(node);

    fillExprOperands(node);

    node->object = getExprOperand(node, 0, "object");
    node->field = static_cast<FieldDeclNode*>(
        getExprOperand(node, 1, "field"));

    // args 0 object
    // args 1 FIELD_DECL of member
    // args 2 offset, better use component_ref_field_offset
}

}
