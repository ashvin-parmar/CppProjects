#include<iostream>
#include<tmwp>
using namespace std;
using namespace tmwp;
void doSomething(Request *request)
{
cout<<"Function got called"<<endl;

}
int main()
{
TMWebProjector server(8080);

server.onRequest("/register",(void (*)(void *))doSomething);
server.start();

return 0;
}
