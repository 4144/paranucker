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

#ifndef ANALYSIS_ANALYSIS_H
#define ANALYSIS_ANALYSIS_H

#include "includes.h"

struct Node;
struct WalkItem;

namespace Analysis
{
    void startWalkTree(Node *node);

    void walkTree(Node *node, const WalkItem &wi, WalkItem &wo);

    void analyseNode(Node *node, const WalkItem &wi, WalkItem &wo);

    int findBackLocation(Node *node);

    void reportParmDeclNullPointer(Node *mainNode,
                                   Node *node,
                                   const WalkItem &wi);

    void removeCheckNullVars(WalkItem &wi);

    Node *skipNop(Node *node);

    void mergeNullChecked(WalkItem &wi1, WalkItem &wi2);

    void mergeNonNullChecked(WalkItem &wi1, WalkItem &wi2);

    void intersectNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2);

    void intersectNonNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2);
}

#endif // ANALYSIS_ANALYSIS_H
