Name: Ashvin Parmar
Subject: C++
Lecture: C++ 114
Topic: Find and Replace specific words (VARIABLE) with INT type values
Assignment: Find and replace keywords
========================================================

//Lecture: C++ 114
//Problem: Find and Replace specific words (VARIABLE) with INT type values

//Find and replace '${VARIABLE}' with given INT type value

#include<stdio.h>
#include<iostream>
#include<map>
#include<string.h>
using namespace std;
void findAndReplce(string fileName,map<string,int> &variable)
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
map<string,int>::iterator i;
i=variable.find(s);
if(i!=variable.end())
{
char value[11];
sprintf(value,"%d",i->second);
int size=strlen(value);
for(int i=0;i<size;i++) fputc(value[i],tmp);
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
map<string,int> variablesMap;
while(1)
{
cout<<"Enter variable name: ";
string variable;
getline(cin,variable);
cout<<"Enter value(INT): ";
int value;
cin>>value;
cin.ignore(1000,'\n');
variablesMap.insert(pair<string,int>(variable,value));
cout<<"Want to enter more variable (Y/N): ";
char m;
cin>>m;
cin.ignore(1000,'\n');
if(m!='y' && m!='Y') break;
}
findAndReplce(fileName,variablesMap);
return 0;
}

============================================================

//TestCase Only for Abhishek Bhaiya ke liye
fileName: "xyz.dat"
File-Content: 
"
abcdefghijklmnopqrstuvwxyzABCDEFGHe${x}dqpwfinpq2 hfgp${y}pansdpfifh${ABCD}dqefgqafgdwqegmweqgEG

wrqerhwrgbwifoiab${fmd} AFMPFPQA <Cacfm${cam;fcoeacecpn}damlfmamf${fmafmopafocmaslm;f    ${XYZ}
daslffmmpn ckasnnc@}$$afjaof${camscop} fafnopJ${dasf${DFLM	asf'kasf
"

TestCase: (Like This)
Enter file name: xyz.dat
Enter variable name: x
Enter value(INT): 256
Want to enter more variable (Y/N): y
Enter variable name: y
Enter value(INT): 21341
Want to enter more variable (Y/N): n
============================================================