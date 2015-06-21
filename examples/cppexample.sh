#!/bin/bash

g++-5 -fplugin=../cppastdumper.so -fplugin-arg-cppastdumper-command=detectnullpointers cppexample.cpp
