#include<iostream>
#include<dbdl/uomdao>
#include<dbdl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer_db;
int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;
UnitOfMeasurement unitOfMeasurement;
int code;
cout<<"Enter code: ";
cin>>code;
cin.ignore(1000,'\n');
string title;
cout<<"Enter title: ";
getline(cin,title);
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