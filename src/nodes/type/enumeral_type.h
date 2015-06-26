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

#ifndef NODES_TYPE_ENUMERALTYPENODE_H
#define NODES_TYPE_ENUMERALTYPENODE_H

#include "nodes/base/type.h"

#include "nodes/cst/integer_cst.h"

#include "nodes/list/tree_list.h"

#include <string>

struct EnumeralTypeNode : public TypeNode
{
    EnumeralTypeNode() :
        TypeNode(),
        minValue(nullptr),
        maxValue(nullptr),
        values(nullptr),
        precisionBits(0),
        isUnsigned(false)
    {
    }

    IntegerCstNode *minValue;
    IntegerCstNode *maxValue;
    TreeListNode *values;
    int precisionBits;
    bool isUnsigned;
};

#endif // NODES_TYPE_ENUMERALTYPENODE_H
