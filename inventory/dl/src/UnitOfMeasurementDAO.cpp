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
return NULL;
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() noexcept(false)
{
return NULL;
}
int UnitOfMeasurementDAO::getCount() noexcept(false)
{
return 0;
}
int UnitOfMeasurementDAO::titleExist(string title) noexcept(false)
{
return 0;

}
int UnitOfMeasurementDAO::codeExist(int code) noexcept(false)
{
return 0;
}
