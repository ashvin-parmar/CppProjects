#include<iostream>
using namespace std;

string validateEmail(string &email)
{
string::iterator i;
if(email.size()==0) return string("");
for(i=email.begin();i!=email.end();i++)
{
if(email[i]=='@') break;
}
if(i==email.end()) return string("");
string username;
string domain;
username.insert(0,email,)

}


int main()
{
string email;
cout<<"Enter email: ";
getline(cin,email);
cout<<"Validate Email: "<<validateEmail(email)<<endl;
return 0;
}