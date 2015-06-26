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

#include "includes.h"

#include "plugin-version.h"
#include "intl.h"

#include "command.h"

#include "analysis/analysis.h"

#include "parsers/generic.h"

#include <map>

#include "localconsts.h"

int plugin_is_GPL_compatible = 1;

struct Node;

Command command = Command::DetectNullPointers;
std::map<tree, Node*> foundNodesMap;
std::map<Node*, Node*> updateNodesMap;

static void pre_generic(void *gcc_data,
                        void *user_data A_UNUSED)
{
    Node *node = Generic::parseNodes((tree)gcc_data);
    if (command == Command::FindArgs ||
        command == Command::DetectNullPointers ||
        command == Command::DumpNullPointers)
    {
        Generic::updateNodes();
        Analysis::startWalkTree(node);
    }
    Generic::cleanAllNodes(node);
}

int plugin_init (struct plugin_name_args *plugin_info,
                 struct plugin_gcc_version *version)
{
    if (!plugin_default_version_check (version, &gcc_version))
        return 1;

    const char *const plugin_name = plugin_info->base_name;
    const int argc = plugin_info->argc;
    struct plugin_argument *argv = plugin_info->argv;
    for (int f = 0; f < argc; f ++)
    {
        if (!strcmp (argv[f].key, "command"))
        {
            const std::string cmd = argv[f].value;
            if (cmd == "parse")
            {
                command = Command::Parse;
            }
            else if (cmd == "dump")
            {
                command = Command::Dump;
            }
            else if (cmd == "smalldump")
            {
                command = Command::SmallDump;
            }
            else if (cmd == "memoryusage")
            {
                command = Command::MemoryUsage;
            }
            else if (cmd == "dumpunsupported")
            {
                command = Command::DumpUnsupported;
            }
            else if (cmd == "findargs")
            {
                command = Command::FindArgs;
            }
            else if (cmd == "detectnullpointers")
            {
                command = Command::DetectNullPointers;
            }
            else if (cmd == "dumpnullpointers")
            {
                command = Command::DumpNullPointers;
            }
            else
            {
                error("Plugin %s. Unknown command: %s",
                    plugin_name,
                    cmd.c_str());
                return 0;
            }
        }
    }

    register_callback(plugin_info->base_name,
        PLUGIN_PRE_GENERICIZE,
        &pre_generic,
        0);

    return 0;
}
