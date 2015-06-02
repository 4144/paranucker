AUTOMAKE_OPTIONS = subdir-objects

SRC = plugin.cpp
CXX := g++

SHARED_CXXFLAGS = -pipe -ffast-math -Wall -Wextra \
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
