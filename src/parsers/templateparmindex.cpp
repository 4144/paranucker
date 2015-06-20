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

parserDefine(TemplateParmIndex);


#include "nodes/templateparmindex.h"

namespace Generic
{

void parseTemplateParmIndexNode(TemplateParmIndexNode *node)
{
    fillType(node);
    Log::dump(node);

#ifdef ENABLE_CPPLANG
    setPrintField(node, TEMPLATE_PARM_IDX, parmIdx);
    setPrintField(node, TEMPLATE_PARM_LEVEL, parmLevel);
    setPrintField(node, TEMPLATE_PARM_ORIG_LEVEL, parmOrigLevel);
    setPrintField(node, TEMPLATE_PARM_PARAMETER_PACK, isParameterPack);

    node->descendants = createParseNode(
        node,
        TEMPLATE_PARM_DESCENDANTS(node->gccNode),
        "descendants");
    node->parmDecl = createParseNode(
        node,
        TEMPLATE_PARM_DECL(node->gccNode),
        "parm decl");
#endif
}

}
