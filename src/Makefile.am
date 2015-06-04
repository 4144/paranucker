AUTOMAKE_OPTIONS = subdir-objects

SRC = nodes/base/declnode.h \
      nodes/base/node.h \
      nodes/base/typenode.h \
      nodes/functiondeclnode.h \
      nodes/functiontypenode.h \
      nodes/identifiernode.h \
      nodes/parmdeclnode.h \
      nodes/resultdeclnode.h \
      nodes/treelistnode.h \
      nodes/typedeclnode.h \
      nodes/voidtypenode.h \
      parsers/function_decl.cpp \
      parsers/function_type.cpp \
      parsers/generic.cpp \
      parsers/generic.h \
      parsers/identifier_node.cpp \
      parsers/parserincludes.h \
      parsers/result_decl.cpp \
      parsers/tree_list.cpp \
      parsers/type_decl.cpp \
      parsers/void_type.cpp \
      parsers/base/decl.cpp \
      parsers/base/decl.h \
      parsers/base/type.cpp \
      parsers/base/type.h \
      includes.h \
      localconsts.h \
      logger.cpp \
      logger.h \
      plugin.cpp
CXX := g++

# in future need remove -Wno-switch
SHARED_CXXFLAGS = -pipe -ffast-math -Wall -Wextra \
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
