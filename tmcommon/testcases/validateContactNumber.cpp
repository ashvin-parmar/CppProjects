#include<common/stringutils>
using namespace stringutils;

int main()
{
string a;
cout<<"Enter Contact Number: ";
getline(cin,a);
cout<<"Validate: "<<validateContactNumber(a)<<endl;

return 0;
}