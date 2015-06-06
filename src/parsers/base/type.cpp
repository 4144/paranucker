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

#include "parsers/base/type.h"

#include "includes.h"
#include "logger.h"

#include "nodes/base/type.h"

#include "parsers/generic.h"

#include "localconsts.h"

namespace Generic
{

void fillTypeAttributes(TypeNode *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }
    node->attribute = createParseNode(
        node,
        TYPE_ATTRIBUTES(node->gccNode),
        "attribute");
}

void fillTypeName(TypeNode *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }
    node->typeName = static_cast<DeclNode*>(createParseNode(
        node,
        TYPE_NAME(node->gccNode),
        "type name"));
}

}
