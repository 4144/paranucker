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

#include "command.h"
#include "includes.h"

#include "analysis/walkitem.h"

#include "nodes/base/node.h"

#include <set>

#include "localconsts.h"

namespace Log
{

void dump(const Node *const node,
          const char *const text,
          ...)
{
    if (command != Command::Dump)
        return;

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

void dumpRaw(const Node *const node,
             const char *const text,
             ...)
{
    if (command != Command::Dump)
        return;

    va_list ap;
    va_start(ap, text);

    if (node)
        fprintf(stderr, "%s", node->getIndent().c_str());
    vfprintf(stderr, text, ap);
    fprintf(stderr, "\n");

    va_end(ap);
}

void error(const char *const text,
           ...)
{
    va_list ap;
    va_start(ap, text);

    vfprintf(stderr, text, ap);
    fprintf(stderr, "\n");

    va_end(ap);
}

void log(const char *const text,
         ...)
{
    va_list ap;
    va_start(ap, text);
    vfprintf(stderr, text, ap);
    va_end(ap);
}

void dumpInt(const Node *const node,
             const char *const text,
             const int val)
{
    if (command != Command::Dump || !val || !node)
        return;

    fprintf(stderr, "%s", node->getIndent().c_str());
    fprintf(stderr, text, val);
    fprintf(stderr, "\n");
}

void dump(const Node *const node,
          const int indent,
          const char *const text,
          ...)
{
    if (command != Command::Dump)
        return;

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

void dump(const Node *const node)
{
    if (command == Command::SmallDump)
    {
        fprintf(stderr,
            "%d %s %s\n",
            node->indent,
            node->nodeTypeName.c_str(),
            node->file.c_str());
        return;
    }

    if (command != Command::Dump)
        return;

    if (!node)
    {
        fprintf(stderr, "node is null\n");
        return;
    }
    fprintf(stderr, "%s", node->getIndent().c_str());
    fprintf(stderr, "%s", node->nodeTypeName.c_str());
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

void dumpAttr(const Node *const node, int num, bool isReturned)
{
    if (!node)
    {
        fprintf(stderr, "node is null\n");
        return;
    }
    fprintf(stderr, "%s", node->getIndent().c_str());
    fprintf(stderr, "%s", node->nodeTypeName.c_str());
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

    fprintf(stderr, " walkTree%d: %d\n", num, isReturned ? 1 : 0);
}

void dumpWI(Node *const node,
            const std::string &name,
            WalkItem &wi)
{
    //return;
    Log::log("%s%s %s",
        name.c_str(),
        node->nodeTypeName.c_str(),
        node->label.c_str());
    if (wi.cleanExpr)
        Log::log(" clean");
    if (wi.uselessExpr)
        Log::log(" useless");
    if (wi.isReturned)
        Log::log(" returned");
    Log::log(" checkedNullVars:");
    FOR_EACH (std::set<std::string>::const_iterator,
              it,
              wi.checkedNullVars)
    {
        Log::log("%s, ", (*it).c_str());
    }
    Log::log(" checkedNonNullVars:");
    FOR_EACH (std::set<std::string>::const_iterator,
              it,
              wi.checkedNonNullVars)
    {
        Log::log("%s, ", (*it).c_str());
    }
    Log::log("\n");
}

void warn(const int loc,
          const std::string &message,
          const std::string &param)
{
    warning_at(loc, 0, message.c_str(), param.c_str());
}

}