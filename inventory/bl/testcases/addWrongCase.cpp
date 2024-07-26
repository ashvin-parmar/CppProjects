//WRONG TEST_CASE : Because there are pointer which is passed in addUnitOfMeasurement which breaks terminate code withour any exception throwing, because aT that place address of unitOfMeasurement taking behind the scene, there are pointer sends
//Use Correct testcase: (addUnitOfMeasurement.cpp)


#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
string title;
cout<<"Enter Unit Of Measurement Title: ";
getline(cin,title);
cout<<"Hii"<<endl;
try
{
cout<<"Hii"<<endl;
UnitOfMeasurement *unitOfMeasurement;
UnitOfMeasurementManager unitOfMeasurementManager;
cout<<title<<endl;
unitOfMeasurement->setTitle(title);
cout<<"b"<<endl;
//cout<<unitOfMeasurement->getTitle()<<endl;
cout<<title<<endl;
unitOfMeasurementManager.addUnitOfMeasurement(unitOfMeasurement);
cout<<"Title added"<<endl;
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
