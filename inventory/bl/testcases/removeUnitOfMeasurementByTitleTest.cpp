#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
string title;
cout<<"Enter title to remove: ";
cin>>title;
cin.ignore(1000,'\n');
UnitOfMeasurementManager unitOfMeasurementManager;
try
{
unitOfMeasurementManager.removeUnitOfMeasurementByTitle(title);
cout<<"Unit of measurement towards title "<<title<<" removed"<<endl;
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
