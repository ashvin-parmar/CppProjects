#include<iostream>
#include<uomdao>
#include<uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
string title;
abc::IUnitOfMeasurement *unitOfMeasurement;
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"Enter title: ";
cin>>title;
try
{
unitOfMeasurement=unitOfMeasurementDAO.getByTitle(title);
cout<<"Title: "<<unitOfMeasurement->getTitle()<<", Code: "<<unitOfMeasurement->getCode()<<endl;
}catch(DAOException &b)
{
cout<<b.what()<<endl;
}
return 0;
}