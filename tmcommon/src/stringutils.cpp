#include<iostream>
#include<common/stringutils>
using namespace std;

//String handling common functionality
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

//Internal Helping functionality
bool stringutils::isAlphaNum(char m)
{
return (m>=97 && m<=122) || (m>=65 && m<=90) || (m>=48 && m<=57);
}
bool stringutils::isValidateEmail(const string &email)
{
if(email.size()==0) return false;
size_t at_pos= email.find('@');
if (at_pos==std::string::npos || at_pos == 0 || at_pos == email.size() - 1) return false;
size_t dot_pos = email.find('.', at_pos + 1);
if(dot_pos==std::string::npos || dot_pos == email.size() - 1) return false;
// Check for invalid characters before '@'
for (size_t i=0; i<at_pos;++i) 
{
if(!isAlphaNum(email[i]) && email[i]!= '.' && email[i]!='-' && email[i]!='_') return false;
}
//Check for invalid characters after '@'
for (size_t i=at_pos+1; i<email.size();++i) 
{
if(!isAlphaNum(email[i]) && email[i]!= '.' && email[i]!='-' && email[i]!='_') return false;
}
//Check for consecutive dots
if (email.find("..")!=std::string::npos) return false;
if (email.substr(dot_pos + 1).size() < 2) return false;
return true;
}
int stringutils::isValidateIndianContactNumber(const string &contactNumber)
{

//situation=0 invalid
//situation=1 +91 formate
//situation=2 leading with 0 formate
//situation=3 10 digit contact number

if(contactNumber.size()<10 || contactNumber.size()>13 || contactNumber.size()==12) return false;
int i=0;
int situation;
if(contactNumber.size()==13) 
{
if(contactNumber[i++]!='+') return 0;
if(contactNumber[i++]!='9' && contactNumber[i++]!='1') return 0;
situation=1;
}
if(contactNumber.size()==11)
{
if(contactNumber[i++]!='0') return 0;
situation=2;
}
if(i==0) situation=3;
for(;i<contactNumber.size();i++)
{
if(contactNumber[i]<48 || contactNumber[i]>57) return 0;
}
//Check for first digit if '0'
if(contactNumber[0]=='0') return 0;
return situation ;
}
bool stringutils::isValidateGSTNumber(const string &gstNumber)
{
if(gstNumber.size()!=15) return false;
if(gstNumber[12]!='Z') return false;
for(int i=0;i<15;i++)
{
if(i==12) continue;
if(gstNumber[i]>57 || gstNumber[i]<48) return false;
}
return true;
}
bool stringutils::isValidateUPIID(const string &upiID)
{
size_t at_pos= upiID.find('@');
if (at_pos==std::string::npos || at_pos == 0 || at_pos == upiID.size() - 1) return false;
for(size_t i=0;i<upiID.size();i++)
{
if(i==at_pos) continue;
if(!isAlphaNum(upiID[i])) return false;
}
return true;
}
//Invoice Generator string handling
string stringutils::validateEmail(const string &email)
{
string vEmail=trimmed(email);
if(isValidateEmail(vEmail)) return vEmail;
else return string("");
}


string stringutils::validateContactNumber(const string &contactNumber)
{
string vContactNumber=trimmed(contactNumber);
int situation ;
situation=isValidateIndianContactNumber(vContactNumber);
if(situation==0) return string("");
else if(situation==1)
{
vContactNumber.erase(0,3);
}else if(situation==2)
{
vContactNumber.erase(0,1);
}
return vContactNumber;
}
string stringutils::validateGSTNumber(const string &gstNumber)
{
string vGSTNumber=trimmed(gstNumber);
if(!isValidateGSTNumber(vGSTNumber)) return string(""); 
return vGSTNumber;
}
string stringutils::validateUPIID(const string &upiId)
{
string vUPIID=trimmed(upiId);
if(!isValidateUPIID(vUPIID)) return string(""); 
return vUPIID;
}
