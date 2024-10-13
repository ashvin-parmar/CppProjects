#include<iostream>
#include<tmwp>
using namespace std;
using namespace tmwp;
void doSomething(Request &request,Response &response)
{
cout<<"Function got called"<<endl;
map<string *,string *> *data;
map<string *,string *>::iterator i;
data=request.getData();
for(i=data->begin();i!=data->end();i++)
{
cout<<"Vaiable: "<<*(i->first)<<" , Data: "<<*(i->second)<<endl;
delete i->first;
delete i->second;
}
delete data;
}
int main()
{
TMWebProjector server(8080);

server.onRequest("/register",doSomething);
server.start();

return 0;
}
