clang -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -lstdc++ -Iinclude -I ../ -L../../dll/l64 -loes_api extfqkr.cpp -o ../../dll/l64/extfqkr.so -Wno-write-strings -Wno-invalid-source-encoding -Wno-unused-value
clang -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -lstdc++ -Iinclude -I ../ -L../../dll/l64 -loes_api extfekr.cpp -o ../../dll/l64/extfekr.so -Wno-write-strings -Wno-invalid-source-encoding -Wno-unused-value

