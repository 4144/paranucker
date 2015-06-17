CRASHES = crashtest1 crashtest2 crashtest3 crashtest4
TESTS1 = test1-01 test1-02 test1-03 test1-04
TESTS2 = test2-01 test2-02
TESTS3 = test3-01 test3-02
TESTS4 = test4-01 test4-02 test4-03
TESTS5 = test5-01 test5-02 test5-03 test5-04 test5-05
TESTS6 = test6-01 test6-02 test6-03 test6-04
TESTS7 = test7-01 test7-02 test7-03 test7-04 test7-05
TESTS8 = test8-01 test8-02 test8-03 test8-04
ALLTESTS = test1 test2 test3 test4 test5 test6 test7 test8 ${TESTS1} ${TESTS2} ${TESTS3} ${TESTS4} ${TESTS5} ${TESTS6} ${TESTS7} ${TESTS8}

.PHONY: ${ALLTESTS} ${CRASHES} all crashes

CC := gcc-5
CXX := g++-5
MAKEFLAGS += --jobs=9

PLUGIN = ../build/src/.libs/astdumper.so
CMD = LANG=C ${CXX} -c -fplugin=${PLUGIN} -fplugin-arg-astdumper-command=${1} ${2} -o ../build/${3}.out 2>${3}

all: ${ALLTESTS} ${CRASHES}
tests: ${ALLTESTS}
crashes: ${CRASHES}

test1: ${TESTS1}
test1-01:
	$(call CMD,dump,test1.c,test1-01.txt)
test1-02:
	$(call CMD,smalldump,test1.c,test1-02.txt)
test1-03:
	$(call CMD,memoryusage,test1.c,test1-03.txt)
test1-04:
	$(call CMD,dumpunsupported,test1.c,test1-04.txt)

test2: ${TESTS2}
test2-01:
	$(call CMD,dump,test2.c,test2-01.txt)
test2-02:
	$(call CMD,findargs,test2.c,test2-02.txt)

test3: ${TESTS3}
test3-01:
	$(call CMD,dump,test3.c,test3-01.txt)
test3-02:
	$(call CMD,findargs,test3.c,test3-02.txt)

test4: ${TESTS4}
test4-01:
	$(call CMD,dump,test4.c,test4-01.txt)
test4-02:
	$(call CMD,findargs,test4.c,test4-02.txt)
test4-03:
	$(call CMD,detectnullpointers,test4.c,test4-03.txt)

test5: ${TESTS5}
test5-01:
	$(call CMD,dump,test5.c,test5-01.txt)
test5-02:
	$(call CMD,findargs,test5.c,test5-02.txt)
test5-03:
	$(call CMD,detectnullpointers,test5.c,test5-03.txt)
test5-04:
	$(call CMD,dumpunsupported,test5.c,test5-04.txt)
test5-05:
	$(call CMD,dumpnullpointers,test5.c,test5-05.txt)

test6: ${TESTS6}
test6-01:
	$(call CMD,dump,test6.c,test6-01.txt)
test6-02:
	$(call CMD,dumpunsupported,test6.c,test6-02.txt)
test6-03:
	$(call CMD,detectnullpointers,test6.c,test6-03.txt)
test6-04:
	$(call CMD,dumpnullpointers,test6.c,test6-04.txt)

test7: ${TESTS7}
test7-01:
	$(call CMD,dump,test7.cpp,test7-01.txt)
test7-02:
	$(call CMD,smalldump,test7.cpp,test7-02.txt)
test7-03:
	$(call CMD,findargs,test7.cpp,test7-03.txt)
test7-04:
	$(call CMD,detectnullpointers,test7.cpp,test7-04.txt)
test7-05:
	$(call CMD,dumpnullpointers,test7.cpp,test7-05.txt)

test8: ${TESTS8}
test8-01:
	$(call CMD,dump,test8.cpp,test8-01.txt)
test8-02:
	$(call CMD,findargs,test8.cpp,test8-02.txt)
test8-03:
	$(call CMD,dumpnullpointers,test8.cpp,test8-03.txt)
test8-04:
	$(call CMD,detectnullpointers,test8.cpp,test8-04.txt)

crashtest1:
	$(call CMD,dump,crashtest1.h,crashtest1-01.txt)
crashtest2:
	$(call CMD,dump,crashtest2.h,crashtest2-01.txt)
crashtest3:
	$(call CMD,findargs,crashtest3.h,crashtest3-01.txt)
crashtest4:
	$(call CMD,dump,crashtest4.cpp,crashtest4-01.txt)
