gcc -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -I. -I ../ -L../../dll/l64 -lthostmduserapim extfqctpm.cpp -o ../../dll/l64/extfqctpm.so -Wno-write-strings -Wno-write-strings
gcc -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -I. -I ../ -L../../dll/l64 -lthosttraderapim extfectpm.cpp -o ../../dll/l64/extfectpm.so -Wno-write-strings -Wno-write-strings
