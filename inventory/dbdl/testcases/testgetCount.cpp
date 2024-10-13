#include<iostream>
#include<dbdl/uomdao>
#include<dbdl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer_db;
int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"number of count of Unit of measurement available: "<<unitOfMeasurementDAO.getCount()<<endl;


return 0;
}