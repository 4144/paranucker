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

#include "logger.h"

#include "nodes/node.h"

#include "localconsts.h"

namespace Log
{

void log(const Node *const node,
         const char *const text,
         ...
         )
{
    va_list ap;
    va_start(ap, text);

    if (node)
        fprintf(stderr, "%s", node->getIndent().c_str());
    vfprintf(stderr, text, ap);
    if (node && !node->tag.empty())
        fprintf(stderr, " - %s", node->tag.c_str());
    fprintf(stderr, "\n");

    va_end(ap);
}

void log(const Node *const node,
         const int indent,
         const char *const text,
         ...
         )
{
    va_list ap;
    va_start(ap, text);

    std::string str;
    for (int f = 0; f < indent; f ++)
        str.append(" ");

    if (node)
        fprintf(stderr, "%s%s", str.c_str(), node->getIndent().c_str());
    else
        fprintf(stderr, "%s", str.c_str());
    vfprintf(stderr, text, ap);
    if (node && !node->tag.empty())
        fprintf(stderr, " - %s", node->tag.c_str());
    fprintf(stderr, "\n");

    va_end(ap);
}

void log(const Node *const node)
{
    if (!node)
    {
        fprintf(stderr, "node is null\n");
        return;
    }
    fprintf(stderr, "%s", node->getIndent().c_str());
    fprintf(stderr, "%s", node->nodeType.c_str());
    if (!node->label.empty())
        fprintf(stderr, " %s", node->label.c_str());
    if (!node->file.empty())
    {
        fprintf(stderr, " %s %d:%d",
            node->file.c_str(),
            node->line,
            node->column);
    }
    if (!node->tag.empty())
        fprintf(stderr, " - %s", node->tag.c_str());

    fprintf(stderr, "\n");
}

}