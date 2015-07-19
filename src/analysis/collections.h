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

#ifndef ANALYSIS_COLLECTIONS_H
#define ANALYSIS_COLLECTIONS_H

#include "includes.h"

#include <set>
#include <string>

struct Node;
struct WalkItem;

namespace Analysis
{
    void addNeedCheckNullVars(WalkItem &wi,
                              WalkItem &wo);

    void addNeedCheckNullVars2(WalkItem &wi,
                               WalkItem &wo);

    void addUnknownVar(WalkItem &wi,
                       const std::string &var);

    void addNonNullVar(WalkItem &wi,
                       const std::string &var);

    void addNullVar(WalkItem &wi,
                    const std::string &var);

    void addLinkedVar(WalkItem &wi,
                      std::string parent,
                      const std::string &var);

    void removeNeedCheckNullVar(WalkItem &wi, std::string str);

    void removeNeedCheckNullVarsSetAll(WalkItem &wi,
                                       std::set<std::string> &vars);

    void removeNeedCheckNullVarsSet(WalkItem &wi,
                                    std::set<std::string> &vars);

    void mergeThenNullChecked(WalkItem &wi1, WalkItem &wi2);

    void mergeElseNullChecked(WalkItem &wi1, WalkItem &wi2);

    void mergeThenNonNullChecked(WalkItem &wi1, WalkItem &wi2);

    void mergeElseNonNullChecked(WalkItem &wi1, WalkItem &wi2);

    void intersectThenNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2);

    void intersectElseNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2);

    void intersectThenNonNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2);

    void intersectElseNonNullChecked(WalkItem &wi, WalkItem &wi1, WalkItem &wi2);

    void removeFromNeedCheckNullVars(WalkItem &wi,
                                     std::set<std::string> &vars);

    void addKnownNullVarsWithLinked(WalkItem &wo,
                                    WalkItem &wi,
                                    std::set<std::string> &vars);

    void addKnownNonNullVarsWithLinked(WalkItem &wo,
                                       WalkItem &wi,
                                       std::set<std::string> &vars);

    void removeVar(WalkItem &wi, const std::string &var);

    void enforceNeedCheckNullVars(WalkItem &wi);

    void removeLinkVarOnly(WalkItem &wi, const std::string &var);

    void removeNeedCheckNullVarsThen(WalkItem &wco, WalkItem &wi, WalkItem &wo);

    void removeNeedCheckNullVarsElse(WalkItem &wco, WalkItem &wi, WalkItem &wo);

    void addKnownNonNullVarWithLinked(WalkItem &wo, WalkItem &wi, const std::string &var);

    void removeNeedCheckNullVarOnly(WalkItem &wi, const std::string &var);

    void removeKnownNullVars2(WalkItem &wi, WalkItem &wo);
}

#endif // ANALYSIS_COLLECTIONS_H
