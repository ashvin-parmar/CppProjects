#include<bl/uom>
#include<bl/uommanager>
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurementManager unitOfMeasurementManager;
cout<<"Number of Unit of Measurement: "<<unitOfMeasurementManager.getUnitOfMeasurementCount()<<endl;
return 0;
}