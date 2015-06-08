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

#include "nodes/decl/function_decl.h"

#include "localconsts.h"

namespace Analysis
{

void walkTree(Node *node)
{
    analyseNode(node);

    FOR_EACH (std::vector<Node*>::iterator, it, node->childs)
    {
        walkTree(*it);
    }
}

void analyseNode(Node *node)
{
    // searching function declaration
    if (node->nodeType == FUNCTION_DECL)
    {
        analyseFunction(static_cast<FunctionDeclNode*>(node));
    }
}

}
