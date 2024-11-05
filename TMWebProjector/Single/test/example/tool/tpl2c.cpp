#include<iostream>
#include<map>
#include<cstring>
using namespace std;

map<string,string> * getFuncNames(string filename)
{
FILE *f;
map<string,string> *funcnames;
funcnames=new map<string,string>;
//FILE *h;
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
//cout<<"Line: "<<line<<endl;
if(line.find("forward")!=std::string::npos && line.find(".tpl")!=std::string::npos)
{
//cout<<"FORWARD"<<endl;
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
return funcnames;
}
void createH(string filename)
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
sprintf(buff,"server->onRequest(\"%s.tpl.cpp\",%s_TPL);\n",a.first.c_str(),a.second.c_str());
fwrite(buff,sizeof(char),strlen(buff),h);
}
sprintf(buff,"}\n#endif\n");
fwrite(buff,sizeof(char),strlen(buff),h);

fclose(h);
}
void createCPP(string fileName)
{

FILE *cpp;
cpp=fopen((fileName+string(".cpp")).c_str(),"w");
if(cpp==NULL)
{
return ;
}

char buff[1000];
sprintf(buff,"#include<tmwp>\nusing namespace tmwp;\n");
fwrite(buff,(strlen(buff)),sizeof(char),cpp);



fclose(cpp);
}


void tpl2c(string fileName)
{
FILE *f;
f=fopen(fileName.c_str(),"r");
if(f==NULL)
{
cout<<"Unable to open file"<<endl;
return ;
}
FILE *tmp;
tmp=fopen("tmp.tmp","w");
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
/*
if(i!=variable.end())
{
for(int j=0;j<i->second.size();j++) fputc(i->second[j],tmp);
fseek(f,track+s.size()+3,0);
}
else
{
fputc('$',tmp);
fseek(f,track+1,0);
}
*/
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
createCPP(fileName);
/*
tmp=fopen("tmp.tmp","r");
f=fopen(fileName.c_str(),"w");
fseek(tmp,0,0);
fseek(f,0,0);
while(1)
{
char m=fgetc(tmp);
if(feof(tmp)) break;
fputc(m,f);
}
fclose(tmp);
fclose(f);
tmp=fopen("tmp.tmp","w");
fclose(tmp);
*/
}



void tpl2c_1(string fileName,map<string,string> &variable)
{
FILE *f;
f=fopen(fileName.c_str(),"r");
if(f==NULL)
{
cout<<"Unable to open file"<<endl;
return ;
}
FILE *cpp;
FILE *tmp;
cpp=fopen((fileName+string(".cpp")).c_str(),"w");
if(cpp==NULL) 
{
fclose(f);
return ;
}
tmp=fopen("tmp.tmp","w");
if(tmp==NULL)
{
fclose(cpp);
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
map<string,string>::iterator i;
i=variable.find(s);
if(i!=variable.end())
{
for(int j=0;j<i->second.size();j++) fputc(i->second[j],tmp);
fseek(f,track+s.size()+3,0);
}
else
{
fputc('$',tmp);
fseek(f,track+1,0);
}
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

char buff[1000];
sprintf(buff,"#include<tmwp>\nusing namespace tmwp;\n");
fwrite(buff,(strlen(buff)),sizeof(char),cpp);
fclose(cpp);




/*
tmp=fopen("tmp.tmp","r");
f=fopen(fileName.c_str(),"w");
fseek(tmp,0,0);
fseek(f,0,0);
while(1)
{
char m=fgetc(tmp);
if(feof(tmp)) break;
fputc(m,f);
}
fclose(tmp);
fclose(f);
tmp=fopen("tmp.tmp","w");
fclose(tmp);
*/

}
int main()
{
string filename;
cout<<"Enter file name: ";
getline(cin,filename);
map<string,string> keyValueMap;
while(1)
{
/*
cout<<"Enter key: ";
string key;
getline(cin,key);
cout<<"Enter value: ";
string value;
getline(cin,value);
keyValueMap.insert(pair<string,string>(key,value));
*/
char c;
cout<<"Want to enter more values: ";
cin>>c;
cin.ignore(100,'\n');
if(c!='y' && c!='Y') break;

}
//tpl2c_1(filename,keyValueMap);
createH(filename);
return 0;
}
