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

#ifndef PARSERS_GENERIC_H
#define PARSERS_GENERIC_H

#include "includes.h"

#include <string>

struct Node;

namespace Generic
{
    void parseNodes(tree gccNode);

    void parseNode(Node *parent);

    void fillType(Node *node);

    void fillLocation(Node *node);

    Node *createParseNode(Node *parent, tree gccNode);
}

#endif // PARSERS_GENERIC_H
