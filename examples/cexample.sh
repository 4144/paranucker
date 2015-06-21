#!/bin/bash

gcc-5 -fplugin=../astdumper.so -fplugin-arg-astdumper-command=detectnullpointers cexample.c
