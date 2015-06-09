.PHONY: test1 test2 test3 test4 test5 crashtest1 crashtest2 all crashes clean
.NOTPARALLEL: all allcrash

CC := gcc-5
CXX := g++-5

PLUGIN = ../build/src/.libs/astdumper.so
CMD = LANG=C ${CXX} -c -fplugin=${PLUGIN} -fplugin-arg-astdumper-command=${1} ${2} -o a.out 2>${3}

all: test1 test2 test3 test4 test5 clean
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
	$(call CMD,findargs,test2.c,test2-02.txt)
test3:
	$(call CMD,dump,test3.c,test3-01.txt)
	$(call CMD,findargs,test3.c,test3-02.txt)
test4:
	$(call CMD,dump,test4.c,test4-01.txt)
	$(call CMD,findargs,test4.c,test4-02.txt)
	$(call CMD,detectnullpointers,test4.c,test4-03.txt)
test5:
	$(call CMD,dump,test5.c,test5-01.txt)
	$(call CMD,findargs,test5.c,test5-02.txt)
	$(call CMD,detectnullpointers,test5.c,test5-03.txt)
	$(call CMD,dumpunsupported,test5.c,test5-04.txt)

crashtest1:
	$(call CMD,dump,crashtest1.h,crashtest1-01.txt)
crashtest2:
	$(call CMD,dump,crashtest2.h,crashtest2-01.txt)
