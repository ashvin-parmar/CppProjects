#include<iostream>
#include<stringutils>
using namespace std;
string stringutils::trimmed(const string &s)
{
int e,f,len;
len=s.length();
if(len==0) return string("");
for(e=0;s[e]==' ' && e<len;e++);
if(e==len) return string("");
for(f=len-1;s[f]==' ';f--);
char *c;
c=new char[f-e+1];
int k=0;
while(e<=f)
{
c[k]=s[e];
e++;
k++;
}
c[k]='\0';
string str(c);
delete [] c;
return str;
}
int stringutils::compareStringIgnoreCase(const char *a,const char *b)
{
if(a==b) return 0;
if(a==NULL) return -1;
if(b==NULL)return 1;
char c,d;
for(;*a && *b;a++,b++)
{
c=*a;
if(c<=122 && c>=97) c=c-32;
d=*b;
if(d<=122 && d>=97) d=d-32;
if(c!=d) return c-d;
}
if(*a==*b) return 0;
c=*a;
if(c>=97 && c<=122) c=c-32;
d=*b;
if(d>=97 && d<=122) d=d-32;
return c-d;
}