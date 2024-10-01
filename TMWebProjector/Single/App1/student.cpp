//Here we are going to create main for our application

#include<tmwp>
#include<iostream>
using namespace std;
using namespace tmwp;

void addStud(Request &request,Response &response)	//WE have chose those parameter because
{
//Here all functionality of store data from file and searching for already available data in file 
//And respective error handling part are covered
printf("Add Student called\n");
}
void getStud(Request &request,Response &response)
{
//Here data serched in file and taken from file if available or error hadling part
printf("get Student called\n");	//To Check functionality work or not

}

int main()
{
TMWebProjector server(4040);	//Let's we have choose 4040 port to test our student project
server.onRequest("/getStudent",getStud); //Means (if request arrived for getAllStudent then this functionality getStud called)
server.onRequest("/addStudent",addStud);  //Means (If request arrived for '/AddStudent' then this function 'addStud' are called)

server.start();
return 0;
}