clang -g -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -I. -I ../ -L../../dll/l64 -lama extfql2hr.cpp -o ../../dll/l64/extfql2hr.so -Wno-write-strings -Wno-write-strings -Wno-unused-value
