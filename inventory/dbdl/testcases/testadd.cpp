#include<iostream>
#include<dbdl/uomdao>
#include<dbdl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer_db;
int main()
{
UnitOfMeasurement m;
UnitOfMeasurementDAO unitOfMeasurement;
string a;
cout<<"Enter title: ";
getline(cin,a);
m.setTitle(a);
try
{
unitOfMeasurement.add(&m);
cout<<"Unit of measurement added with code as: "<<m.getCode()<<endl;
}catch(DAOException &d)
{
cout<<d.what()<<endl;
}
return 0;
}