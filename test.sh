#!/bin/bash

cd test
g++ -fplugin=../build/src/.libs/libastdumper.so test1.c 2>../test.txt

cd ..