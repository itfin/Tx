#!/bin/sh
gcc -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -I. -I.. extfix.c -o ../../dll/l64/extfix.so -Wno-write-strings
