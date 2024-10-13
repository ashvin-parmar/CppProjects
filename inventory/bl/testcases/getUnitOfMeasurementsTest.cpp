#include<iostream>
#include<forward_list>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/iuom>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
abc::IUnitOfMeasurement *unitOfMeasurement;
UnitOfMeasurementManager unitOfMeasurementManager;
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
unitOfMeasurements=unitOfMeasurementManager.getUnitOfMeasurements();
for(i=unitOfMeasurements->begin();i!=unitOfMeasurements->end();++i)
{
unitOfMeasurement=*i;
cout<<"Code: "<<unitOfMeasurement->getCode()<<" , Title: "<<unitOfMeasurement->getTitle()<<endl;
delete unitOfMeasurement;
}
unitOfMeasurements->clear();		//Written in documentation for releasing memeory
delete  unitOfMeasurements;
return 0;
}