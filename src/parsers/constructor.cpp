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

parserDefine(Constructor);


#include "nodes/constructor.h"

namespace Generic
{

void parseConstructorNode(ConstructorNode *node)
{
    fillType(node);
    Log::dump(node);

    node->constructorType = static_cast<TypeNode*>(createParseNode(
        node,
        TREE_TYPE(node->gccNode),
        "constructor type"));

    unsigned HOST_WIDE_INT cnt;
    tree index;
    tree value;
    FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (node->gccNode), cnt, index, value)
    {
        node->indexes.push_back(createParseNode(
            node,
            index,
            "index"));
        node->values.push_back(createParseNode(
            node,
            value,
            "value"));
    }
}

}
