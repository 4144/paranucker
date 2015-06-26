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

#ifndef NODES_BLOCKNODE_H
#define NODES_BLOCKNODE_H

#include "nodes/base/node.h"

#include "nodes/decl/var_decl.h"

#include <vector>

struct BlockNode : public Node
{
    BlockNode() :
        Node(),
        vars(),
        vars2(),
        blocks(),
        chain()
    {
    }

    std::vector<VarDeclNode*> vars;
    std::vector<Node*> vars2;
    std::vector<BlockNode*> blocks;
    std::vector<Node*> chain;
};

#endif // NODES_BLOCKNODE_H
