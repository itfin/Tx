g++ -g -m64 -DJ64 -DKXVER=3 -fPIC -shared -lm -lpthread -I. -I ../ -L../../dll/l64 -lstdc++ -lh5sdk -lf_os -lfsc_f2config -lfsc_hscommsg -lhs_best_message -lh5sdk_quotelog -lkafka_control extfqhsh5.cpp -o ../../dll/l64/extfqhsh5.so -Wno-write-strings -Wno-write-strings -Wno-unused-value -fpermissive

#g++ -g -m64 -lm -lpthread -I. -I ../ -L../../dll/l64 -lstdc++ -lh5sdk -lf_os -lfsc_f2config -lfsc_hscommsg -lhs_best_message -lh5sdk_quotelog -lkafka_control demo.cpp -o h5demo -Wno-write-strings -Wno-write-strings -Wno-unused-value     -fpermissive
