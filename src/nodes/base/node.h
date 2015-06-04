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

#ifndef NODES_BASE_NODE_H
#define NODES_BASE_NODE_H

#include "includes.h"

#include <string>

struct Node
{
    Node() :
        parent(nullptr),
        nodeType(),
        label(),
        file(),
        tag(),
        gccNode(nullptr),
        line(-1),
        column(-1),
        treeNumber(0),
        indent(0)
    {
    }

    std::string getIndent() const
    {
        std::string str;
        for (int f = 0; f < indent; f ++)
            str.append(" ");
        return str;
    }

    Node *parent;
    std::string nodeType;
    std::string label;
    std::string file;
    std::string tag;
    tree gccNode;
    int line;
    int column;
    int treeNumber;
    int indent;
};

#endif // NODES_BASE_NODE_H
