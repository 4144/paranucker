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

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

struct Node;
struct WalkItem;

namespace Log
{
    void dump(const Node *const node,
              const char *const text,
              ...);

    void dumpRaw(const Node *const node,
                 const char *const text,
                 ...);

    void error(const char *const text,
               ...);

    void log(const char *const text,
             ...);

    void dumpInt(const Node *const node,
                 const char *const text,
                 const int val);

    void dump(const Node *const node,
              const int indent,
              const char *const text,
              ...);

    void dump(const Node *const node);

    void warn(const int loc,
          const std::string &message,
          const std::string &param);

    void dumpAttr(const Node *const node,
                  int num,
                  bool isReturned);

    void dumpWI(Node *const node,
                const std::string &name,
                const WalkItem &wi);
}

#endif  // LOGGER_H
