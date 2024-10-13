#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/uommanager>
using namespace std;
using namespace inventory;
using namespace business_layer;
void add()
{
UnitOfMeasurement unitOfMeasurement;
UnitOfMeasurementManager unitOfMeasurementManager;
string title;
cout<<"Enter Title: ";
getline(cin,title);
unitOfMeasurement.setTitle(title);
unitOfMeasurementManager.addUnitOfMeasurement(&unitOfMeasurement);
cout<<title<<" Added"<<endl;
cout<<"Remeber this code: "<<unitOfMeasurement.getCode()<<" for future reference."<<endl;
}
void update()
{
UnitOfMeasurement unitOfMeasurement;
UnitOfMeasurementManager unitOfMeasurementManager;
int code;
cout<<"Enter code: ";
cin>>code;
cin.ignore(100,'\n');
string title;
cout<<"Enter Title: ";
getline(cin,title);
unitOfMeasurement.setTitle(title);
unitOfMeasurement.setCode(code);
unitOfMeasurementManager.updateUnitOfMeasurement(&unitOfMeasurement);
cout<<"Unit of measurement updated"<<endl;
}
void getByCode()
{
int code;
cout<<"Enter code to search: ";
cin>>code;
cin.ignore(1000,'\n');
UnitOfMeasurementManager unitOfMeasurementManager;
abc::IUnitOfMeasurement *unitOfMeasurement;
unitOfMeasurement=unitOfMeasurementManager.getUnitOfMeasurementByCode(code);
cout<<"Unit of measurement towards code :"<<code<<" and Title: "<<unitOfMeasurement->getTitle()<<endl;
delete unitOfMeasurement;
}
void getByTitle()
{
string title;
cout<<"Enter title to searching: ";
getline(cin,title);
UnitOfMeasurementManager unitOfMeasurementManager;
abc::IUnitOfMeasurement *unitOfMeasurement;
unitOfMeasurement=unitOfMeasurementManager.getUnitOfMeasurementByTitle(title);
cout<<"Unit of measurement towards title: "<<title<<" and code: "<<unitOfMeasurement->getCode()<<endl;
delete unitOfMeasurement;
}
void getAll()
{
abc::IUnitOfMeasurement *unitOfMeasurement;
UnitOfMeasurementManager unitOfMeasurementManager;
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
unitOfMeasurements=unitOfMeasurementManager.getUnitOfMeasurements();
cout<<"List of all Unit of Measurement: "<<endl;
int x;
for(x=1;x<89;x++) cout<<"-";
cout<<endl;
x=1;
char data[101];
for(i=unitOfMeasurements->begin();i!=unitOfMeasurements->end();++i,x++)
{
unitOfMeasurement=*i;
sprintf(data,"| %-5d | Code: %-10d | Title: %-50s |",x,unitOfMeasurement->getCode(),unitOfMeasurement->getTitle().c_str());
cout<<data<<endl;
delete unitOfMeasurement;
}
for(x=1;x<89;x++) cout<<"-";
cout<<endl;
unitOfMeasurements->clear();		//Written in documentation for releasing memeory
delete  unitOfMeasurements;
}
void getCount()
{
UnitOfMeasurementManager unitOfMeasurementManager;
cout<<"Number of Unit of Measurement: "<<unitOfMeasurementManager.getUnitOfMeasurementCount()<<endl;
}
void removeByCode()
{
int code;
cout<<"Enter code to remove: ";
cin>>code;
cin.ignore(1000,'\n');
UnitOfMeasurementManager unitOfMeasurementManager;
unitOfMeasurementManager.removeUnitOfMeasurementByCode(code);
cout<<"Unit of measurement towards code "<<code<<" removed"<<endl;
}
void removeByTitle()
{
string title;
cout<<"Enter title to remove: ";
getline(cin,title);
UnitOfMeasurementManager unitOfMeasurementManager;
unitOfMeasurementManager.removeUnitOfMeasurementByTitle(title);
cout<<"Unit of measurement towards title "<<title<<" removed"<<endl;
}
void isCodeExist()
{
UnitOfMeasurementManager unitOfMeasurementManager;
int code;
cout<<"Enter code for Searching: ";
cin>>code;
cin.ignore(100,'\n');
if(unitOfMeasurementManager.unitOfMeasurementCodeExist(code)) cout<<code<<" Exist"<<endl;
else cout<<code<<" not exist"<<endl;
}
void isTitleExist()
{
UnitOfMeasurementManager unitOfMeasurementManager;
string title;
cout<<"Enter title to searching: ";
getline(cin,title);
if(unitOfMeasurementManager.unitOfMeasurementTitleExist(title)) cout<<title<<" Exist"<<endl;
else cout<<title<<" not exist"<<endl;
}
int main()
{
int ch;
abc::IUnitOfMeasurement *unitOfMeasurement;
UnitOfMeasurementManager unitOfMeasurementManager;
while(true)
{
cout<<"----------Unit of Measurement Menu----------"<<endl;
cout<<"1. Add"<<endl;
cout<<"2. Update"<<endl;
cout<<"3. Remove by code"<<endl;
cout<<"4. Remove by title"<<endl;
cout<<"5. Get all records"<<endl;
cout<<"6. Get number of records"<<endl;
cout<<"7. Get by code"<<endl;
cout<<"8. Get by title"<<endl;
cout<<"9. Is code exist"<<endl;
cout<<"10. Is title exist"<<endl;
cout<<"11. Exit"<<endl;
cout<<"Enter your choice: ";
cin>>ch;
cin.ignore(1000,'\n');
try
{
switch(ch)
{
case 1: 
add();
break;
case 2:
update();
break;
case 3:
removeByCode();
break;
case 4:
removeByTitle();
break;
case 5:
getAll();
break;
case 6:
getCount();
break;
case 7:
getByCode();
break;
case 8:
getByTitle();
break;
case 9:
isCodeExist();
break;
case 10:
isTitleExist();
break;
case 11: break;
default: cout<<"Invalid choice"<<endl;
}
if(ch==11) break;
}catch(BLException blException)
{
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<blException.getPropertyException("title")<<endl;
}
}
cout<<"Press enter to continue....";
cin.ignore(100,'\n');
}
return 0;
}