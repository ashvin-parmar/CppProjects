#include<iostream>
#include<map>
#include<cstring>
using namespace std;
map<string,string> * getFuncNames(string filename)
{
FILE *f;
map<string,string> *funcnames;
funcnames=new map<string,string>;
f=fopen(filename.c_str(),"r");
if(f==NULL) return NULL;
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
if(line.find("forward")!=std::string::npos && line.find(".tpl")!=std::string::npos)
{
if(x==1) 
{
string forw;
size_t pos=line.find(".tpl");
pos--;
while(line[pos]!='"' && pos>=0)
{
forw.insert(0,1,line[pos]);
pos--;
}
funcnames->insert(pair<string,string>(forw,funcname));
funcname.clear();
x=0;
}
}
if(line.find("void")!=std::string::npos && line.find("Request")!=std::string::npos && line.find("Response")!=std::string::npos)
{
int index=0;
for(;index<line.size() && line[index]!=' ';index++); 
index++;
funcname.clear();
for(;index<line.size() && line[index]!='(';index++)
{
funcname.push_back(line[index]);
}
x=1;
}
if(feof(f)) break;
}
fclose(f);
return funcnames;
}
void createTMP(string fileName)
{
FILE *f;
f=fopen(fileName.c_str(),"r");
if(f==NULL)
{
return ;
}
FILE *tmp;
tmp=fopen((fileName.substr(0,fileName.size()-3)+string("tmp")).c_str(),"w");
if(tmp==NULL)
{
fclose(f);
return ;
}
int track;
while(1)
{
track=ftell(f);
char m=fgetc(f);
if(feof(f)) break;
string buffer;
if(m=='$')
{
m=fgetc(f);
if(feof(f)) break; 
if(m=='{')
{
m=fgetc(f);
if(feof(f)==EOF) break;
string s;
while(m!='}')
{
s.push_back(m);
m=fgetc(f);
if(feof(f)) break;
}
if(feof(f)) 
{
fputc('$',tmp);
fseek(f,track+1,0);
continue;
}
fputc('\n',tmp);
char buff[100];
sprintf(buff,"request.getValue(\"%s\")",s.c_str());
fwrite(buff,sizeof(char),strlen(buff),tmp);
fputc('\n',tmp);
}
else
{
fputc('$',tmp);
fseek(f,track+1,0);
}
}
else
{
fputc(m,tmp);
}
}//While loop ends here
fclose(tmp);
fclose(f);
}
void tpl2c(string filename)
{
FILE *h;
h=fopen("tpl.h","w");
if(h==NULL)
{
printf("tpl.h file not opened\n");
return ;
}

char buff[1000];
sprintf(buff,"#ifndef __TMWP_H\n#define __TMWP_H\n#include<tmwp>\nusing namespce tmwp;\n");
fwrite(buff,sizeof(char),strlen(buff),h);
map<string,string> *data;
data=getFuncNames(filename);
for(pair<string,string> a:*data)
{
sprintf(buff,"void %s_TPL(Request &request,Response &response);\n",a.second.c_str());
fwrite(buff,sizeof(char),strlen(buff),h);
}
sprintf(buff,"void registerTPLs(TMWebProjector *server)\n{\n");
fwrite(buff,sizeof(char),strlen(buff),h);
for(pair<string,string> a:*data)
{
sprintf(buff,"server->onRequest(\"%s.tpl\",%s_TPL);\n",a.first.c_str(),a.second.c_str());
fwrite(buff,sizeof(char),strlen(buff),h);
}
sprintf(buff,"}\n#endif\n");
fwrite(buff,sizeof(char),strlen(buff),h);
fclose(h);

for(pair<string,string> a:*data)
{
FILE *cpp;
createTMP(a.first+string(".tpl"));
FILE *f;
f=fopen(((a.first)+string(".tmp")).c_str(),"r");
if(f==NULL)
{
continue;
}
cpp=fopen((a.first+string(".tpl.cpp")).c_str(),"w");
if(cpp==NULL)
{
continue;
}
sprintf(buff,"#include<tmwp>\nusing namespace tmwp;\n");
fwrite(buff,(strlen(buff)),sizeof(char),cpp);
sprintf(buff,"void %s_TPL(Request &request,Response &response)\n{\n",a.second.c_str());
fwrite(buff,strlen(buff),sizeof(char),cpp);
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
sprintf(buff,"response.write(\"%s\");\n",line.c_str());
fwrite(buff,sizeof(char),strlen(buff),cpp);
if(feof(f)) break;
}
fclose(f);
f=fopen(((a.first)+string(".tmp")).c_str(),"w");
fclose(f);
sprintf(buff,"}\n");
fwrite(buff,sizeof(char),strlen(buff),cpp);
fclose(cpp);
}//funcMap
delete data;
}
int main()
{
string filename;
cout<<"Enter file name: ";
getline(cin,filename);
tpl2c(filename);
return 0;
}

