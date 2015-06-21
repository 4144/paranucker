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
TESTS11 = test11-01 test11-02 test11-03 test11-04
TESTS12 = test12-01 test12-02 test12-03 test12-04
TESTS13 = test13-01 test13-02 test13-03 test13-04 test13-05
TESTS14 = test14-01 test14-02 test14-03 test14-04
TESTS15 = test15-01 test15-02 test15-03 test15-04
TESTS16 = test16-01 test16-02 test16-03 test16-04
TESTS17 = test17-01 test17-02 test17-03 test17-04
TESTS18 = test18-01 test18-02 test18-03 test18-04
ALLTESTS = test01 test02 test03 test04 test05 test06 test07 test08 test09 test10 test11 test12 test13 test14 test15 test16 test17 test18 ${TESTS01} ${TESTS02} ${TESTS03} ${TESTS04} ${TESTS05} ${TESTS06} ${TESTS07} ${TESTS08} ${TESTS09} ${TESTS10} ${TESTS11} ${TESTS12} ${TESTS13} ${TESTS14} ${TESTS15} ${TESTS16} ${TESTS17} ${TESTS18}

.PHONY: ${ALLTESTS} ${CRASHES} all crashes

CC := gcc-5
CXX := g++-5
MAKEFLAGS += --jobs=9

PLUGINXX = ../cppastdumper.so
PLUGIN = ../astdumper.so

CMDXX = LANG=C ${CXX} -c -fplugin=${PLUGINXX} -fplugin-arg-cppastdumper-command=${1} ${2} -o ../build/${3}.out 2>${3}
CMD = LANG=C ${CC} -c -fplugin=${PLUGIN} -fplugin-arg-astdumper-command=${1} ${2} -o ../build/${3}.out 2>${3}

all: ${ALLTESTS} ${CRASHES}
tests: ${ALLTESTS}
crashes: ${CRASHES}

test01: ${TESTS01}
test01-01:
	$(call CMDXX,dump,test01.cpp,test01-01.txt)
test01-02:
	$(call CMDXX,smalldump,test01.cpp,test01-02.txt)
test01-03:
	$(call CMDXX,memoryusage,test01.cpp,test01-03.txt)
test01-04:
	$(call CMDXX,dumpunsupported,test01.cpp,test01-04.txt)

test02: ${TESTS02}
test02-01:
	$(call CMDXX,dump,test02.cpp,test02-01.txt)
test02-02:
	$(call CMDXX,findargs,test02.cpp,test02-02.txt)

test03: ${TESTS03}
test03-01:
	$(call CMDXX,dump,test03.cpp,test03-01.txt)
test03-02:
	$(call CMDXX,findargs,test03.cpp,test03-02.txt)

test04: ${TESTS04}
test04-01:
	$(call CMDXX,dump,test04.cpp,test04-01.txt)
test04-02:
	$(call CMDXX,findargs,test04.cpp,test04-02.txt)
test04-03:
	$(call CMDXX,detectnullpointers,test04.cpp,test04-03.txt)

test05: ${TESTS05}
test05-01:
	$(call CMDXX,dump,test05.cpp,test05-01.txt)
test05-02:
	$(call CMDXX,findargs,test05.cpp,test05-02.txt)
test05-03:
	$(call CMDXX,detectnullpointers,test05.cpp,test05-03.txt)
test05-04:
	$(call CMDXX,dumpunsupported,test05.cpp,test05-04.txt)
test05-05:
	$(call CMDXX,dumpnullpointers,test05.cpp,test05-05.txt)

test06: ${TESTS06}
test06-01:
	$(call CMDXX,dump,test06.cpp,test06-01.txt)
test06-02:
	$(call CMDXX,dumpunsupported,test06.cpp,test06-02.txt)
test06-03:
	$(call CMDXX,detectnullpointers,test06.cpp,test06-03.txt)
test06-04:
	$(call CMDXX,dumpnullpointers,test06.cpp,test06-04.txt)

test07: ${TESTS07}
test07-01:
	$(call CMDXX,dump,test07.cpp,test07-01.txt)
test07-02:
	$(call CMDXX,smalldump,test07.cpp,test07-02.txt)
test07-03:
	$(call CMDXX,findargs,test07.cpp,test07-03.txt)
test07-04:
	$(call CMDXX,detectnullpointers,test07.cpp,test07-04.txt)
test07-05:
	$(call CMDXX,dumpnullpointers,test07.cpp,test07-05.txt)

test08: ${TESTS08}
test08-01:
	$(call CMDXX,dump,test08.cpp,test08-01.txt)
test08-02:
	$(call CMDXX,findargs,test08.cpp,test08-02.txt)
