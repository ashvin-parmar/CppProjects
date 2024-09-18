#include<tmwp>
#include<iostream>
using namespace std;
using namespace tmwp;
void addStud(Request &request,Response &response)
{

}
void getAllStudent(Request &request,Response &response)
{

}
int main()
{
TMWebProjector server(8080);
server.onRequest("/addStudent",addStud);
server.onRequest("/getStudents",getAllStudent);
server.start();
return 0;
}