#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
void createH(string filename,vector<string> &funcnames)
{
FILE *f;
FILE *h;
char *buffer;
f=fopen(filename.c_str(),"r");
if(f==NULL) return;
int x=0;
string funcname;
while(1)
{
char c;
string line;
while(1)
{
c=fgetc(f);
if(feof(f)) break;
if(c=='\n') break;
line.push_back(c);
}
//cout<<"Line: "<<line<<endl;
if(line.find("forward")!=std::string::npos && line.find(".tpl")!=std::string::npos)
{
//cout<<"FORWARD"<<endl;
if(x==1) 
{
funcnames.push_back(funcname);
funcname.clear();
x=0;
}
}
if(line.find("void")!=std::string::npos && line.find("Request")!=std::string::npos && line.find("Response")!=std::string::npos)
{
//cout<<"FUNCTION"<<endl;
int index=0;
for(;index<line.size() && line[index]!=' ';index++); 
index++;
funcname.clear();
for(;index<line.size() && line[index]!='(';index++)
{
funcname.push_back(line[index]);
}
x=1;
//cout<<funcname<<endl;
}
if(feof(f)) break;
}
fclose(f);
//fclose(h);
//cout<<"Size of func: "<<funcnames.size()<<endl;
}
int main()
{
vector<string> funcname;
//funcname=new vector<string>;
cout<<"Enter filename: ";
string filename;
getline(cin,filename);
createH(filename,funcname);
for(string i:funcname)
{
cout<<i<<endl;
}
return 0;
}
