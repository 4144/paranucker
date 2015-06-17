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

#ifndef ANALYSIS_WALKITEM_H
#define ANALYSIS_WALKITEM_H

#include <set>
#include <string>

struct WalkItem
{
    WalkItem() :
        checkNullVars(),
        removeNullVars(),
        stopWalking(false),
        isReturned(false),
        isExpr(false)
    {
    }

    WalkItem(const WalkItem &item) :
        checkNullVars(item.checkNullVars),
        removeNullVars(item.removeNullVars),
        stopWalking(item.stopWalking),
        isReturned(item.isReturned)
    {
    }

    std::set<std::string> checkNullVars;
    std::set<std::string> removeNullVars;
    bool stopWalking;   // stop walking on tree after this node
    bool isReturned;    // set if return present in child nodes
    bool isExpr;        // set if walking on expression for if other kind nodes
};


#endif // ANALYSIS_WALKITEM_H
