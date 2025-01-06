#include <iostream>
#include "ThreadManager.h"

using namespace std;

class aaa {
public:
    void sam(int i, int j) {
        for (int k = i; k <= j; k++) cout << k << " ";
        cout << endl;
    }
};

class bbb {
public:
    void tom(int i, int j) {
        for (int k = i; k <= j; k++) cout << k << " ";
        cout << endl;
    }
};

    void jonny(aaa& a, bbb& b) {
        a.sam(100, 2000);
        b.tom(3000, 4000);
    }

int main() {
    aaa a;
    bbb b;
//abc c;
    ThreadManager<void(*)(aaa&, bbb&), aaa&, bbb&> threadManager(jonny, a, b);
    cout << "About to start" << endl;
    threadManager.start();

    for (int i = 10000; i < 15000; i++) cout << i << " ";
    cout << endl;

    return 0;
}
