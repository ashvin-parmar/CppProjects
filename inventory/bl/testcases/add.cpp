#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
#include<dl/daoexception>
#include<dl/uomdao>
#include<dl/uom>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
string title;
cout<<"Enter Unit Of Measurement: ";
cin>>title;
cout<<title<<endl;
try
{
UnitOfMeasurement *unitOfMeasurement;
UnitOfMeasurementManager unitOfMeasurementManager;
unitOfMeasurement->setTitle(title);
cout<<unitOfMeasurement->getTitle()<<endl;
unitOfMeasurementManager.addUnitOfMeasurement(unitOfMeasurement);
}catch(BLException blException)
{
cout<<blException.what()<<endl;
}catch(inventory::data_layer::DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}
return 0;
}
