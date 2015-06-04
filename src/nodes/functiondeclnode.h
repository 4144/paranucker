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

#ifndef NODES_FUNCTIONDECLNODE_H
#define NODES_FUNCTIONDECLNODE_H

#include "nodes/functiontypenode.h"
#include "nodes/parmdeclnode.h"
#include "nodes/resultdeclnode.h"

#include "nodes/base/declnode.h"

#include <string>
#include <vector>

struct FunctionDeclNode : public DeclNode
{
    FunctionDeclNode() :
        DeclNode(),
        functionType(nullptr),
        result(nullptr),
        code(nullptr),
        target(nullptr),
        optimisation(nullptr),
        args(),
        isVirtual(false),
        isFinal(false),
        isConst(false),
        isPure(false),
        hasTargets(false)
    {
    }

    FunctionTypeNode *functionType;
    ResultDeclNode *result;
    Node *code;
    Node *target;
    Node *optimisation;
    std::vector<ParmDeclNode*> args;
    bool isVirtual;
    bool isFinal;
    bool isConst;
    bool isPure;
    bool hasTargets;
};

#endif // NODES_FUNCTIONDECLNODE_H
