#include<tmwp>
using namespace tmwp;
void getCityView_TPL(Request &request,Response &response)
{
response.write("<!DOCTYPE HTML>");
response.write("<head>");
response.write("<meta charset='utf8'>");
response.write("<title>Error Page</title>");
response.write("</head>");
response.write("<body>");
response.write("");
response.write(request.getValue("error"));
response.write("<BR>");
response.write("<a href='index.html'>Home</a><BR>");
response.write("</body>");
response.write("</html>");
response.write("");
}
