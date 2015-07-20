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

#ifndef ANALYSIS_STATEMENT_H
#define ANALYSIS_STATEMENT_H

#include "includes.h"

struct BreakStmtNode;
struct ContinueStmtNode;
struct IfStmtNode;
struct Node;
struct WalkItem;
struct WhileStmtNode;

namespace Analysis
{
    void analyseCondition(Node *node,
                          Node *condNode,
                          Node *thenNode,
                          Node *elseNode,
                          const WalkItem &wi,
                          WalkItem &wo);

    void analyseIfStmt(IfStmtNode *node,
                       const WalkItem &wi,
                       WalkItem &wo);

    void analyseWhileStmt(WhileStmtNode *node,
                          const WalkItem &wi,
                          WalkItem &wo);

    void analyseBreakStmt(BreakStmtNode *node,
                          const WalkItem &wi,
                          WalkItem &wo);

    void analyseContinueStmt(ContinueStmtNode *node,
                             const WalkItem &wi,
                             WalkItem &wo);
}

#endif // ANALYSIS_STATEMENT_H
