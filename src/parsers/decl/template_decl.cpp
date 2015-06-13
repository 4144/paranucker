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

parserDefine(TemplateDecl);

#include "parsers/base/decl.h"

#include "nodes/decl/template_decl.h"

namespace Generic
{

void parseTemplateDeclNode(TemplateDeclNode *node)
{
    fillType(node);
    fillLocation(node);
    fillDeclLabel(node);
    Log::dump(node);

    fillDeclAutoGenerated(node);
    fillDeclAttributes(node);

    node->specializations = static_cast<TreeListNode*>(createParseNode(
        node,
        DECL_TEMPLATE_SPECIALIZATIONS(node->gccNode),
        TREE_LIST,
        "specialisation"));

    node->instantiations = static_cast<TreeListNode*>(createParseNode(
        node,
        DECL_TEMPLATE_INSTANTIATIONS(node->gccNode),
        TREE_LIST,
        "instantiations"));
}

}
