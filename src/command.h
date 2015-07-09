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

#ifndef COMMAND_H
#define COMMAND_H

#define checkCommand(val) ((command & Command::val) == Command::val)
#define disableCommand(val) command = static_cast<Command>(static_cast<int>( \
    command | Command::val) ^ static_cast<int>(Command::val))

enum Command : int
{
    Parse              = 0,
    Dump               = 1,
    SmallDump          = 2,
    DumpUnsupported    = 4,
    MemoryUsage        = 8,
    FindArgs           = 16,
    DetectNullPointers = 32,
    DumpNullPointers   = 64,
    DetectUseless      = 128
};

extern Command command;

#endif  // COMMAND_H
