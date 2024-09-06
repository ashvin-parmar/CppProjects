#include<tmwp>
#include<iostream>
using namespace tmwp;
using namespace std;
void doSomething()
{
cout<<"Respective function got called"<<endl;
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/ttt",doSomething);
server.start();
return 0;
}