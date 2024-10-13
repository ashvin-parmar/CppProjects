#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurement m;
UnitOfMeasurementDAO unitOfMeasurement;
string a;
cout<<"Enter title: ";
cin>>a;
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