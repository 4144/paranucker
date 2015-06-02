#!/bin/bash

cd test
g++ -fplugin=../build/src/.libs/libastdumper.so test1.c

cd ..