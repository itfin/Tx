gcc -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -I. -I ../ -L../../dll/l64 -lthostmduserapi extfqctp.cpp -o ../../dll/l64/extfqctp.so -Wno-write-strings -Wno-write-strings
gcc -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -I. -I ../ -L../../dll/l64 -lthosttraderapi extfectp.cpp -o ../../dll/l64/extfectp.so -Wno-write-strings -Wno-write-strings
