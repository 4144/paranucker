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

#include "analysis/analysis.h"

#include "analysis/walkitem.h"

#include "localconsts.h"

namespace Analysis
{

// add variables null pointer checks
void addNeedCheckNullVars(WalkItem &wi, WalkItem &wo)
{
    FOR_EACH (it, wi.addNullVars)
    {
        wo.needCheckNullVars.insert(it);
        wo.knownVars.insert(it);
    }
}

// remove one variable from null pointer checks
void removeNeedCheckNullVar(WalkItem &wi, std::string str)
{
    if (isIn(str, wi.needCheckNullVars))
    {
        wi.needCheckNullVars.erase(str);
    }
    if (isIn(str, wi.addNullVars))
    {
        wi.addNullVars.erase(str);
    }
    auto it2 = wi.linkedVars.find(str);
    if (it2 != wi.linkedVars.end())
    {
        const StringSet &linked = (*it2).second;
        FOR_EACH (it3, linked)
        {
            if (isIn(it3, wi.needCheckNullVars))
            {
                wi.needCheckNullVars.erase(it3);
            }
            if (isIn(it3, wi.addNullVars))
            {
                wi.addNullVars.erase(it3);
            }
        }
    }
}

// remove vars from checks for null pointer with linked vars
void removeNeedCheckNullVarsSetAll(WalkItem &wi, std::set<std::string> &vars)
{
    FOR_EACH (it, vars)
    {
        // remove var if need
        removeNeedCheckNullVar(wi, it);
        // if need remove some linked var, search it parent,
        // and remove all linked vars for this parent
        auto it3 = wi.linkedReverseVars.find(it);
        if (it3 != wi.linkedReverseVars.end())
        {
            const std::string parent = (*it3).second;
            //wi.linkedVars.erase(parent);
            removeNeedCheckNullVar(wi, parent);
        }
    }
}

// remove vars from checks for null pointer without linked vars
void removeNeedCheckNullVarsSet(WalkItem &wi, std::set<std::string> &vars)
{
    FOR_EACH (it, vars)
    {
        if (isIn(it, wi.needCheckNullVars))
        {
            wi.needCheckNullVars.erase(it);
        }
        if (isIn(it, wi.addNullVars))
        {
            wi.addNullVars.erase(it);
        }
        auto it2 = wi.linkedVars.find(it);
        if (it2 != wi.linkedVars.end())
        {
            const StringSet linked = (*it2).second;
            std::string newParent = *(linked.begin());
            wi.linkedVars[newParent] = linked;
            wi.linkedVars.erase(it);
            wi.linkedVars[newParent].erase(newParent);
        }
        auto it3 = wi.linkedReverseVars.find(it);
        if (it3 != wi.linkedReverseVars.end())
        {
            wi.linkedReverseVars.erase(it);
        }
    }
}

void addNullVar(WalkItem &wi,
                const std::string &var)
{
    wi.addNullVars.insert(var);
    wi.removeNullVars.erase(var);
}

// link var to parent. (type var = parent)
void addLinkedVar(WalkItem &wi,
                  std::string parent,
                  const std::string &var)
{
    if (isIn(parent, wi.addNullVars) ||
        isIn(parent, wi.needCheckNullVars))
    {
        wi.addNullVars.insert(var);
        wi.removeNullVars.erase(var);
    }
    if (isIn(parent, wi.removeNullVars))
    {
        wi.removeNullVars.insert(var);
        wi.addNullVars.erase(var);
    }
    if (isIn(parent, wi.knownNullVars))
    {
        wi.knownNullVars.insert(var);
        wi.knownNonNullVars.erase(var);
    }
    else if (isIn(parent, wi.knownNonNullVars))
    {
        wi.knownNonNullVars.insert(var);
        wi.knownNullVars.erase(var);
    }
    wi.knownVars.insert(var);

    // found parent as already linked var. need change parent to real parent
    if (isIn(parent, wi.linkedReverseVars))
        parent = wi.linkedReverseVars[parent];
    if (isNotIn(parent, wi.linkedVars))
        wi.linkedVars[parent] = std::set<std::string>();
    wi.linkedVars[parent].insert(var);
    wi.linkedReverseVars[var] = parent;
}

// merger two checked for null var sets
void mergeNullChecked(WalkItem &wi1, WalkItem &wi2)
{
    wi1.checkedNullVars.insert(wi2.checkedNullVars.begin(),
        wi2.checkedNullVars.end());
}

// merger two checked for non null var sets
void mergeNonNullChecked(WalkItem &wi1, WalkItem &wi2)
{
    wi1.checkedNonNullVars.insert(wi2.checkedNonNullVars.begin(),
        wi2.checkedNonNullVars.end());
}

// intersect two checked for null sets
void intersectNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2)
{
    FOR_EACH (it, wi1.checkedNullVars)
    {
        if (isIn(it, wi2.checkedNullVars))
            wi.checkedNullVars.insert(it);
    }
}

// intersect two checked for non null sets
void intersectNonNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2)
{
    FOR_EACH (it, wi1.checkedNonNullVars)
    {
        if (isIn(it, wi2.checkedNonNullVars))
            wi.checkedNonNullVars.insert(it);
    }
}

void removeFromNeedCheckNullVars(WalkItem &wi, std::set<std::string> &vars)
{
    FOR_EACH (it, vars)
    {
        wi.needCheckNullVars.erase(it);
    }
}

}
