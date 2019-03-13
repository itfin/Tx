gcc -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -I. -I ../ -L../../dll/l64 -lXtTraderApi extfext.cpp -o ../../dll/l64/extfext.so -Wno-write-strings -Wno-write-strings
