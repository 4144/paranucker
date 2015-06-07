CC := gcc-5
CXX := g++-5

ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src
#EXTRA_DIST = 

test:
	${CXX} -fplugin=src/.libs/libastdumper.so ../test/test1.c 2>../test.txt

.PHONY: test
