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
#include "nodes/functiontypenode.h"

#include "parsers/functiondeclnode.h"
#include "parsers/functiontypenode.h"
#include "parsers/resultdeclnode.h"

#include "localconsts.h"

namespace Generic
{

Node *createParseNode(Node *parent, tree gccNode)
{
    return createParseNode(parent, gccNode, ERROR_MARK);
}

Node *createParseNode(Node *parent, tree gccNode, tree_code wantType)
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
        case FUNCTION_TYPE:
            node = new FunctionTypeNode;
            break;
        case RESULT_DECL:
            node = new Node;
            break;
        default:
            Log::log(parent, "Not supported node type: %s",
                get_tree_code_name(TREE_CODE(gccNode)));
            break;
    }
    if (node)
    {
        node->parent = parent;
        node->gccNode = gccNode;
        if (parent)
            node->indent  = parent->indent + 1;

        switch (TREE_CODE(node->gccNode))
        {
            case FUNCTION_DECL:
                parseFunctionDeclNode(static_cast<FunctionDeclNode*>(node));
                break;
            case FUNCTION_TYPE:
                parseFunctionTypeNode(node);
                break;
            case RESULT_DECL:
                parseResultDeclNode(node);
                break;
            default:
                break;
        }
        if (wantType != ERROR_MARK &&
            node->nodeType != get_tree_code_name(wantType))
        {
            Log::log(node, "Wrong node type. Want %s but get %s",
                get_tree_code_name(wantType),
                node->nodeType.c_str());
        }
    }
    return node;
}

void parseNodes(tree gccNode)
{
    createParseNode(nullptr, gccNode, FUNCTION_DECL);
}

void fillType(Node *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }

    node->treeNumber = static_cast<int>(TREE_CODE(node->gccNode));
    node->nodeType = get_tree_code_name(TREE_CODE(node->gccNode));
//    Log::log(node);
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
