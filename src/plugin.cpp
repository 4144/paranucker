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

#include "gcc-plugin.h"
#include "print-tree.h"
#include "tree.h"

int plugin_is_GPL_compatible = 1;

static void pre_generic(void *gcc_data,
                        void *user_data)
{
    tree node = (tree)gcc_data;
    printf("pre_generic\n");
}

int plugin_init (struct plugin_name_args *plugin_info,
                 struct plugin_gcc_version *version)
{
    register_callback(plugin_info->base_name,
        PLUGIN_PRE_GENERICIZE,
        &pre_generic,
        0);

    return 0;
}
