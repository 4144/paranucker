.PHONY: test1 test2 crashtest1 crashtest2 all crashes clean
.NOTPARALLEL: all allcrash

CC := gcc-5
CXX := g++-5

PLUGIN = ../build/src/.libs/astdumper.so
CMD = ${CXX} -fplugin=${PLUGIN} -fplugin-arg-astdumper-command=${1} ${2} -o a.out 2>${3}

all: test1 test2 clean
crashes: crashtest1 crashtest2 clean

clean:
	@rm a.out 2>/dev/null || true

test1:
	$(call CMD,dump,test1.c,test1-01.txt)
	$(call CMD,smalldump,test1.c,test1-02.txt)
	$(call CMD,memoryusage,test1.c,test1-03.txt)
	$(call CMD,dumpunsupported,test1.c,test1-04.txt)
test2:
	$(call CMD,dump,test2.c,test2-01.txt)

crashtest1:
	$(call CMD,dump,crashtest1.h,crashtest1-01.txt)
crashtest2:
	$(call CMD,dump,crashtest2.h,crashtest2-01.txt)
