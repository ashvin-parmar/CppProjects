#include<iostream>
using namespace std;

int isValidateIndianContactNumber(const string &contactNumber)
{

//situation=0 invalid
//situation=1 +91 formate
//situation=2 leading with 0 formate
//situation=3 10 digit contact number

if(contactNumber.size()<10 || contactNumber.size()>13 || contactNumber.size()==12) return false;
int i=0;
int situation;
cout<<contactNumber.size()<<endl;
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
return situation ;
}
string validateContactNumber(const string &contactNumber)
{
string vContactNumber=contactNumber;
int situation ;
situation=isValidateIndianContactNumber(vContactNumber);
cout<<situation<<endl;
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

int main()
{
string contact;
cout<<"ENter contact Number: ";
cin>>contact;
string vContactNumber=validateContactNumber(contact);
cout<<"Contact Number : "<<vContactNumber<<endl;
return 0;
}