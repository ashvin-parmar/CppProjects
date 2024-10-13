g++ -c TMWP.cpp -I ..\include -I e:\CppProject\URLDecoder\include
del ..\lib\tmwp.lib
ar rcs tmwp.lib *.o e:\CppProject\URLDecoder\src\*.o
move tmwp.lib ..\lib