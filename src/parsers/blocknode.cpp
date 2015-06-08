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

parserDefine(BlockNode);

#include "nodes/blocknode.h"

namespace Generic
{

void parseBlockNode(BlockNode *node)
{
    fillType(node);
    location_t loc = BLOCK_SOURCE_LOCATION(node->gccNode);
    if (loc)
    {
        node->file = LOCATION_FILE(loc);
        node->line = LOCATION_LINE(loc);
        node->column = LOCATION_COLUMN(loc);
    }
    Log::dump(node);

    FOR_CHAIN(node->gccNode, it, BLOCK_VARS, DECL_CHAIN)
    {
        node->vars.push_back(static_cast<VarDeclNode*>(createParseNode(
            node,
            it,
            VAR_DECL,
            "block vars")));
    }

    const int sz = BLOCK_NUM_NONLOCALIZED_VARS(node->gccNode);
    for (int f = 0; f < sz; f ++)
    {
        node->vars2.push_back(createParseNode(
            node,
            BLOCK_NONLOCALIZED_VAR(node->gccNode, f),
            "nonlocalized block var"));
    }

    FOR_CHAIN(node->gccNode, it, BLOCK_SUBBLOCKS, BLOCK_CHAIN)
    {
        node->blocks.push_back(static_cast<BlockNode*>(createParseNode(
            node,
            it,
            BLOCK,
            "sub block")));
    }

    FOR_CHAIN(node->gccNode, it, BLOCK_CHAIN, BLOCK_CHAIN)
    {
        node->chain.push_back(createParseNode(
            node,
            it,
            "block chain"));
    }

    FOR_CHAIN(node->gccNode, it, BLOCK_FRAGMENT_CHAIN, BLOCK_FRAGMENT_CHAIN)
    {
        (createParseNode(
            node,
            it,
            BLOCK,
            "block fragment chain"));
    }

/*
    parent function
    createParseNode(
        node,
        BLOCK_SUPERCONTEXT(node->gccNode),
        "super context");
*/
}

}
