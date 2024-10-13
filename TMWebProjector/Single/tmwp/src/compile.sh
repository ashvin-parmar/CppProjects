g++ -c TMWP_Linux.cpp -I ../include -I ./../../../../URLDecoder/include
rm ./../lib/libtmwp.a
ar rcs ./../lib/libtmwp.a TMWP_Linux.o ./../../../../URLDecoder/src/*.o
