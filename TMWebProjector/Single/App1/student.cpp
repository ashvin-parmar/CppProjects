//HERE ARE MY BASIC STUDENT APPLICATION OF CRUD APPLICATION
//BEHIND THIS APPLICATION, MY OWN WEB SERVER IS WORKING

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
string fileName="student.dat";	
void addStud(Request &request,Response &response)
{
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
response.write("<body>");
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
printf("get Student called\n");	
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
void editStud(Request &request,Response &response)
{
//HERE WE ARE SERCHING DATA FROM FILE THAT ROLL NUMBER IS EXIST OR NOT

FILE *f;
f=fopen(fileName.c_str(),"rb");
if(f==NULL) return;		//THIS IS HARD TO NOT OPEN
Student student;
char tmp[200];
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
response.write("<body>");
response.write("Student (Edit Module)");
response.write("<form method='get' action='updateStudent'>");
sprintf(tmp,"Roll Number <input type='text' id='rl' name='rl' value='%d'><br>",student.rollNumber);
response.write(tmp);
sprintf(tmp,"Previous Name <input type='text'  value='%s'><br>",student.name);
response.write(tmp);
response.write("New Name <input type ='text' id='nm' name='nm' ><br>");
response.write("<button type='submit'>Update </button>");
response.write("</form>");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
fclose(f);
return;
}
}
response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("<body>");
response.write("Student with given roll number is not available");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
fclose(f);
}

void updateStud(Request &request,Response &response)
{
//HERE WE ARE SERCHING DATA FROM FILE THAT ROLL NUMBER IS EXIST OR NOT

FILE *f;
f=fopen(fileName.c_str(),"rb+");
if(f==NULL) return;		//THIS IS HARD TO NOT OPEN
Student student;
char tmp[200];
int track;
while(1)
{
track=ftell(f);		//To Track location of student
fread(&student,1,sizeof(Student),f);
if(feof(f)) break;
if(student.rollNumber==atoi(request.get("rl").c_str())) 
{
string name=request.get("nm");
fseek(f,track,0);
strcpy(student.name,name.c_str());
fwrite(&student,1,sizeof(Student),f);
response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("<body>");
response.write("Student Updated");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
fclose(f);
response.sendResponse();
return ;
}
}
}
void confirmDeleteStud(Request &request,Response &response)
{
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
response.write("<body>");
response.write("Student Deleted Module");
response.write("<form method='get' action='deleteStudent'>");
char tmp[200];
sprintf(tmp,"Roll Number :%d",student.rollNumber);
response.write(tmp);
sprintf(tmp,"<input type='hidden' id='rl' name='rl' value='%d'><br>",atoi(request.get("rl").c_str()));
response.write(tmp);
sprintf(tmp,"Name : %s",student.name);
response.write(tmp);
response.write("<button type='subtmi'>Delete</button>");
response.write("</form>");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
fclose(f);
return ;
}
}
response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("<body>");
response.write("Student Not Found<BR>");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
fclose(f);
return ;
}
void deleteStud(Request &request,Response &response)
{
FILE *f, *t;
f=fopen(fileName.c_str(),"rb");
t=fopen("tmp.tmp","wb");
if(f==NULL) return;		
Student student;
while(1)
{
fread(&student,1,sizeof(Student),f);
if(feof(f)) break;
if(student.rollNumber!=atoi(request.get("rl").c_str())) 
{
fwrite(&student,1,sizeof(Student),t);
}
}
fclose(f);
fclose(t);
f=fopen(fileName.c_str(),"wb");
t=fopen("tmp.tmp","rb");
while(1)
{
fread(&student,1,sizeof(Student),t);
if(feof(t)) break;
fwrite(&student,1,sizeof(Student),f);
}
fclose(f);
fclose(t);
f=fopen("tmp.tmp","wb");
fclose(f);			//To clear "tmp.tmp" file
response.write("<!DOCTYPE HTML>");
response.write("<HTML lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>Whatever</title>");
response.write("</head>");
response.write("<body>");
response.write("Student Deleted<BR>");
response.write("<a href='index.html'>HOME</a>");
response.write("</body>");
response.write("</html>");
response.sendResponse();
return ;
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
server.onRequest("/editStudent",editStud); //Means (If request arrived for '/editStudent' then this function 'editStud' are called)
server.onRequest("/updateStudent",updateStud);
server.onRequest("/confirmDeleteStudent",confirmDeleteStud);
server.onRequest("/deleteStudent",deleteStud);
server.start();
return 0;
}