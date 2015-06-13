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

parserDefine(ArrayType);

#include "parsers/base/type.h"

#include "nodes/type/array_type.h"

namespace Generic
{

void parseArrayTypeNode(ArrayTypeNode *node)
{
    fillType(node);
    Log::dump(node);

    setPrintField(node, TYPE_STRING_FLAG, isString);

    fillTypeName(node);
    fillTypeAttributes(node);

    node->elementType = static_cast<TypeNode*>(createParseNode(
        node,
        TREE_TYPE(node->gccNode),
        "element type"));

    node->domain = static_cast<TypeNode*>(createParseNode(
        node,
        TYPE_DOMAIN(node->gccNode),
        "domain"));
    node->minIndex = static_cast<IntegerCstNode*>(createParseNode(
        node,
        TYPE_MIN_VALUE(node->gccNode),
        INTEGER_CST,
        "min index"));
    node->maxIndex = static_cast<IntegerCstNode*>(createParseNode(
        node,
        TYPE_MAX_VALUE(node->gccNode),
        INTEGER_CST,
        "max index"));
}

}
