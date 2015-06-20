/* Definitions for C++ parsing and type checking.
   Copyright (C) 1987-2015 Free Software Foundation, Inc.
   Contributed by Michael Tiemann (tiemann@cygnus.com)

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef CUSTOM_FIXED_CP_TREE_H
#define CUSTOM_FIXED_CP_TREE_H

#define VAR_FUNCTION_OR_PARM_DECL_CHECK(NODE) \
  TREE_CHECK3(NODE,VAR_DECL,FUNCTION_DECL,PARM_DECL)

#define EXPR_STMT_EXPR(NODE) TREE_OPERAND (EXPR_STMT_CHECK (NODE), 0)

#define HANDLER_PARMS(NODE) TREE_OPERAND (HANDLER_CHECK (NODE), 0)
#define HANDLER_BODY(NODE) TREE_OPERAND (HANDLER_CHECK (NODE), 1)
#define HANDLER_TYPE(NODE) TREE_TYPE (HANDLER_CHECK (NODE))
#define DECL_THIS_STATIC(NODE) \
  DECL_LANG_FLAG_6 (VAR_FUNCTION_OR_PARM_DECL_CHECK (NODE))

#define SWITCH_STMT_COND(NODE) TREE_OPERAND (SWITCH_STMT_CHECK (NODE), 0)
#define SWITCH_STMT_BODY(NODE) TREE_OPERAND (SWITCH_STMT_CHECK (NODE), 1)
#define SWITCH_STMT_TYPE(NODE) TREE_OPERAND (SWITCH_STMT_CHECK (NODE), 2)
#define SWITCH_STMT_SCOPE(NODE) TREE_OPERAND (SWITCH_STMT_CHECK (NODE), 3)

#define CLEANUP_BODY(NODE) TREE_OPERAND (CLEANUP_STMT_CHECK (NODE), 0)
#define CLEANUP_EXPR(NODE) TREE_OPERAND (CLEANUP_STMT_CHECK (NODE), 1)
#define CLEANUP_DECL(NODE) TREE_OPERAND (CLEANUP_STMT_CHECK (NODE), 2)

#define DO_COND(NODE) TREE_OPERAND (DO_STMT_CHECK (NODE), 0)
#define DO_BODY(NODE) TREE_OPERAND (DO_STMT_CHECK (NODE), 1)

#define WHILE_COND(NODE) TREE_OPERAND (WHILE_STMT_CHECK (NODE), 0)
#define WHILE_BODY(NODE) TREE_OPERAND (WHILE_STMT_CHECK (NODE), 1)

#define FOR_INIT_STMT(NODE) TREE_OPERAND (FOR_STMT_CHECK (NODE), 0)
#define FOR_COND(NODE) TREE_OPERAND (FOR_STMT_CHECK (NODE), 1)
#define FOR_EXPR(NODE) TREE_OPERAND (FOR_STMT_CHECK (NODE), 2)
#define FOR_BODY(NODE) TREE_OPERAND (FOR_STMT_CHECK (NODE), 3)
#define FOR_SCOPE(NODE) TREE_OPERAND (FOR_STMT_CHECK (NODE), 4)

#define IF_COND(NODE) TREE_OPERAND (IF_STMT_CHECK (NODE), 0)
#define THEN_CLAUSE(NODE) TREE_OPERAND (IF_STMT_CHECK (NODE), 1)
#define ELSE_CLAUSE(NODE) TREE_OPERAND (IF_STMT_CHECK (NODE), 2)
#define IF_SCOPE(NODE) TREE_OPERAND (IF_STMT_CHECK (NODE), 3)

#endif  // CUSTOM_FIXED_CP_TREE_H
