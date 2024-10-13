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
int code;
cout<<"Enter code: ";
cin>>code;
cin.ignore(100,'\n');
string title;
cout<<"Enter Title: ";
getline(cin,title);
unitOfMeasurement.setTitle(title);
unitOfMeasurement.setCode(code);
try
{
unitOfMeasurementManager.updateUnitOfMeasurement(&unitOfMeasurement);
cout<<"Unit of measurement updated"<<endl;
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
if(blException.hasPropertyException("title"))
{
cout<<blException.getPropertyException("title")<<endl;
}
}
return 0;
}