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

#ifndef ANALYSIS_VARITEM_H
#define ANALYSIS_VARITEM_H

#include <string>

struct VarItem
{
    VarItem() :
        name(),
        isNonNull(false)
    {
    }

    VarItem(const std::string &name0) :
        name(name0),
        isNonNull(false)
    {
    }

    VarItem(const std::string &name0,
            const bool isNonNull0) :
        name(name0),
        isNonNull(isNonNull0)
    {
    }

    bool empty() const
    { return name.empty(); }

    size_t size() const
    { return name.size(); }

    std::string name;
    bool isNonNull;
};


#endif // ANALYSIS_VARITEM_H
