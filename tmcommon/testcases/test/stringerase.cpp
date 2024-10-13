#include<iostream>
using namespace std;
int main()
{
string a;
cout<<"Enter string:";
cin>>a;
cout<<a<<endl;
a.erase(0,2);
cout<<a<<endl;
return 0;
}