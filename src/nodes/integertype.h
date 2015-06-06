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

#ifndef NODES_INTEGERTYPENODE_H
#define NODES_INTEGERTYPENODE_H

#include "nodes/integercst.h"

#include "nodes/base/type.h"

#include <string>

struct IntegerTypeNode : public TypeNode
{
    IntegerTypeNode() :
        TypeNode(),
        typeSize(nullptr),
        minValue(nullptr),
        maxValue(nullptr),
        precisionBits(0),
        sizeBits(0),
        isChar(false),
        isUnsigned(false)
    {
    }

    IntegerCstNode *typeSize;
    IntegerCstNode *minValue;
    IntegerCstNode *maxValue;
    int precisionBits;
    int sizeBits;
    bool isChar;
    bool isUnsigned;
};

#endif // NODES_INTEGERTYPENODE_H
