.PHONY: test1 crashtest1 all allcrash clean
.NOTPARALLEL: all allcrash

CC := gcc-5
CXX := g++-5

PLUGIN = ../build/src/.libs/astdumper.so
CMD = ${CXX} -fplugin=${PLUGIN} -fplugin-arg-astdumper-command=${1} ${2} -o a.out 2>${3}

all: test1 allcrash clean

allcrash: crashtest1

clean:
	@rm a.out 2>/dev/null || true

test1:
	$(call CMD,dump,test1.c,test1.txt)

crashtest1:
	$(call CMD,dump,crashtest1.h,crashtest1.txt)
