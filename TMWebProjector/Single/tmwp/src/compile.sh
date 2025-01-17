g++ -c TMWP_Linux.cpp -I ../include -I ../../../../ThreadManager/include/ -I ../../../../URLDecoder/include/ -L ../../../../ThreadManager/lib/ -l threadmanager
export LD_LIBRARY_PATH=../../../../ThreadManager/lib/.:$LD_LIBRARY_PATH
rm ./../lib/libtmwp.a
ar rcs ./../lib/libtmwp.a TMWP_Linux.o ./../../../../URLDecoder/src/*.o
