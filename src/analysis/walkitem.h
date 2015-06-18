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
        checkedNullVars(),
        checkedNonNullVars(),
        stopWalking(false),
        isReturned(false),
        cleanExpr(false)
    {
    }

    WalkItem(const WalkItem &item) :
        checkNullVars(item.checkNullVars),
        removeNullVars(item.removeNullVars),
        checkedNullVars(item.checkedNullVars),
        checkedNonNullVars(item.checkedNonNullVars),
        stopWalking(item.stopWalking),
        isReturned(item.isReturned),
        cleanExpr(item.cleanExpr)
    {
    }

    std::set<std::string> checkNullVars;        // need check for usage without null pointer check
    std::set<std::string> removeNullVars;       // need remove vars from parent checkNullVars
    std::set<std::string> checkedNullVars;      // vars checked for null in expressions
    std::set<std::string> checkedNonNullVars;   // vars checked for nonnull in expressions
    bool stopWalking;   // stop walking on tree after this node
    bool isReturned;    // set if return present in child nodes
    bool cleanExpr;     // set if expression is only variable check without compound conditions
};


#endif // ANALYSIS_WALKITEM_H
