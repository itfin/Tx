clang -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -lstdc++ -Iinclude -I ../ -L../../dll/l64 -latptradeapi extfeatp.cpp -o ../../dll/l64/extfeatp.so -Wno-write-strings -Wno-invalid-source-encoding -Wno-unused-value
clang -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -lstdc++ -Iinclude -I ../ -L../../dll/l64 -lKDEncodeCli kdencode.cpp -o ../../dll/l64/kdencode.so -Wno-write-strings -Wno-invalid-source-encoding -Wno-unused-value

