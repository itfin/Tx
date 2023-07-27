#!/bin/sh

gcc -gstabs+ -D_DEBUG1 -DMLINTERFACE=4 -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -lWSTP64i4 -lrt -luuid -I. -I.. -L../../dll/l64 -L/lib/x86_64-linux-gnu  qmma.c -o ../../dll/l64/qmma.so -Wno-write-strings -Wno-unused-variable -Wno-int-conversion -Wno-incompatible-pointer-types

#gcc -gstabs+ -D_DEBUG1 -DMLINTERFACE=4 -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -lML64i4 -lrt -luuid -I. -I.. -L../../dll/l64 -L/lib/x86_64-linux-gnu  qmma.c -o ../../dll/l64/qmma.so -Wno-write-strings -Wall
