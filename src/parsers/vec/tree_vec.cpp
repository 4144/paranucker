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

#include "includes/parserincludes.h"

parserDefine(TreeVec);

#include "parsers/base/vec.h"

#include "nodes/vec/tree_vec.h"

namespace Generic
{

void parseTreeVecNode(TreeVecNode *node)
{
    fillType(node);
    Log::dump(node);

    const int sz = TREE_VEC_LENGTH(node->gccNode);
    for (int f = 0; f < sz; f ++)
    {
        node->args.push_back(createParseNode(
            node,
            TREE_VEC_ELT (node->gccNode, f),
            "element"));
    }
}

}
