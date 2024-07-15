#include<iostream>
#include<uomdao>
#include<uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurement m;
UnitOfMeasurementDAO unitOfMeasurement;
m.setTitle(string("Gram"));
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