#include<iuom>
#include<uom>
#include<iuomdao>
#include<uomdao>
#include<daoexception>
#include<stringutils>
#include<string.h>
#include<fstream>
using namespace inventory;
using namespace data_layer;
using namespace stringutils;
void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{
//if(unitOfMeasurement==NULL) throw DAOException("Empty data provided, please specify something");
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0) throw DAOException("Title required, Length of title is zero");
if(title.length()>50) throw DAOException("Title cannot exceed 50 characters");
Header header;
_UnitOfMeasurement _unitOfMeasurement;
fstream dataFile(FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail()) 
{
ofstream dFile(FILE_NAME,ios::app | ios::binary);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
dFile.write((char *)&header,sizeof(Header));
_unitOfMeasurement.code=1;
strcpy(_unitOfMeasurement.title,title.c_str());
dFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dFile.close();
unitOfMeasurement->setCode(1);
return;
}
dataFile.seekp(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.clear();
dataFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
dataFile.write((char *)&header,sizeof(Header));
_unitOfMeasurement.code=1;
strcpy(_unitOfMeasurement.title,title.c_str());
dataFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dataFile.close();
unitOfMeasurement->setCode(1);
return;
}
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0)
{
dataFile.close();
throw DAOException(title+string(" Exist"));
}
}
dataFile.clear();
header.lastGeneratedCode++;
header.numberOfRecords++;
_unitOfMeasurement.code=header.lastGeneratedCode;
strcpy(_unitOfMeasurement.title,title.c_str());
dataFile.seekp(0,ios::end);
dataFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close();
unitOfMeasurement->setCode(header.lastGeneratedCode);
}
void UnitOfMeasurementDAO::update(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{



}
void UnitOfMeasurementDAO::remove(int code) noexcept(false)
{

}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string title) noexcept(false)
{
return NULL;
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByCode(int code) noexcept(false)
{
if(code<=0) throw DAOException("Invalid code.");
Header header;
char arr[100];
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) 
{
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
dataFile.seekp(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
if(header.numberOfRecords==0 || code>header.lastGeneratedCode)
{
dataFile.close();
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
_UnitOfMeasurement _unitOfMeasurement;
abc::IUnitOfMeasurement *unitOfMeasurement;
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code)
{
dataFile.close();
unitOfMeasurement=new abc::IUnitOfMeasurement;
unitOfMeasurement->setCode(_unitOfMeasurement.code);
unitOfMeasurement->setTitle(string(_unitOfMeasurement.title));
return unitOfMeasurement;
}
}
dataFile.close();
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() noexcept(false)
{
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) 
{
throw DAOException("Unit of measurement does not exist");
}
dataFile.seekp(0,ios::beg);
Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Unit of measurement does not exist");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Unit of measurement does not exist");
}
_UnitOfMeasurement _unitOfMeasurement;
abc::IUnitOfMeasurement *unitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *> *list;
list=new forward_list<abc::IUnitOfMeasurement*>;
forward_list<abc::IUnitOfMeasurement *>::iterator i=list->before_begin();
while(true) 
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(_unitOfMeasurement.code);
unitOfMeasurement->setTitle(string(_unitOfMeasurement.title));
i=list->insert_after(i,unitOfMeasurement);
}
return list;
}
int UnitOfMeasurementDAO::getCount() noexcept(false)
{
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) 
{
return 0;
}
dataFile.seekp(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
dataFile.close();
return header.numberOfRecords;
}
}
int UnitOfMeasurementDAO::titleExist(string vTitle) noexcept(false)
{
string title=trimmed(vTitle);

//if(title.length()==0) throw DAOException("Title required, Length of title is zero");
//if(title.length()>50) throw DAOException("Title cannot exceed 50 characters");
Header header;
_UnitOfMeasurement _unitOfMeasurement;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) 
{
return false;
}
dataFile.seekp(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return false;
}
if(header.numberOfRecords==0)
{
dataFile.close();
return false;
}
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0)
{
dataFile.close();
return true;
}
}
dataFile.close();
return false;
}
int UnitOfMeasurementDAO::codeExist(int code) noexcept(false)
{
if(code<=0)
{
throw DAOException("Invalid code.");
}
Header header;
_UnitOfMeasurement _unitOfMeasurement;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) 
{
return false;
}
dataFile.seekp(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return false;
}
if(header.numberOfRecords==0 || code>header.lastGeneratedCode)
{
dataFile.close();
return false;
}
while(true)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code)
{
dataFile.close();
return true;
}
}
dataFile.close();
return false;
}