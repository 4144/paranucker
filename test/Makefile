.PHONY: test1 all clean
.NOTPARALLEL: all

CC := gcc-5
CXX := g++-5

PLUGIN = ../build/src/.libs/astdumper.so
CMD = ${CXX} -fplugin=${PLUGIN} -fplugin-arg-astdumper-command=${1} ${2} 2>../${3}

all: test1 clean

clean:
	@rm a.out 2>/dev/null || true

test1:
	$(call CMD,dump,test1.c,test.txt)
