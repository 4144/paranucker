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

parserDefine(RecordType);

#include "parsers/base/type.h"

#include "nodes/type/record_type.h"

namespace Generic
{

void parseRecordTypeNode(RecordTypeNode *node)
{
    fillType(node);
    Log::dump(node);

    fillTypeName(node);
    fillTypeAttributes(node);

    if (!node->parseChilds)
        return;

    FOR_CHAIN(node->gccNode, it, TYPE_FIELDS, DECL_CHAIN)
    {
        node->fields.push_back(static_cast<DeclNode*>(
            createParseNode(node, it, "field")));
    }
}

}
