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

#include "logger.h"

#include "nodes/functiondeclnode.h"
#include "nodes/node.h"

#include "parsers/functiondeclnode.h"

#include "localconsts.h"

extern int plugin_is_GPL_compatible;

namespace Generic
{

Node *createEmptyNode(Node *parent, tree gccNode)
{
    if (gccNode == NULL_TREE)
    {
        return nullptr;
    }

    Node *node = nullptr;
    switch (TREE_CODE(gccNode))
    {
        case FUNCTION_DECL:
            node = new FunctionDeclNode;
            break;
        default:
            Log::log(parent, "Not supported node type: %s",
                get_tree_code_name(TREE_CODE(node->gccNode)));
            break;
    }
    return node;
}

void parseNode(Node *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }

    switch (TREE_CODE(node->gccNode))
    {
        case FUNCTION_DECL:
            parseFunctionDeclNode(node);
            break;
        default:
            Log::log(node, "Not supported node type: %s",
                get_tree_code_name(TREE_CODE(node->gccNode)));
            break;
    }
}

void parseNodes(tree gccNode)
{
    //Node *rootNode = new Node;
    Node *node = createEmptyNode(nullptr, gccNode);
    //node->parent = rootNode;
    node->gccNode = gccNode;
    parseNode(node);
}

void fillType(Node *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }

    node->treeNumber = static_cast<int>(TREE_CODE(node->gccNode));
    node->nodeType = get_tree_code_name(TREE_CODE(node->gccNode));
}

void fillLocation(Node *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }

    location_t loc = DECL_SOURCE_LOCATION(node->gccNode);
    node->file = LOCATION_FILE(loc);
    node->line = LOCATION_LINE(loc);
    node->column = LOCATION_COLUMN(loc);
}

}
