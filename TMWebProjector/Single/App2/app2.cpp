#include<tmwp>
#include<iostream>
using namespace std;
using namespace tmwp;
void funcOne(Request &request,Response &response) //First function
{
cout<<"1 got called"<<endl;
request.forward("xyz.html");	//Forward request to xyz.html
}
void funcTwo(Request &request,Response &response)
{
cout<<"2 got called"<<endl;
request.forward("/three");	//Forward request to '/three' hyperlink
}
void funcThree(Request &request,Response &response)	//Third function p2f: pointer to function
{
cout<<"3 got called"<<endl;
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Three</title>");
response.write("</head>");
response.write("<body>");
response.write("COOL <BR>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
}
int main()
{
TMWebProjector server(8080);
server.onRequest("/one",funcOne);
server.onRequest("/two",funcTwo);
server.onRequest("/three",funcThree);
server.start();
return 0;
}