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

#ifndef NODES_TYPE_METHODTYPENODE_H
#define NODES_TYPE_METHODTYPENODE_H

#include "nodes/base/type.h"

#include "nodes/list/tree_list.h"

#include <string>

struct MethodTypeNode : public TypeNode
{
    MethodTypeNode() :
        TypeNode(),
        returnType(nullptr),
        methodBaseType(nullptr),
        argTypes(nullptr)
    {
    }

    TypeNode *returnType;
    TypeNode *methodBaseType;
    TreeListNode *argTypes;
};

#endif // NODES_TYPE_METHODTYPENODE_H
