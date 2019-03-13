#!/bin/sh
g++ -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -lstdc++ -I. -I..  -L../../dll/l64 -lGWDPApi extgwdp.cpp -o ../../dll/l64/extgwdp.so -Wno-write-strings
