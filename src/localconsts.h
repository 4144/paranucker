/*
 *  Copyright (C) 2015  Andrei Karas
 *
 *  This file is part of Paranoid null checker.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
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

#define A_DELETE(func) func = delete
#define A_DELETE_COPY(name) name(const name &) = delete; \
    name &operator=(const name&) = delete;

#define A_UNUSED  __attribute__ ((unused))
#define A_WARN_UNUSED __attribute__ ((warn_unused_result))
#define DEPRECATED __attribute__ ((deprecated))
#define restrict __restrict__

#define notfinal

#define FOR_EACH(iter, array) for (auto&& iter : array)

#define FOR_CHAIN(node, var, function, next) \
    for (tree var = function(node); var; var = next(var))

#define FOR_TREE_LIST(node) \
    for (; node; node = node->chain)

#define FOR_TREE_LIST2(node, start) \
    for (TreeListNode *node = start; node; node = node->chain)

#define setPrintField(node, macro, method) \
    node->method = macro(node->gccNode); \
    Log::dumpInt(node, \
        "- "#method": %d", \
        node->method)

#define isIn(value, collection) \
    ((collection).find(value) != (collection).end())

#define isNotIn(value, collection) \
    ((collection).find(value) == (collection).end())
