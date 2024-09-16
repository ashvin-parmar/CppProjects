g++ -c *.cpp -I ..\include
ar rcs ..\lib\urldecoder.lib *.o
cd..
cd test
cmp