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

parserDefine(TreeList);

#include "nodes/list/tree_list.h"

namespace Generic
{

void parseTreeListNode(TreeListNode *node)
{
    fillType(node);
    Log::dump(node);

    node->purpose = createParseNode(
        node,
        TREE_PURPOSE(node->gccNode),
        "purpose");

    node->value = createParseNode(
        node,
        TREE_VALUE(node->gccNode),
        "value");

/*
    present in tree.h as supported but really not working
    node->attribute = createParseNode(
        node,
        TYPE_ATTRIBUTES(node->gccNode),
        "attribute");
*/

    node->chain = static_cast<TreeListNode*>(createParseNode(
        node,
        TREE_CHAIN(node->gccNode),
        TREE_LIST,
        "chain"));

/* look like infinite loop
    FOR_CHAIN(node->gccNode, it, TREE_CHAIN, TREE_CHAIN)
    {
        if (node->gccNode == it)
            continue;
        createParseNode(
            node,
            it,
            node->tag);
    }
*/
}

}
