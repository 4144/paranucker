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

#include "parsers/base/ref.h"

#include "includes.h"

#include "nodes/base/ref.h"

#include "parsers/generic.h"

#include "localconsts.h"

namespace Generic
{

void fillRefLocation(Node *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }

    if (EXPR_HAS_LOCATION(node->gccNode))
    {
        location_t loc = EXPR_LOCATION(node->gccNode);
        node->location = loc;
        node->file = LOCATION_FILE(loc);
        node->line = LOCATION_LINE(loc);
        node->column = LOCATION_COLUMN(loc);
    }
}

void fillRefOperands(RefNode *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }
    const int sz = TREE_OPERAND_LENGTH(node->gccNode);
    for (int f = 0;f < sz; f ++)
    {
        node->args.push_back(createParseNode(
            node,
            TREE_OPERAND (node->gccNode, f),
            "operand"));
    }
}

Node *getRefOperand(RefNode *node,
                    const int pos,
                    const std::string &tag)
{
    if (!node || node->gccNode == NULL_TREE)
        return nullptr;
//    const int sz = TREE_OPERAND_LENGTH(node->gccNode);
//    if (sz >= pos)
//        return nullptr;

    return createParseNode(
        node,
        TREE_OPERAND (node->gccNode, pos),
        tag);
}

}
