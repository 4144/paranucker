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

#include "includes/parserincludes.h"

parserDefine(FunctionType);

#include "nodes/type/function_type.h"

#include "parsers/base/type.h"

namespace Generic
{

void parseFunctionTypeNode(FunctionTypeNode *node)
{
    fillType(node);
    Log::dump(node);

    node->returnType = static_cast<TypeNode*>(createParseNode(
        node,
        TREE_TYPE(node->gccNode),
        "function return type",
        node->parseChilds));

    fillTypeAttributes(node);

    if (!node->parseChilds)
        return;

    fillTypeName(node);
    node->argTypes = static_cast<TreeListNode*>(createParseNode(
        node,
        TYPE_ARG_TYPES(node->gccNode),
        TREE_LIST,
        "arg types"));
}

}
