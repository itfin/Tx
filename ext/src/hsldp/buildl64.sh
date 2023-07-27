g++ -m64 -DJ64 -DKXVER=3 -fPIC -shared  -I. -I ../ -L../../dll/l64 extfeldp.cpp -o ../../dll/l64/extfeldp.so -Wno-write-strings -Wno-write-strings -Wno-unused-value -lt2sdk_ldp -lldptcpsdk -lHSSecuTradeApi -lpthread -lm 
 
g++ -m64 -DJ64 -DKXVER=3 -fPIC -shared  -I. -I ../ -L /q/l64/ldpfut -L/q/l64 extfeldpfu.cpp -o ../../dll/l64/extfeldpfu.so -Wno-write-strings -Wno-write-strings -Wno-unused-value -lt2sdk -lldptcpsdk -lHsFutuSystemInfo -lLinuxDataCollect -lHSTradeApi -lHSMdApi -lpthread -lm

g++ -m64 -DJ64 -DKXVER=3 -fPIC -shared  -I. -I ../ -L /q/l64/ldpfut -L/q/l64 extfeldpfu.cpp -o ../../dll/l64/extfeldpfutest.so -Wno-write-strings -Wno-write-strings -Wno-unused-value -lt2sdk -lldptcpsdk -lHsFutuSystemInfo.x64test -lLinuxDataCollectTest -lHSTradeApi -lHSMdApi -lpthread -lm
