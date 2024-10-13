#include<iostream>
#include<ctime>
#include<tmwp>
using namespace std;
using namespace tmwp;
void saveEnquiry(Request &request,Response &response)
{
string n=request.get("nm");
string c=request.get("ct");
string q=request.get("msg");
string a=request.get("address");

cout<<"Data recived"<<endl;
cout<<"Name: "<<n<<endl;
cout<<"Address: "<<a<<endl;
cout<<"City: "<<c<<endl;
cout<<"Query: "<<q<<endl;
//Some proccess done here to save data in file

request.forward("saveNotification.html");
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/addEnquiry",saveEnquiry);

server.start();

return 0;
}