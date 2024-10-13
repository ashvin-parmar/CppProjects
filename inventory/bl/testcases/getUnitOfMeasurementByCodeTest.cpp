#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/iuom>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
int code;
cout<<"Enter code to search: ";
cin>>code;
cin.ignore(1000,'\n');
UnitOfMeasurementManager unitOfMeasurementManager;
abc::IUnitOfMeasurement *unitOfMeasurement;
try
{
unitOfMeasurement=unitOfMeasurementManager.getUnitOfMeasurementByCode(code);
cout<<"Unit of measurement towards code :"<<code<<" and Title: "<<unitOfMeasurement->getTitle()<<endl;
delete unitOfMeasurement;
}catch(BLException blException)
{
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}
}
return 0;
}
