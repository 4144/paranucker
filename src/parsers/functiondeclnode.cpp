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

#include "localconsts.h"

namespace Generic
{

void parseFunctionDeclNode(Node *node)
{
    fillType(node);
    fillLocation(node);
    Log::log(node);
    Node *typeNode = createParseNode(node, TREE_TYPE(node->gccNode));
    Node *resultNode = createParseNode(node, DECL_RESULT(node->gccNode));
}

}
