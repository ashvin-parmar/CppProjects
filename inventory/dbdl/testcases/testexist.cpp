#include<iostream>
#include<dbdl/uomdao>
#include<dbdl/uom>
using namespace std;
using namespace inventory;
using namespace data_layer_db;
int main()
{
string title;
cout<<"Enter title for searching: ";
cin>>title;
UnitOfMeasurementDAO unitOfMeasurement;
try
{
if(unitOfMeasurement.titleExist(title)) cout<<"Title : "<<title<<" exist."<<endl;
else cout<<"Title : "<<title<<" not exist."<<endl;
}catch(DAOException &d)
{
cout<<d.what()<<endl;
}
int code;
cout<<"Enter code: ";
cin>>code;
try
{
if(unitOfMeasurement.codeExist(code)) cout<<"Code: "<<code<<" exist."<<endl;
else cout<<"Code : "<<code<<" not exist."<<endl;
}catch(DAOException &d)
{
cout<<d.what()<<endl;
}

return 0;
}