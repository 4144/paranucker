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

#include "command.h"

#include "includes/nodeincludes.h"
#include "includes/parserincludes.h"
#include "includes/parserdefines.inc"

#include "localconsts.h"

int allocations = 0;

namespace Generic
{

Node *createParseNode(Node *parent,
                      tree gccNode,
                      std::string tag)
{
    return createParseNode(parent,
        gccNode,
        ERROR_MARK,
        tag);
}

Node *createParseNode(Node *parent,
                      tree gccNode,
                      tree_code wantType,
                      std::string tag)
{
    if (gccNode == NULL_TREE)
    {
        return nullptr;
    }

    Node *node = nullptr;
    switch (TREE_CODE(gccNode))
    {
#define handleNodeType(code, type) \
    case code: \
        node = new type##Node; \
        break;
#include "includes/nodeshandling.inc"
        default:
            Log::log(parent,
                1,
                "Not supported node type: %s - %s",
                get_tree_code_name(TREE_CODE(gccNode)),
                tag.c_str());
            break;
    }
    if (node)
    {
        node->parent = parent;
        node->gccNode = gccNode;
        if (parent)
        {
            node->indent  = parent->indent + 1;
            if (tag.empty())
                node->tag = parent->tag;
            else
                node->tag = tag;
            parent->childs.push_back(node);
        }
        else
        {
            node->tag = tag;
        }

        if (wantType != ERROR_MARK &&
            TREE_CODE(node->gccNode) != wantType)
        {
            if (tag.empty())
            {
                Log::log(node,
                    "Wrong node type. Want %s but get %s",
                    get_tree_code_name(wantType),
                    node->nodeType.c_str());
            }
            else
            {
                Log::log(node,
                    "Wrong node type. Want %s but get %s - %s",
                    get_tree_code_name(wantType),
                    node->nodeType.c_str(),
                    tag.c_str());
            }
            if (!parent)
                delete node;
            return nullptr;
        }

        switch (TREE_CODE(node->gccNode))
        {
#undef handleNodeType
#define handleNodeType(code, type) \
    case code: \
        parse##type##Node(static_cast<type##Node*>(node)); \
        break;
#include "includes/nodeshandling.inc"
            default:
                break;
        }
    }
    return node;
}

Node *parseNodes(tree gccNode)
{
    return createParseNode(nullptr, gccNode, FUNCTION_DECL);
}

void cleanAllNodes(Node *node)
{
    if (command == Command::MemoryUsage)
        Log::error("Allocations before cleanup: %d", allocations);
    cleanNodes(node);
    if (command == Command::MemoryUsage)
        Log::error("Allocations after cleanup: %d", allocations);
}

void cleanNodes(Node *node)
{
    FOR_EACH (std::vector<Node*>::iterator, it, node->childs)
    {
        cleanNodes(*it);
    }
    delete node;
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
