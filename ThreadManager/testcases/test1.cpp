#include<iostream>
#include<threadmanager>
using namespace std;
void doSomething(int s,int e)
{
for(int i=s;i<=e;i++) cout<<i<<" ";
}
int main()
{
ThreadManager<void (*)(int,int),int,int> threadManager(doSomething,1,5000);
cout<<"About to start"<<endl;
threadManager.start();
for(int i=10000;i<15000;i++) cout<<i<<" ";
cout<<endl;
return 0;
}
