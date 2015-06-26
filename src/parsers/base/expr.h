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

#ifndef PARSERS_BASE_EXPR_H
#define PARSERS_BASE_EXPR_H

#include <string>

struct ExprNode;
struct Node;

namespace Generic
{
    void fillExprLocation(Node *node);

    void fillExprOperands(ExprNode *node);

    Node *getExprOperand(ExprNode *node,
                         const int pos,
                         const std::string &tag);
}

#endif // PARSERS_BASE_EXPR_H
