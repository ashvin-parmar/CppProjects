#include<iostream>
#include<threadmanager>
using namespace std;
class aaa
{
public:
void sam(int i,int j)
{
for(int k=i;k<=j;k++) cout<<k<<" ";
}
};
class bbb
{
public:
void tom(int i,int j)
{
for(int k=i;k<=j;k++) cout<<k<<" ";
}
};
class abc
{
public:

};
void jonny(aaa& a,bbb& b)
{
a.sam(1000,23400);
b.tom(300,4040);
}void doSomething(int s,int e)
{
for(int i=s;i<=e;i++) cout<<i<<" ";
}
int main()
{
abc c;
aaa a;
bbb b;

ThreadManager<void (*)(aaa&,bbb&),aaa&,bbb&> threadManager(jonny,a,b);
cout<<"About to start"<<endl;
threadManager.start();
for(int i=1000;i<1500;i++) cout<<i<<" ";
cout<<endl;
return 0;
}
