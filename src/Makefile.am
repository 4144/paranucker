AUTOMAKE_OPTIONS = subdir-objects

SRC = nodes/base/cst.h \
      nodes/base/decl.h \
      nodes/base/expr.h \
      nodes/base/node.h \
      nodes/base/type.h \
      nodes/cst/integer_cst.h \
      nodes/decl/function_decl.h \
      nodes/decl/parm_decl.h \
      nodes/decl/result_decl.h \
      nodes/decl/type_decl.h \
      nodes/expr/return_expr.h \
      nodes/list/statement_list.h \
      nodes/list/tree_list.h \
      nodes/type/function_type.h \
      nodes/type/integer_type.h \
      nodes/type/pointer_type.h \
      nodes/type/void_type.h \
      nodes/identifier.h \
      parsers/generic.cpp \
      parsers/generic.h \
      parsers/identifier_node.cpp \
      parsers/base/decl.cpp \
      parsers/base/decl.h \
      parsers/base/expr.cpp \
      parsers/base/expr.h \
      parsers/base/type.cpp \
      parsers/base/type.h \
      parsers/cst/integer_cst.cpp \
      parsers/decl/function_decl.cpp \
      parsers/decl/parm_decl.cpp \
      parsers/decl/result_decl.cpp \
      parsers/decl/type_decl.cpp \
      parsers/expr/return_expr.cpp \
      parsers/list/statement_list.cpp \
      parsers/list/tree_list.cpp \
      parsers/type/function_type.cpp \
      parsers/type/integer_type.cpp \
      parsers/type/pointer_type.cpp \
      parsers/type/void_type.cpp \
      includes/parserdefines.inc \
      includes/parserincludes.h \
      includes.h \
      localconsts.h \
      logger.cpp \
      logger.h \
      plugin.cpp \
      stringutils.cpp \
      stringutils.h

CC := gcc-5
CXX := g++-5

# in future need remove -Wno-switch
SHARED_CXXFLAGS = -fPIC -fno-rtti -O2 -pipe -ffast-math -Wall -Wextra \
-std=gnu++1y -Wc++14-compat \
-Wno-literal-suffix -Wno-switch \
-I$(shell $(CC) -print-file-name=plugin)/include

SHARED_LDFLAGS = -avoid-version -lgcc_s

if ENABLE_SANITIZE
#skip -fsanitize=alignment
SHARED_CXXFLAGS += -fsanitize=address \
-fsanitize=shift -fsanitize=integer-divide-by-zero -fsanitize=unreachable \
-fsanitize=vla-bound -fsanitize=null -fsanitize=return \
-fsanitize=signed-integer-overflow -fsanitize=bounds \
-fsanitize=object-size -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
-fsanitize=nonnull-attribute -fsanitize=returns-nonnull-attribute -fsanitize=bool \
-fsanitize=enum -fsanitize=vptr
SHARED_LDFLAGS += -lasan -lubsan -fsanitize=address \
-fsanitize=shift -fsanitize=integer-divide-by-zero -fsanitize=unreachable \
-fsanitize=vla-bound -fsanitize=null -fsanitize=return \
-fsanitize=signed-integer-overflow -fsanitize=bounds \
-fsanitize=object-size -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
-fsanitize=nonnull-attribute -fsanitize=returns-nonnull-attribute -fsanitize=bool \
-fsanitize=enum -fsanitize=vptr
endif

if ENABLE_GPROF
SHARED_CXXFLAGS += "-pg"
endif

lib_LTLIBRARIES = libastdumper.la
libastdumper_la_SOURCES = ${SRC}
libastdumper_la_LDFLAGS = ${SHARED_LDFLAGS}
libastdumper_la_CXXFLAGS = ${SHARED_CXXFLAGS}

all-local: libastdumper.la
	echo done
