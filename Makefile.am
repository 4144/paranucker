CC := gcc-5
CXX := g++-5

ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src
#EXTRA_DIST = 

test:
	cp src/.libs/libastdumper.so src/.libs/astdumper.so
	cd ../test && make

.PHONY: test
