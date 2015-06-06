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

#include "nodes/functiondecl.h"
#include "nodes/functiontype.h"
#include "nodes/integertype.h"
#include "nodes/parmdecl.h"
#include "nodes/pointertype.h"
#include "nodes/voidtype.h"
#include "nodes/typedecl.h"
#include "nodes/identifier.h"
#include "nodes/integercst.h"
#include "nodes/returnexpr.h"
#include "nodes/statementlist.h"

#include "parsers/parserincludes.h"

parserDefine(FunctionDecl);
parserDefine(ParmDecl);
parserDefine(ResultDecl);
parserDefine(TypeDecl);

parserDefine(FunctionType);
parserDefine(IntegerType);
parserDefine(PointerType);
parserDefine(VoidType);

parserDefine(ReturnExpr);

parserDefine(TreeList);
parserDefine(Identifier);
parserDefine(IntegerCst);
parserDefine(StatementList);

#include "localconsts.h"

#define createNodeType(code, type) \
    case code: \
        node = new type; \
        break

#define parseNodeType(code, type) \
    case code: \
        parse##type##Node(static_cast<type##Node*>(node)); \
        break


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
        createNodeType(FUNCTION_DECL, FunctionDeclNode);
        createNodeType(PARM_DECL, ParmDeclNode);
        createNodeType(RESULT_DECL, ResultDeclNode);
        createNodeType(TYPE_DECL, TypeDeclNode);
        createNodeType(FUNCTION_TYPE, FunctionTypeNode);
        createNodeType(INTEGER_TYPE, IntegerTypeNode);
        createNodeType(VOID_TYPE, VoidTypeNode);
        createNodeType(POINTER_TYPE, PointerTypeNode);
        createNodeType(RETURN_EXPR, ReturnExprNode);
        createNodeType(TREE_LIST, TreeListNode);
        createNodeType(IDENTIFIER_NODE, IdentifierNode);
        createNodeType(INTEGER_CST, IntegerCstNode);
        createNodeType(STATEMENT_LIST, StatementListNode);
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
            parseNodeType(FUNCTION_DECL, FunctionDecl);
            parseNodeType(PARM_DECL, ParmDecl);
            parseNodeType(RESULT_DECL, ResultDecl);
            parseNodeType(TYPE_DECL, TypeDecl);
            parseNodeType(FUNCTION_TYPE, FunctionType);
            parseNodeType(INTEGER_TYPE, IntegerType);
            parseNodeType(VOID_TYPE, VoidType);
            parseNodeType(POINTER_TYPE, PointerType);
            parseNodeType(RETURN_EXPR, ReturnExpr);
            parseNodeType(TREE_LIST, TreeList);
            parseNodeType(IDENTIFIER_NODE, Identifier);
            parseNodeType(INTEGER_CST, IntegerCst);
            parseNodeType(STATEMENT_LIST, StatementList);
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
