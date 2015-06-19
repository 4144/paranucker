CRASHES = crashtest01 crashtest02 crashtest03 crashtest4
TESTS01 = test01-01 test01-02 test01-03 test01-04
TESTS02 = test02-01 test02-02
TESTS03 = test03-01 test03-02
TESTS04 = test04-01 test04-02 test04-03
TESTS05 = test05-01 test05-02 test05-03 test05-04 test05-05
TESTS06 = test06-01 test06-02 test06-03 test06-04
TESTS07 = test07-01 test07-02 test07-03 test07-04 test07-05
TESTS08 = test08-01 test08-02 test08-03 test08-04
TESTS09 = test09-01 test09-02 test09-03 test09-04
TESTS10 = test10-01 test10-02 test10-03 test10-04
ALLTESTS = test01 test02 test03 test04 test05 test06 test07 test08 test09 test10 ${TESTS01} ${TESTS02} ${TESTS03} ${TESTS04} ${TESTS05} ${TESTS06} ${TESTS07} ${TESTS08} ${TESTS09} ${TESTS10}

.PHONY: ${ALLTESTS} ${CRASHES} all crashes

CC := gcc-5
CXX := g++-5
MAKEFLAGS += --jobs=9

PLUGIN = ../build/src/.libs/astdumper.so
CMD = LANG=C ${CXX} -c -fplugin=${PLUGIN} -fplugin-arg-astdumper-command=${1} ${2} -o ../build/${3}.out 2>${3}

all: ${ALLTESTS} ${CRASHES}
tests: ${ALLTESTS}
crashes: ${CRASHES}

test01: ${TESTS01}
test01-01:
	$(call CMD,dump,test01.c,test01-01.txt)
test01-02:
	$(call CMD,smalldump,test01.c,test01-02.txt)
test01-03:
	$(call CMD,memoryusage,test01.c,test01-03.txt)
test01-04:
	$(call CMD,dumpunsupported,test01.c,test01-04.txt)

test02: ${TESTS02}
test02-01:
	$(call CMD,dump,test02.c,test02-01.txt)
test02-02:
	$(call CMD,findargs,test02.c,test02-02.txt)

test03: ${TESTS03}
test03-01:
	$(call CMD,dump,test03.c,test03-01.txt)
test03-02:
	$(call CMD,findargs,test03.c,test03-02.txt)

test04: ${TESTS04}
test04-01:
	$(call CMD,dump,test04.c,test04-01.txt)
test04-02:
	$(call CMD,findargs,test04.c,test04-02.txt)
test04-03:
	$(call CMD,detectnullpointers,test04.c,test04-03.txt)

test05: ${TESTS05}
test05-01:
	$(call CMD,dump,test05.c,test05-01.txt)
test05-02:
	$(call CMD,findargs,test05.c,test05-02.txt)
test05-03:
	$(call CMD,detectnullpointers,test05.c,test05-03.txt)
test05-04:
	$(call CMD,dumpunsupported,test05.c,test05-04.txt)
test05-05:
	$(call CMD,dumpnullpointers,test05.c,test05-05.txt)

test06: ${TESTS06}
test06-01:
	$(call CMD,dump,test06.c,test06-01.txt)
test06-02:
	$(call CMD,dumpunsupported,test06.c,test06-02.txt)
test06-03:
	$(call CMD,detectnullpointers,test06.c,test06-03.txt)
test06-04:
	$(call CMD,dumpnullpointers,test06.c,test06-04.txt)

test07: ${TESTS07}
test07-01:
	$(call CMD,dump,test07.cpp,test07-01.txt)
test07-02:
	$(call CMD,smalldump,test07.cpp,test07-02.txt)
test07-03:
	$(call CMD,findargs,test07.cpp,test07-03.txt)
test07-04:
	$(call CMD,detectnullpointers,test07.cpp,test07-04.txt)
test07-05:
	$(call CMD,dumpnullpointers,test07.cpp,test07-05.txt)

test08: ${TESTS08}
test08-01:
	$(call CMD,dump,test08.cpp,test08-01.txt)
test08-02:
	$(call CMD,findargs,test08.cpp,test08-02.txt)
test08-03:
	$(call CMD,dumpnullpointers,test08.cpp,test08-03.txt)
test08-04:
	$(call CMD,detectnullpointers,test08.cpp,test08-04.txt)

test09: ${TESTS09}
test09-01:
	$(call CMD,dump,test09.cpp,test09-01.txt)
test09-02:
	$(call CMD,findargs,test09.cpp,test09-02.txt)
test09-03:
	$(call CMD,dumpnullpointers,test09.cpp,test09-03.txt)
test09-04:
	$(call CMD,detectnullpointers,test09.cpp,test09-04.txt)

test10: ${TESTS10}
test10-01:
	$(call CMD,dump,test10.cpp,test10-01.txt)
test10-02:
	$(call CMD,findargs,test10.cpp,test10-02.txt)
test10-03:
	$(call CMD,dumpnullpointers,test10.cpp,test10-03.txt)
test10-04:
	$(call CMD,detectnullpointers,test10.cpp,test10-04.txt)

crashtest01:
	$(call CMD,dump,crashtest01.h,crashtest01-01.txt)
crashtest02:
	$(call CMD,dump,crashtest02.h,crashtest02-01.txt)
crashtest03:
	$(call CMD,findargs,crashtest03.h,crashtest03-01.txt)
crashtest04:
	$(call CMD,dump,crashtest04.cpp,crashtest04-01.txt)
