#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;
UnitOfMeasurement unitOfMeasurement;
int code;
string title;
cout<<"Enter title: ";
cin>>title;
cout<<"Enter code: ";
cin>>code;
try
{
unitOfMeasurement.setCode(code);
unitOfMeasurement.setTitle(title);
unitOfMeasurementDAO.update(&unitOfMeasurement);
cout<<"Data updated successfully"<<endl; 
}catch(DAOException &b)
{
cout<<b.what()<<endl;
}
return 0;
}