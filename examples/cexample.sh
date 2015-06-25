#!/bin/bash

gcc-5 -fplugin=../paranucker.so -fplugin-arg-paranucker-command=detectnullpointers cexample.c
