clang -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -lrt -I. -I ../ -L../../dll/l64 -lTDFAPI30 extfqtdf.cpp -o ../../dll/l64/extfqtdf.so -Wno-write-strings -Wno-write-strings -Wno-unused-value
