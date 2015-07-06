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

parserDefine(EnumeralType);

#include "parsers/base/type.h"

#include "nodes/type/enumeral_type.h"

namespace Generic
{

void parseEnumeralTypeNode(EnumeralTypeNode *node)
{
    fillType(node);
    Log::dump(node);

    setPrintField(node, TYPE_PRECISION, precisionBits);
    node->isUnsigned = TYPE_UNSIGNED(node->gccNode);
    if (node->isUnsigned)
        Log::dumpRaw(node, "- unsigned");
    else
        Log::dumpRaw(node, "- signed");

    if (!node->parseChilds)
        return;

    fillTypeName(node);
    fillTypeAttributes(node);

    node->minValue = static_cast<IntegerCstNode*>(createParseNode(
        node,
        TYPE_MIN_VALUE(node->gccNode),
        INTEGER_CST,
        "min value"));
    node->maxValue = static_cast<IntegerCstNode*>(createParseNode(
        node,
        TYPE_MAX_VALUE(node->gccNode),
        INTEGER_CST,
        "max value"));
    node->values = static_cast<TreeListNode*>(createParseNode(
        node,
        TYPE_VALUES(node->gccNode),
        TREE_LIST,
        "values"));
}

}
