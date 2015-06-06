#!/bin/bash

cd test
g++-5 -fplugin=../build/src/.libs/libastdumper.so test1.c 2>../test.txt

cd ..
