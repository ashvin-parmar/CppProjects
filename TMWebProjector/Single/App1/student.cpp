//HERE ARE MY BASIC STUDENT APPLICATION OF CRUD APPLICATION
//BEHIND THIS APPLICATION, MY OWN WEB SERVER IS WORKING

SEE YOU!

#include<tmwp>		//Web Server Library used
#include<iostream>
#include<string.h>
using namespace std;
using namespace tmwp;
typedef struct __student
{
char name[51];
int rollNumber;
}Student;
string fileName="student.dat";	//Global to use in all functions

void addStud(Request &request,Response &response)	//WE have chose those parameter because
{
//Here all functionality of store data from file and searching for already available data in file 
//And respective error handling part are covered
printf("Add Student called\n");
FILE *f;
f=fopen(fileName.c_str(),"rb");
if(f==NULL) return;
Student student;
while(1)
{
fread(&student,1,sizeof(Student),f);
if(feof(f)) break;
if(student.rollNumber==atoi(request.get("rl").c_str())) 
{
response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("Student with same roll Number are already exist");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
fclose(f);
return;
}
}
fclose(f);
f=fopen(fileName.c_str(),"ab");
string name=request.get("nm");
if(name.size()>50) 
{
response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("Student name size should be lesser than 50");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
fclose(f);
return;
}
strcpy(student.name,name.c_str());
student.rollNumber=atoi(request.get("rl").c_str());
fwrite(&student,1,sizeof(Student),f);
//Response Page
response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("Student Data Saved");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
fclose(f);
}
void getStud(Request &request,Response &response)
{
//Here data serched in file and taken from file if available or error hadling part
printf("get Student called\n");	//To Check functionality work or not
FILE *f;
f=fopen(fileName.c_str(),"rb");
if(f==NULL) return;
Student student;
response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("<table border='1'>");
response.write("<tr>");
response.write("<th>S_no</th>");
response.write("<th>Roll_number</th>");
response.write("<th>Name</th>");
response.write("</tr>");
int x=0;
char tmp[200];
while(1)
{
fread(&student,1,sizeof(Student),f);
if(feof(f)) break;
response.write("<tr>");
sprintf(tmp,"<td>%d</td>",++x);
response.write(tmp);
sprintf(tmp,"<td>%d</td>",student.rollNumber);
response.write(tmp);
sprintf(tmp,"<td>%s</td>",student.name);
response.write(tmp);
response.write("</tr>");
//printf("Student name: %s\n",student.name);
//printf("Student rollNumber: %d\n",student.rollNumber);
}
if(x==0) 
{
response.write("<tr>");
response.write("<td>There are zero Student record available</td>");
response.write("</tr>");
}
response.write("</table>");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
fclose(f);
}
int main()
{
FILE *f;
f=fopen(fileName.c_str(),"rb");
if(f==NULL)
{
f=fopen(fileName.c_str(),"wb");
if(f==NULL)
{
printf("Some Problems\n");
return 0;
}
}
fclose(f);

TMWebProjector server(4040);	//Let's we have choose 4040 port to test our student project
server.onRequest("/getStudent",getStud); //Means (if request arrived for getAllStudent then this functionality getStud called)
server.onRequest("/addStudent",addStud);  //Means (If request arrived for '/AddStudent' then this function 'addStud' are called)

server.start();
return 0;
}