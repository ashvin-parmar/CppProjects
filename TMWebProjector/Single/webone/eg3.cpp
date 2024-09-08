#include<tmwp>
#include<iostream>
using namespace std;
using namespace tmwp;
void doSomething(int dataCount,char *data[])
{
cout<<"Function got called"<<endl;
if(dataCount>0) cout<<"Data recieved from client: "<<endl;
for(int j=0;j<dataCount;j++)
{
cout<<data[j]<<endl;
}
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/register",doSomething);
server.start();
return 0;
}