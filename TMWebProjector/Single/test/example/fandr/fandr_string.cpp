//Find and remove '${x}' with given STRING type value

#include<stdio.h>
#include<iostream>
#include<map>
#include<string.h>
using namespace std;
void findAndReplce(string fileName,map<string,string> &variable)
{
FILE *f;
f=fopen(fileName.c_str(),"r");
FILE *tmp;
tmp=fopen("tmp.tmp","w");
if(f==NULL)
{
cout<<"Unable to open file"<<endl;
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
}
int main()
{
string fileName;
cout<<"Enter file name: ";
getline(cin,fileName);
map<string,string> variablesMap;
while(1)
{
cout<<"Enter variable name: ";
string variable;
getline(cin,variable);
string value;
cout<<"Enter value(STRING): ";
getline(cin,value);
variablesMap.insert(pair<string,string>(variable,value));
cout<<"Want to enter more variable (Y/N): ";
char m;
cin>>m;
cin.ignore(1000,'\n');
if(m!='y' && m!='Y') break;
}
findAndReplce(fileName,variablesMap);
return 0;
}
