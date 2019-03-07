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

#ifndef ANALYSIS_REPORTS_H
#define ANALYSIS_REPORTS_H

#include "includes.h"

#include <set>
#include <string>

struct Node;
struct WalkItem;

namespace Analysis
{
    void reportParmDeclNullPointer(Node *mainNode,
                                   Node *node,
                                   const WalkItem &wi);

    void reportParmDeclLeftNullPointer(Node *mainNode,
                                       Node *node,
                                       const WalkItem &wi);

    void reportComponentRefNullPointer(Node *mainNode,
                                       Node *node,
                                       const WalkItem &wi);

    void reportParmDeclAttrNullPointer(Node *mainNode,
                                       Node *node,
                                       const WalkItem &wi);

    void reportPossibleNullPointer(Node *node,
                                   const std::string &label);

    void reportUselessCheck(Node *node,
                            const std::string &var);

    bool checkForReport(Node *node,
                        const WalkItem &wi);

    void reportWrongCheck(Node *node);

    void reportCollectionsDifferent(Node *node,
                                    const std::string &name,
                                    const std::string& str1,
                                    const std::string& str2);
}

#endif // ANALYSIS_REPORTS_H
