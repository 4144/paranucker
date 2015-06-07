.PHONY: test1 all clean
.NOTPARALLEL: all

CC := gcc-5
CXX := g++-5

PLUGIN = ../build/src/.libs/astdumper.so
CMD = ${CXX} -fplugin=${PLUGIN} -fplugin-arg-astdumper-command=${1} ${2} -o a.out 2>../${3}

all: test1 test2 clean

clean:
	@rm a.out 2>/dev/null || true

test1:
	$(call CMD,dump,test1.c,test.txt)
test2:
	$(call CMD,dump,test2.h,test2.txt)
