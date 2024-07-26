#include<bl/uom>
#include<bl/uommanager>
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurementManager unitOfMeasurementManager;
string title;
cout<<"Enter Title Searching: ";
getline(cin,title);
if(unitOfMeasurementManager.unitOfMeasurementTitleExist(title)) cout<<title<<" Exist"<<endl;
else cout<<title<<" not exist"<<endl;
return 0;
}