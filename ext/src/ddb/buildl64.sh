#!/bin/sh
g++ -g -m64 -DJ64 -DKXVER=3 -std=c++11 -DLINUX -D_GLIBCXX_USE_CXX11_ABI=0 -DLOGGING_LEVEL_2 -fPIC -shared -I. -I..  -L../../dll/l64 qddb.c -o ../../dll/l64/qddb.so -Wno-write-strings -Wno-unused-variable -lm -lpthread -lDolphinDBAPI -lssl -lrt

