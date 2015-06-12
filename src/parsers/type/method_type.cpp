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

parserDefine(MethodType);

#include "parsers/base/type.h"

#include "nodes/type/method_type.h"

namespace Generic
{

void parseMethodTypeNode(MethodTypeNode *node)
{
    fillType(node);
    Log::dump(node);

    fillTypeName(node);
    node->returnType = static_cast<TypeNode*>(createParseNode(
        node,
        TREE_TYPE(node->gccNode),
        "method return type"));
    fillTypeAttributes(node);

    node->methodBaseType = static_cast<TypeNode*>(createParseNode(
        node,
        TYPE_METHOD_BASETYPE(node->gccNode),
        "method base type"));

    node->argTypes = static_cast<TreeListNode*>(createParseNode(
        node,
        TYPE_ARG_TYPES(node->gccNode),
        TREE_LIST,
        "arg types"));
}

}
