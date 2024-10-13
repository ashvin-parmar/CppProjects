#include<iostream>
#include <cctype>
using namespace std;
bool isAlphaNum(char m)
{
return (m>=97 && m<=122) || (m>=65 && m<=90) || (m>=48 && m<=57);
}
int validateEmail(string &email)
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
int main()
{
string email;
cout<<"Enter email: ";
getline(cin,email);
cout<<"Validate Email: "<<validateEmail(email)<<endl;
return 0;
}