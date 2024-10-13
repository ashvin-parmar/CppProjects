#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"number of count of Unit of measurement available: "<<unitOfMeasurementDAO.getCount()<<endl;


return 0;
}