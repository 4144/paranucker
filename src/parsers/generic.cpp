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

#include "parsers/generic.h"

#include "nodes/create.h"
#include "nodes/node.h"

#include "parsers/functiondeclnode.h"

#include "localconsts.h"

extern int plugin_is_GPL_compatible;

namespace Generic
{

void parseNode(Node *parent,
               tree gccNode)
{
    if (!parent || gccNode == NULL_TREE)
    {
        return;
    }

    switch (TREE_CODE(gccNode))
    {
        case FUNCTION_DECL:
            parseFunctionDeclNode(parent, gccNode);
    }
}

void parseNodes(tree gccNode)
{
    Node *node = new Node;
    parseNode(node, gccNode);
}

void fillType(Node *node,
              tree gccNode)
{
    if (!node || gccNode == NULL_TREE)
    {
        return;
    }

    location_t loc = DECL_SOURCE_LOCATION(gccNode);
    node->treeNumber = static_cast<int>(TREE_CODE(gccNode));
    node->nodeType = get_tree_code_name(TREE_CODE(gccNode));
}

}
