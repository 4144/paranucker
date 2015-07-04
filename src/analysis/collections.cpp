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

#include "logger.h"

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

void removeNeedCheckNullVarOnly(WalkItem &wi, const std::string &var)
{
    if (isIn(var, wi.needCheckNullVars))
    {
        wi.needCheckNullVars.erase(var);
    }
    if (isIn(var, wi.addNullVars))
    {
        wi.addNullVars.erase(var);
    }
    auto it2 = wi.linkedVars.find(var);
    if (it2 != wi.linkedVars.end())
    {
        const StringSet linked = (*it2).second;
        std::string newParent = *(linked.begin());
        wi.linkedReverseVars.erase(newParent);
        wi.linkedVars[newParent] = linked;
        wi.linkedVars.erase(var);
        wi.linkedVars[newParent].erase(newParent);
        if (wi.linkedVars[newParent].empty())
        {
            wi.linkedVars.erase(newParent);
        }
        else
        {
            const StringSet &linked2 = wi.linkedVars[newParent];
            FOR_EACH (it3, linked2)
            {
                wi.linkedReverseVars[it3] = newParent;
            }
        }
    }
    if (isIn(var, wi.linkedReverseVars))
    {
        std::string parent = wi.linkedReverseVars[var];
        wi.linkedVars[parent].erase(var);
        if (wi.linkedVars[parent].empty())
            wi.linkedVars.erase(parent);
    }
    wi.linkedReverseVars.erase(var);
}

// remove vars from checks for null pointer without linked vars
void removeNeedCheckNullVarsSet(WalkItem &wi, std::set<std::string> &vars)
{
    FOR_EACH (it, vars)
    {
        removeNeedCheckNullVarOnly(wi, it);
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
    //Log::log("add var\n");
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

    if (isIn(var, wi.linkedReverseVars))
    {
        std::string oldParent = wi.linkedReverseVars[var];
        wi.linkedVars[oldParent].erase(var);
        if (wi.linkedVars.empty())
            wi.linkedVars.erase(oldParent);
    }

    // found parent as already linked var. need change parent to real parent
    if (isIn(parent, wi.linkedReverseVars))
        parent = wi.linkedReverseVars[parent];
    if (isNotIn(parent, wi.linkedVars))
        wi.linkedVars[parent] = std::set<std::string>();
    wi.linkedVars[parent].insert(var);
    wi.linkedReverseVars[var] = parent;

    // found what variable have linked vars to it.
    // Need move all this vars to new parent.
    if (isIn(var, wi.linkedVars))
    {
        StringSet linked = wi.linkedVars[var];
        std::string newParent = *(linked.begin());
        wi.linkedReverseVars.erase(newParent);
        wi.linkedVars[newParent] = linked;
        wi.linkedVars.erase(var);
        wi.linkedVars[newParent].erase(newParent);
        if (wi.linkedVars[newParent].empty())
        {
            wi.linkedVars.erase(newParent);
        }
        else
        {
            const StringSet &linked2 = wi.linkedVars[newParent];
            FOR_EACH (it3, linked2)
            {
                wi.linkedReverseVars[it3] = newParent;
            }
        }
/*
        StringSet oldLinked = wi.linkedVars[var];
        wi.linkedVars.erase(var);
        wi.linkedVars[parent].insert(oldLinked.begin(),
            oldLinked.end());
        FOR_EACH (it, oldLinked)
        {
            wi.linkedReverseVars[it] = parent;
        }
*/
    }
}

// merger two checked for null var sets
void mergeThenNullChecked(WalkItem &wi1, WalkItem &wi2)
{
    wi1.checkedThenNullVars.insert(wi2.checkedThenNullVars.begin(),
        wi2.checkedThenNullVars.end());
}

// merger two checked for null var sets
void mergeElseNullChecked(WalkItem &wi1, WalkItem &wi2)
{
    wi1.checkedElseNullVars.insert(wi2.checkedElseNullVars.begin(),
        wi2.checkedElseNullVars.end());
}

// merger two checked for non null var sets
void mergeThenNonNullChecked(WalkItem &wi1, WalkItem &wi2)
{
    wi1.checkedThenNonNullVars.insert(wi2.checkedThenNonNullVars.begin(),
        wi2.checkedThenNonNullVars.end());
}

// merger two checked for non null var sets
void mergeElseNonNullChecked(WalkItem &wi1, WalkItem &wi2)
{
    wi1.checkedElseNonNullVars.insert(wi2.checkedElseNonNullVars.begin(),
        wi2.checkedElseNonNullVars.end());
}

// intersect two checked for null sets
void intersectThenNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2)
{
    FOR_EACH (it, wi1.checkedThenNullVars)
    {
        if (isIn(it, wi2.checkedThenNullVars))
            wi.checkedThenNullVars.insert(it);
    }
}

// intersect two checked for null sets
void intersectElseNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2)
{
    FOR_EACH (it, wi1.checkedElseNullVars)
    {
        if (isIn(it, wi2.checkedElseNullVars))
            wi.checkedElseNullVars.insert(it);
    }
}

// intersect two checked for non null sets
void intersectThenNonNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2)
{
    FOR_EACH (it, wi1.checkedThenNonNullVars)
    {
        if (isIn(it, wi2.checkedThenNonNullVars))
            wi.checkedThenNonNullVars.insert(it);
    }
}

// intersect two checked for non null sets
void intersectElseNonNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2)
{
    FOR_EACH (it, wi1.checkedElseNonNullVars)
    {
        if (isIn(it, wi2.checkedElseNonNullVars))
            wi.checkedElseNonNullVars.insert(it);
    }
}

void removeFromNeedCheckNullVars(WalkItem &wi, std::set<std::string> &vars)
{
    FOR_EACH (it, vars)
    {
        wi.needCheckNullVars.erase(it);
    }
}

void addKnownNullVarsWithLinked(WalkItem &wo, WalkItem &wi, std::set<std::string> &vars)
{
    wo.knownNullVars.insert(vars.begin(),
        vars.end());
    FOR_EACH (it, vars)
    {
        auto it2 = wi.linkedVars.find(it);
        if (it2 == wi.linkedVars.end() && isIn(it, wi.linkedReverseVars))
        {
            wo.knownNullVars.insert(wi.linkedReverseVars[it]);
            it2 = wi.linkedVars.find(wi.linkedReverseVars[it]);
        }
        if (it2 != wi.linkedVars.end())
        {
            const StringSet &linked = (*it2).second;
            wo.knownNullVars.insert(linked.begin(), linked.end());
        }
    }
}

void addKnownNonNullVarsWithLinked(WalkItem &wo, WalkItem &wi, std::set<std::string> &vars)
{
    wo.knownNonNullVars.insert(vars.begin(),
        vars.end());
    FOR_EACH (it, vars)
    {
        auto it2 = wi.linkedVars.find(it);
        if (it2 == wi.linkedVars.end() && isIn(it, wi.linkedReverseVars))
        {
            wo.knownNonNullVars.insert(wi.linkedReverseVars[it]);
            it2 = wi.linkedVars.find(wi.linkedReverseVars[it]);
        }
        if (it2 != wi.linkedVars.end())
        {
            const StringSet &linked = (*it2).second;
            wo.knownNonNullVars.insert(linked.begin(), linked.end());
        }
    }
}

void removeVar(WalkItem &wi, const std::string &var)
{
    wi.removeNullVars.insert(var);
    wi.knownVars.erase(var);
    wi.knownNullVars.erase(var);
    wi.knownNonNullVars.erase(var);
    removeNeedCheckNullVarOnly(wi, var);
}

}
