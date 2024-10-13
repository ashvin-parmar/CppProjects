#include<iostream>
#include<ctime>
#include<tmwp>
using namespace std;
using namespace tmwp;
void dispatchTime(Request &request,Response &response)
{
time_t t=time(0);
char *now=ctime(&t);
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>The Clock</title>");
response.write("</head>");
response.write("<body>");
response.write("<h1>");
response.write(now);
response.write("</h1>");
response.write("<a href='now'>Refresh</a><br>");
response.write("<a href='index.html'>HOME</a><br>");
response.write("</body>");
response.write("</html>");
response.close();

}
void clock(Request &request,Response &response)
{
request.forward("/now");
request.forward("/clock");
}

int main()
{
TMWebProjector server(8080);
server.onRequest("/now",dispatchTime);
server.onRequest("/clock",clock);
server.start();

return 0;
}