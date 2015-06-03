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

#include "parsers/functiondeclnode.h"

#include "logger.h"

#include "parsers/generic.h"

#include "nodes/functiondeclnode.h"
#include "nodes/resultdeclnode.h"

#include "localconsts.h"

namespace Generic
{

void parseFunctionDeclNode(FunctionDeclNode *node)
{
    fillType(node);
    fillLocation(node);
    Log::log(node);
    node->functionType = static_cast<FunctionTypeNode*>(
        createParseNode(node, TREE_TYPE(node->gccNode), FUNCTION_TYPE));
    node->result = static_cast<ResultDeclNode*>(
        createParseNode(node, DECL_RESULT(node->gccNode), RESULT_DECL));
    FOR_CHAIN(node->gccNode, it)
    {
        node->args.push_back(static_cast<ParmDeclNode*>(
            createParseNode(node, it, PARM_DECL)));
    }
    node->code = createParseNode(node, DECL_SAVED_TREE(node->gccNode));
}

}