test08-03:
	$(call CMDXX,dumpnullpointers,test08.cpp,test08-03.txt)
test08-04:
	$(call CMDXX,detectnullpointers,test08.cpp,test08-04.txt)

test09: ${TESTS09}
test09-01:
	$(call CMDXX,dump,test09.cpp,test09-01.txt)
test09-02:
	$(call CMDXX,findargs,test09.cpp,test09-02.txt)
test09-03:
	$(call CMDXX,dumpnullpointers,test09.cpp,test09-03.txt)
test09-04:
	$(call CMDXX,detectnullpointers,test09.cpp,test09-04.txt)

test10: ${TESTS10}
test10-01:
	$(call CMDXX,dump,test10.cpp,test10-01.txt)
test10-02:
	$(call CMDXX,findargs,test10.cpp,test10-02.txt)
test10-03:
	$(call CMDXX,dumpnullpointers,test10.cpp,test10-03.txt)
test10-04:
	$(call CMDXX,detectnullpointers,test10.cpp,test10-04.txt)

test11: ${TESTS11}
test11-01:
	$(call CMDXX,dump,test11.cpp,test11-01.txt)
test11-02:
	$(call CMDXX,findargs,test11.cpp,test11-02.txt)
test11-03:
	$(call CMDXX,dumpnullpointers,test11.cpp,test11-03.txt)
test11-04:
	$(call CMDXX,detectnullpointers,test11.cpp,test11-04.txt)

test12: ${TESTS12}
test12-01:
	$(call CMDXX,dump,test12.cpp,test12-01.txt)
test12-02:
	$(call CMDXX,findargs,test12.cpp,test12-02.txt)
test12-03:
	$(call CMDXX,dumpnullpointers,test12.cpp,test12-03.txt)
test12-04:
	$(call CMDXX,detectnullpointers,test12.cpp,test12-04.txt)

test13: ${TESTS13}
test13-01:
	$(call CMD,dump,test13.c,test13-01.txt)
test13-02:
	$(call CMD,findargs,test13.c,test13-02.txt)
test13-03:
	$(call CMD,detectnullpointers,test13.c,test13-03.txt)
test13-04:
	$(call CMD,dumpunsupported,test13.c,test13-04.txt)
test13-05:
	$(call CMD,dumpnullpointers,test13.c,test13-05.txt)

test14: ${TESTS14}
test14-01:
	$(call CMD,dump,test14.c,test14-01.txt)
test14-02:
	$(call CMD,dumpunsupported,test14.c,test14-02.txt)
test14-03:
	$(call CMD,detectnullpointers,test14.c,test14-03.txt)
test14-04:
	$(call CMD,dumpnullpointers,test14.c,test14-04.txt)

test15: ${TESTS15}
test15-01:
	$(call CMD,dump,test15.c,test15-01.txt)
test15-02:
	$(call CMD,findargs,test15.c,test15-02.txt)
test15-03:
	$(call CMD,dumpnullpointers,test15.c,test15-03.txt)
test15-04:
	$(call CMD,detectnullpointers,test15.c,test15-04.txt)

test16: ${TESTS16}
test16-01:
	$(call CMD,dump,test16.c,test16-01.txt)
test16-02:
	$(call CMD,findargs,test16.c,test16-02.txt)
test16-03:
	$(call CMD,dumpnullpointers,test16.c,test16-03.txt)
test16-04:
	$(call CMD,detectnullpointers,test16.c,test16-04.txt)

test17: ${TESTS17}
test17-01:
	$(call CMD,dump,test17.c,test17-01.txt)
test17-02:
	$(call CMD,findargs,test17.c,test17-02.txt)
test17-03:
	$(call CMD,dumpnullpointers,test17.c,test17-03.txt)
test17-04:
	$(call CMD,detectnullpointers,test17.c,test17-04.txt)

test18: ${TESTS18}
test18-01:
	$(call CMDXX,dump,test18.cpp,test18-01.txt)
test18-02:
	$(call CMDXX,findargs,test18.cpp,test18-02.txt)
test18-03:
	$(call CMDXX,dumpnullpointers,test18.cpp,test18-03.txt)
test18-04:
	$(call CMDXX,detectnullpointers,test18.cpp,test18-04.txt)

crashtest01:
	$(call CMDXX,dump,crashtest01.h,crashtest01-01.txt)
crashtest02:
	$(call CMDXX,dump,crashtest02.h,crashtest02-01.txt)
crashtest03:
	$(call CMDXX,findargs,crashtest03.h,crashtest03-01.txt)
crashtest04:
	$(call CMDXX,dump,crashtest04.cpp,crashtest04-01.txt)
