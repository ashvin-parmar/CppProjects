#include<iostream>
#include<uomdao>
#include<uom>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
abc::IUnitOfMeasurement *unitOfMeasurement;
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"Enter Code: ";
cin>>code;
try
{
unitOfMeasurement=unitOfMeasurementDAO.getByCode(code);
cout<<"Title: "<<unitOfMeasurement->getTitle()<<", Code: "<<unitOfMeasurement->getCode()<<endl;
}catch(DAOException &b)
{
cout<<b.what()<<endl;
}
return 0;
}