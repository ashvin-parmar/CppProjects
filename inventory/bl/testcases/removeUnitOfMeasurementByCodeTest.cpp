#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
int code;
cout<<"Enter code to remove: ";
cin>>code;
cin.ignore(1000,'\n');
UnitOfMeasurementManager unitOfMeasurementManager;
try
{
unitOfMeasurementManager.removeUnitOfMeasurementByCode(code);
cout<<"Unit of measurement towards code "<<code<<" removed"<<endl;
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
