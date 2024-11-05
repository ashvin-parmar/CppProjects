#include "tpl.h"
#include<iostream>
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
request.setKeyValue("error","Invalid Code, Please try again");
request.forward("errorPage.tpl");
x++;
}
}

void Hii(Request &request,Response &response)
{

}
void Hello(Request &request,Response &response)
{
request.forward("hii.tpl");
}
void Greate(Request &request,Response &response)
{
request.forward("hii.ppl");
}
void nice(Request &res,Response &respons)
{
request.forward(".tpl")
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/getCity",getCityView);
registerTPLs(&server);
server.start();

return 0;
}
