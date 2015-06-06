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

#include "parsers/parserincludes.h"

parserDefine(IntegerType);

#include "parsers/base/type.h"

#include "nodes/integer_type.h"

namespace Generic
{

void parseIntegerTypeNode(IntegerTypeNode *node)
{
    fillType(node);
    Log::log(node);

    setPrintField(node, TYPE_PRECISION, precisionBits);
    setPrintField(node, TYPE_STRING_FLAG, isChar);
    node->isUnsigned = TYPE_UNSIGNED(node->gccNode);
    if (node->isUnsigned)
        Log::logRaw(node, "- unsigned");
    else
        Log::logRaw(node, "- signed");

    fillTypeName(node);
    fillTypeAttributes(node);
    node->typeSize = static_cast<IntegerCstNode*>(createParseNode(
        node,
        TYPE_SIZE(node->gccNode),
        INTEGER_CST,
        "type size"));
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
}

}
