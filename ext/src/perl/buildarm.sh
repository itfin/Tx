#!/bin/sh
gcc -DJ64 -DKXVER=3 -fPIC -shared -I. -I.. qperl.c -o ../../dll/l64arm/qperl.so `perl -MExtUtils::Embed -e ccopts -e ldopts` 


