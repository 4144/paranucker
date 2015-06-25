#!/bin/bash

g++-5 -fplugin=../cxxparanucker.so -fplugin-arg-cxxparanucker-command=detectnullpointers cxxexample.cpp
