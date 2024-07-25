#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
#include<dl/daoexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
string title;
cout<<"Enter Unit Of Measurement: ";
cin>>title;
try
{
UnitOfMeasurement *unitOfMeasurement;
UnitOfMeasurementManager unitOfMeasurementManager;
unitOfMeasurement->setTitle(title);
unitOfMeasurementManager.addUnitOfMeasurement(unitOfMeasurement);
}catch(BLException &blException)
{
cout<<blException.what()<<endl;
}
catch(inventory::data_layer::DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}
