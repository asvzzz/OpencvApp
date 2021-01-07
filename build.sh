#!/bin/bash

HOME=`pwd`

if [ ! -d "bin" ]; then
    mkdir bin
fi
cd bin

if [ ! -d "build_linux" ]; then
    mkdir build_linux
fi
cd build_linux
if [ ! -f "Makefile" ]; then
    cmake  ../../src
fi
make
cd $HOME
