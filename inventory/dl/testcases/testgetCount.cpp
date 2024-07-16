#include<iostream>
#include<uomdao>
#include<uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"number of count of Unit of measurement available: "<<unitOfMeasurementDAO.getCount()<<endl;


return 0;
}