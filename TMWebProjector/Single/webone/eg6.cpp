#include<iostream>
#include<tmwp>
using namespace std;
using namespace tmwp;
void doSomething(Request &request,Response &response)
{
cout<<"Function got called"<<endl;
string ct=request.get("ct");
if(ct.size()==0) cout<<"ct does not exist as variable"<<endl;
else cout<<"ct Method Data: "<<ct<<endl;
}
int main()
{
TMWebProjector server(8080);

server.onRequest("/register",doSomething);
server.start();

return 0;
}
