TEST = $(foreach num,$(value S${2}),test${1}-$(num))
S2 = 01 02
S3 = 01 02 03
S4 = 01 02 03 04
S5 = 01 02 03 04 05
CRASHES = crashtest01 crashtest02 crashtest03 crashtest4
TESTS01 = $(call TEST,01,4)
TESTS02 = $(call TEST,02,2)
TESTS03 = $(call TEST,03,2)
TESTS04 = $(call TEST,04,3)
TESTS05 = $(call TEST,05,5)
TESTS06 = $(call TEST,06,4)
TESTS07 = $(call TEST,07,5)
TESTS08 = $(call TEST,08,4)
TESTS09 = $(call TEST,09,4)
TESTS10 = $(call TEST,10,4)
TESTS11 = $(call TEST,11,4)
TESTS12 = $(call TEST,12,4)
TESTS13 = $(call TEST,13,5)
TESTS14 = $(call TEST,14,4)
TESTS15 = $(call TEST,15,4)
TESTS16 = $(call TEST,16,4)
TESTS17 = $(call TEST,17,4)
TESTS18 = $(call TEST,18,4)
TESTS19 = $(call TEST,19,4)
TESTS20 = $(call TEST,20,4)
TESTS21 = $(call TEST,21,5)
TESTS22 = $(call TEST,22,5)
TESTS23 = $(call TEST,23,5)
TESTS24 = $(call TEST,24,5)
TESTS25 = $(call TEST,25,5)
TESTS26 = $(call TEST,26,5)
TESTS27 = $(call TEST,27,5)
TESTS28 = $(call TEST,28,5)
TESTS29 = $(call TEST,29,5)
TESTNUMBERS = 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
ALLTESTS = $(foreach num,$(TESTNUMBERS),test$(num) ${TESTS$(num)})

.PHONY: ${ALLTESTS} ${CRASHES} all crashes

CC := gcc-5
CXX := g++-5
MAKEFLAGS += --jobs=9

PLUGINXX = ../cxxparanucker.so
PLUGIN = ../paranucker.so

CMDXX = LANG=C ${CXX} -c ${4} -fplugin=${PLUGINXX} -fplugin-arg-cxxparanucker-command=${1} ${2} -o ../build/${3}.out 2>${3}
CMD = LANG=C ${CC} -c ${4} -fplugin=${PLUGIN} -fplugin-arg-paranucker-command=${1} ${2} -o ../build/${3}.out 2>${3}

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

test19: ${TESTS19}
test19-01:
	$(call CMDXX,dump,test19.cpp,test19-01.txt)
test19-02:
	$(call CMDXX,findargs,test19.cpp,test19-02.txt)
test19-03:
	$(call CMDXX,dumpnullpointers,test19.cpp,test19-03.txt)
test19-04:
	$(call CMDXX,detectnullpointers,test19.cpp,test19-04.txt)

test20: ${TESTS20}
test20-01:
	$(call CMD,dump,test20.c,test20-01.txt)
test20-02:
	$(call CMD,findargs,test20.c,test20-02.txt)
test20-03:
	$(call CMD,dumpnullpointers,test20.c,test20-03.txt)
test20-04:
	$(call CMD,detectnullpointers,test20.c,test20-04.txt)

test21: ${TESTS21}
test21-01:
	$(call CMDXX,dump,test21.cpp,test21-01.txt)
test21-02:
	$(call CMDXX,findargs,test21.cpp,test21-02.txt)
test21-03:
	$(call CMDXX,dumpnullpointers,test21.cpp,test21-03.txt)
test21-04:
	$(call CMDXX,detectnullpointers,test21.cpp,test21-04.txt)
test21-05:
	$(call CMDXX,detectnullpointers,test21.cpp,test21-05.txt,"-O2")

test22: ${TESTS22}
test22-01:
	$(call CMDXX,dump,test22.cpp,test22-01.txt)
test22-02:
	$(call CMDXX,findargs,test22.cpp,test22-02.txt)
test22-03:
	$(call CMDXX,dumpnullpointers,test22.cpp,test22-03.txt)
test22-04:
	$(call CMDXX,detectnullpointers,test22.cpp,test22-04.txt)
test22-05:
	$(call CMDXX,detectnullpointers,test22.cpp,test22-05.txt,"-O2")

test23: ${TESTS23}
test23-01:
	$(call CMDXX,dump,test23.cpp,test23-01.txt)
test23-02:
	$(call CMDXX,findargs,test23.cpp,test23-02.txt)
