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

#ifndef ANALYSIS_WALKITEM_H
#define ANALYSIS_WALKITEM_H

#include <map>
#include <set>
#include <string>

typedef std::set<std::string> StringSet;
typedef std::map<std::string, StringSet> StringMapSet;
typedef std::map<std::string, std::string> StringMap;

struct WalkItem
{
    WalkItem() :
        needCheckNullVars(),
        knownVars(),
        knownNullVars(),
        knownNonNullVars(),
        removeNullVarsAll(),
        removeNullVars(),
        addNullVars(),
        checkedThenNullVars(),
        checkedThenNonNullVars(),
        checkedElseNullVars(),
        checkedElseNonNullVars(),
        linkedVars(),
        linkedReverseVars(),
        stopWalking(false),
        isReturned(false),
        cleanExpr(false),
        uselessExpr(true)
    {
    }

    WalkItem(const WalkItem &item) :
        needCheckNullVars(item.needCheckNullVars),
        knownVars(item.knownVars),
        knownNullVars(item.knownNullVars),
        knownNonNullVars(item.knownNonNullVars),
        removeNullVarsAll(item.removeNullVarsAll),
        removeNullVars(item.removeNullVars),
        addNullVars(item.addNullVars),
        checkedThenNullVars(item.checkedThenNullVars),
        checkedThenNonNullVars(item.checkedThenNonNullVars),
        checkedElseNullVars(item.checkedElseNullVars),
        checkedElseNonNullVars(item.checkedElseNonNullVars),
        linkedVars(item.linkedVars),
        linkedReverseVars(item.linkedReverseVars),
        stopWalking(item.stopWalking),
        isReturned(item.isReturned),
        cleanExpr(item.cleanExpr),
        uselessExpr(item.uselessExpr)
    {
    }

    StringSet needCheckNullVars;     // need check for usage without null pointer check
    StringSet knownVars;             // known vars what can be checked or already checked
    StringSet knownNullVars;         // vars checked and it null
    StringSet knownNonNullVars;      // vars checked for null pointer
    StringSet removeNullVarsAll;     // need remove vars from parent checkNullVars with linked vars
    StringSet removeNullVars;        // need remove vars from parent checkNullVars without linked vars
    StringSet addNullVars;           // need add vars to parent checkNullVars
    StringSet checkedThenNullVars;   // vars checked for null in expressions for then case
    StringSet checkedThenNonNullVars;  // vars checked for nonnull in expressions for then case
    StringSet checkedElseNullVars;   // vars checked for null in expressions for else case
    StringSet checkedElseNonNullVars;  // vars checked for nonnull in expressions for else case
    StringMapSet linkedVars;         // linked vars. map <parent, set(vars)>
    StringMap linkedReverseVars;     // linked vars. map <child, parent>
    bool stopWalking;   // stop walking on tree after this node
    bool isReturned;    // set if return present in child nodes
    bool cleanExpr;     // set if expression is only variable check without compound conditions
    bool uselessExpr;   // set if some part of expression is unknown and not checking parameters
};


#endif // ANALYSIS_WALKITEM_H
