#include<iostream>
#include<ctime>
#include<tmwp>
using namespace std;
using namespace tmwp;
void getCityView(Request &request,Response &response)
{
string cityCodeString=request.get("cityCode");
int cityCode=atoi(cityCodeString.c_str());
if(cityCode==1) request.forward("Ujjain.html");
else if(cityCode==2) request.forward("Indore.html");
else if(cityCode==3) request.forward("Dewas.html");
else 
{
request.set("error","Invalid Code");
request.forward("errorPage");
}
}
void errorMsg(Request &request,Response &response)
{
cout<<"errorMsg called"<<endl;
string msg=request.get("error");
cout<<"get value is : "<<msg<<endl;
cout<<"For now, We are sending it to index page"<<endl;
request.forward("index.html");
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/getCity",getCityView);
server.onRequest("/errorPage",errorMsg);

server.start();

return 0;
}
