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
#include "nodes/voidtypenode.h"

#include "parsers/function_decl.h"
#include "parsers/function_type.h"
#include "parsers/result_decl.h"
#include "parsers/void_type.h"

#include "localconsts.h"

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
        case FUNCTION_DECL:
            node = new FunctionDeclNode;
            break;
        case RESULT_DECL:
            node = new ResultDeclNode;
            break;
        case FUNCTION_TYPE:
            node = new FunctionTypeNode;
            break;
        case VOID_TYPE:
            node = new VoidTypeNode;
            break;
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
        }
        else
        {
            node->tag = tag;
        }

        switch (TREE_CODE(node->gccNode))
        {
            case FUNCTION_DECL:
                parseFunctionDeclNode(static_cast<FunctionDeclNode*>(node));
                break;
            case RESULT_DECL:
                parseResultDeclNode(static_cast<ResultDeclNode*>(node));
                break;
            case FUNCTION_TYPE:
                parseFunctionTypeNode(static_cast<FunctionTypeNode*>(node));
                break;
            case VOID_TYPE:
                parseVoidTypeNode(static_cast<VoidTypeNode*>(node));
                break;
            default:
                break;
        }
        if (wantType != ERROR_MARK &&
            node->nodeType != get_tree_code_name(wantType))
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
