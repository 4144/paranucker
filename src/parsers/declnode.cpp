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

#include "parsers/declnode.h"

#include "includes.h"
#include "logger.h"

#include "nodes/declnode.h"

#include "parsers/generic.h"

#include "localconsts.h"

namespace Generic
{

void fillDeclLabel(DeclNode *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }
    if (DECL_NAME(node->gccNode))
        node->label = IDENTIFIER_POINTER(DECL_NAME(node->gccNode));
}

void fillDeclAttributes(DeclNode *node)
{
    if (!node || node->gccNode == NULL_TREE)
    {
        return;
    }
    node->attribute = createParseNode(
        node,
        DECL_ATTRIBUTES(node->gccNode),
        "attribute");
}

}
