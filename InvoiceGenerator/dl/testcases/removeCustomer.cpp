#include<iostream>
#include<dl/customer>
#include<dl/customermanager>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
Customer customer;
CustomerManager customerManager;
string email;
cout<<"Enter email: ";
getline(cin,email);
try
{
customerManager.removeCustomer(email);
cout<<"Customer removed"<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}