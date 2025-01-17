#include"tpl.h"
#include<iostream>
#include<ctime>
#include<tmwp>
using namespace std;
using namespace tmwp;
void __getCityView_TPL(Request &request,Response &response)
{
response.write("<!DOCTYPE HTML>");
response.write("<head>");
response.write("<meta charset='utf8'>");
response.write("<title>Error Page</title>");
response.write("</head>");
response.write("<body>");
response.write("");
response.write(request.getValue("error"));
printf("%s\n",request.getValue("error").c_str());
response.write("<BR>");
response.write("<a href='index.html'>Home</a><BR>");
response.write("</body>");
response.write("</html>");
response.write("");
}
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
}
}
int main()
{
TMWebProjector server(4040);
server.onRequest("/getCity",getCityView);
registerTPLs(&server);
server.start();
return 0;
}
