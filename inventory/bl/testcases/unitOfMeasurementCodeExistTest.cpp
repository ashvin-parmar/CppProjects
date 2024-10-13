#include<bl/uom>
#include<bl/uommanager>
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurementManager unitOfMeasurementManager;
int code;
cout<<"Enter code for Searching: ";
cin>>code;
cin.ignore(100,'\n');
if(unitOfMeasurementManager.unitOfMeasurementCodeExist(code)) cout<<code<<" Exist"<<endl;
else cout<<code<<" not exist"<<endl;
return 0;
}