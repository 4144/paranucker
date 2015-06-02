#!/bin/bash

CMD="$1"

if [[ -z "${CMD}" ]]; then
    export CMD="default"
fi

mkdir build
# this need for some outdated os
mkdir m4
autoreconf -i
cd build
if [[ "${CMD}" == "sanitize" ]]; then
    ../configure --enable-sanitize
elif [[ "${CMD}" == "default" ]]; then
    ../configure
elif [[ "${CMD}" == "gprof" ]]; then
    ../configure --enable-gprof
fi
make -j9
