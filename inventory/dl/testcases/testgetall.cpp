#include<iostream>
#include<dl/uomdao>
#include<dl/uom>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurement;
abc::IUnitOfMeasurement *data;
forward_list<abc::IUnitOfMeasurement *> *list;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
try
{
list=unitOfMeasurement.getAll();
for(i=list->begin();i!=list->end();i++)
{
data=*i;
cout<<"Code: "<<data->getCode()<<", Title: "<<data->getTitle()<<endl;
}
}catch(DAOException &d)
{
cout<<d.what()<<endl;
}
return 0;
}