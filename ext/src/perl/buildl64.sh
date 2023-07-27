#!/bin/sh
gcc -m64 -DJ64 -DKXVER=3 -fPIC -shared -I. -I.. -I/usr/lib/x86_64-linux-gnu/perl/5.36.0/CORE/  -L../../dll/l64 -L/lib/x86_64-linux-gnu  -L/usr/lib/x86_64-linux-gnu/perl/5.36.0/CORE/ qperl.c -o ../../dll/l64/qperl.so -Wno-write-strings -Wno-unused-variable -Wno-int-conversion -Wno-incompatible-pointer-types -lm -lpthread -lperl 


