#!/bin/sh
gcc -g -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lt2sdk -lHsFutuSystemInfo -lLinuxDataCollect -I. -I.. -L../../dll/l64  extfeufx.cpp -o ../../dll/l64/extfeufx.so -Wno-write-strings #-D_DEBUG
gcc -g -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lt2sdk -lHsFutuSystemInfo.x64test  -lLinuxDataCollectTest -I. -I.. -L../../dll/l64  extfeufx.cpp -o ../../dll/l64/extfeufxtest.so -Wno-write-strings #-D_DEBUG

