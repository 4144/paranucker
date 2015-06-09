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

#include "analysis/analysis.h"

#include "command.h"

#include "analysis/function.h"
#include "analysis/walkitem.h"

#include "nodes/decl/function_decl.h"

#include "localconsts.h"

namespace Analysis
{

void startWalkTree(Node *node)
{
    walkTree(node, WalkItem());
}

void walkTree(Node *node, WalkItem wi)
{
    wi = analyseNode(node, wi);
    if (wi.stopWalking)
        return;

    FOR_EACH (std::vector<Node*>::iterator, it, node->childs)
    {
        walkTree(*it, wi);
    }
}

WalkItem analyseNode(Node *node, WalkItem wi)
{
    // searching function declaration
    if (node->nodeType == FUNCTION_DECL)
    {
        return analyseFunction(static_cast<FunctionDeclNode*>(node), wi);
    }
    return wi;
}

}