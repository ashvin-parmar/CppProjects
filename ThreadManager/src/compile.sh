g++ -c threadmanager.cpp -I ../include -Wall -Werror -fPIC
g++ -shared -o ../lib/libthreadmanager.so *.o
