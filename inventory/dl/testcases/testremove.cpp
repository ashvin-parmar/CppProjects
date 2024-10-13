#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;
int code;
cout<<"Enter code: ";
cin>>code;
try
{
unitOfMeasurementDAO.remove(code);
cout<<"Data deleted successfully"<<endl; 
}catch(DAOException &b)
{
cout<<b.what()<<endl;
}
return 0;
}