test23-03:
	$(call CMDXX,dumpnullpointers,test23.cpp,test23-03.txt)
test23-04:
	$(call CMDXX,detectnullpointers,test23.cpp,test23-04.txt)
test23-05:
	$(call CMDXX,detectnullpointers,test23.cpp,test23-05.txt,"-O2")

test24: ${TESTS24}
test24-01:
	$(call CMD,dump,test24.c,test24-01.txt)
test24-02:
	$(call CMD,findargs,test24.c,test24-02.txt)
test24-03:
	$(call CMD,dumpnullpointers,test24.c,test24-03.txt)
test24-04:
	$(call CMD,detectnullpointers,test24.c,test24-04.txt)
test24-05:
	$(call CMD,detectnullpointers,test24.c,test24-05.txt,"-O2")

test25: ${TESTS25}
test25-01:
	$(call CMDXX,dump,test25.cpp,test25-01.txt,-std=c++0x)
test25-02:
	$(call CMDXX,findargs,test25.cpp,test25-02.txt,-std=c++0x)
test25-03:
	$(call CMDXX,dumpnullpointers,test25.cpp,test25-03.txt,-std=c++0x)
test25-04:
	$(call CMDXX,detectnullpointers,test25.cpp,test25-04.txt,-std=c++0x)
test25-05:
	$(call CMDXX,detectnullpointers,test25.cpp,test25-05.txt,-O2 -std=c++0x -Wall -Wnonnull)

test26: ${TESTS26}
test26-01:
	$(call CMDXX,dump,test26.cpp,test26-01.txt,-std=c++0x)
test26-02:
	$(call CMDXX,findargs,test26.cpp,test26-02.txt,-std=c++0x)
test26-03:
	$(call CMDXX,dumpnullpointers,test26.cpp,test26-03.txt,-std=c++0x)
test26-04:
	$(call CMDXX,detectnullpointers,test26.cpp,test26-04.txt,-std=c++0x)
test26-05:
	$(call CMDXX,detectnullpointers,test26.cpp,test26-05.txt,-O2 -std=c++0x -Wall -Wnonnull)

test27: ${TESTS27}
test27-01:
	$(call CMDXX,dump,test27.cpp,test27-01.txt,-std=c++0x)
test27-02:
	$(call CMDXX,findargs,test27.cpp,test27-02.txt,-std=c++0x)
test27-03:
	$(call CMDXX,dumpnullpointers,test27.cpp,test27-03.txt,-std=c++0x)
test27-04:
	$(call CMDXX,detectnullpointers,test27.cpp,test27-04.txt,-std=c++0x)
test27-05:
	$(call CMDXX,detectnullpointers,test27.cpp,test27-05.txt,-O2 -std=c++0x -Wall -Wnonnull)

test28: ${TESTS28}
test28-01:
	$(call CMDXX,dump,test28.cpp,test28-01.txt,-std=c++0x)
test28-02:
	$(call CMDXX,findargs,test28.cpp,test28-02.txt,-std=c++0x)
test28-03:
	$(call CMDXX,dumpnullpointers,test28.cpp,test28-03.txt,-std=c++0x)
test28-04:
	$(call CMDXX,detectnullpointers,test28.cpp,test28-04.txt,-std=c++0x)
test28-05:
	$(call CMDXX,detectnullpointers,test28.cpp,test28-05.txt,-O2 -std=c++0x -Wall -Wnonnull)

test29: ${TESTS29}
test29-01:
	$(call CMDXX,dump,test29.cpp,test29-01.txt,-std=c++0x)
test29-02:
	$(call CMDXX,findargs,test29.cpp,test29-02.txt,-std=c++0x)
test29-03:
	$(call CMDXX,dumpnullpointers,test29.cpp,test29-03.txt,-std=c++0x)
test29-04:
	$(call CMDXX,detectnullpointers,test29.cpp,test29-04.txt,-std=c++0x)
test29-05:
	$(call CMDXX,detectnullpointers,test29.cpp,test29-05.txt,-O2 -std=c++0x -Wall -Wnonnull)

crashtest01:
	$(call CMDXX,dump,crashtest01.h,crashtest01-01.txt)
crashtest02:
	$(call CMDXX,dump,crashtest02.h,crashtest02-01.txt)
crashtest03:
	$(call CMDXX,findargs,crashtest03.h,crashtest03-01.txt)
crashtest04:
	$(call CMDXX,dump,crashtest04.cpp,crashtest04-01.txt)
