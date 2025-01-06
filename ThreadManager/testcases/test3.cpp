#include <iostream>
#include<threadmanager>
using namespace std;

class aaa {
public:
    void sam(int i, int j) {
        for (int k = i; k <= j; k++) cout << k << " ";
    }
};

class bbb {
public:
    void tom(int i, int j) {
        for (int k = i; k <= j; k++) cout << k << " ";
    }
};

    static void jonny(aaa& a, bbb& b) {
        a.sam(1000, 2000);
        b.tom(3000, 4000);
    }

void doSomething(int s, int e) {
    for (int i = s; i <= e; i++) cout << i << " ";
}

int main() {
    aaa a;
    bbb b;

    ThreadManager<void (*)(aaa&, bbb&), aaa&, bbb&> threadManager(jonny, std::ref(a), std::ref(b));
    cout << "About to start" << endl;
    threadManager.start();
    for (int i = 1000; i < 1500; i++) cout << i << " ";
    cout << endl;
    return 0;
}
