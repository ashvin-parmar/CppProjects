#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurement unitOfMeasurement;
UnitOfMeasurementManager unitOfMeasurementManager;
string title;
cout<<"Enter Title: ";
getline(cin,title);
unitOfMeasurement.setTitle(title);
try
{
unitOfMeasurementManager.addUnitOfMeasurement(&unitOfMeasurement);
cout<<title<<" Added"<<endl;
cout<<"Remeber this code: "<<unitOfMeasurement.getCode()<<" for future reference."<<endl;
}catch(BLException blException)
{
cout<<"Some problem"<<endl;
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<blException.getPropertyException("title")<<endl;
}
}
return 0;
}