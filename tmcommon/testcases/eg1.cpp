#include<iostream>
#include<common/stringutils>
using namespace stringutils;
using namespace std;
int main()
{
string a;
cout<<"Enter string: ";
cin>>a;
string b;
cout<<validateEmail(a)<<endl;

return 0;
}