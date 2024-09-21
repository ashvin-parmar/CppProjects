#include<iostream>
#include<tmwp>
using namespace std;
using namespace tmwp;
void doSomething(Request &request,Response &response)
{
string n=request.get("nm");
string c=request.get("ct");

response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("Hello");
response.write(n);
response.write("<BR>");
response.write("Data Saved");
response.write("</body>");
response.write("</html>");
response.sendResponse();

}
int main()
{
TMWebProjector server(8080);

server.onRequest("/register",doSomething);
server.start();

return 0;
}
