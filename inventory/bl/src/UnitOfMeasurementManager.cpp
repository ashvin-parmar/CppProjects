#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<bl/blexception>
#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<dl/daoexception>
#include<common/stringutils>
#include<map>
#include<utility>
#include<forward_list>
using namespace inventory;
using namespace business_layer;
using namespace stringutils;

bool UnitOfMeasurementManagerTitleComparator::operator()(const string *left,const string *right)
{
return compareStringIgnoreCase(left->c_str(),right->c_str())<0;
}
UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel;
UnitOfMeasurementManager::DataModel::DataModel()
{
UnitOfMeasurementManager::DataModel::populateDataStructure();
}
UnitOfMeasurementManager::DataModel::~DataModel()
{
_UnitOfMeasurement *unitOfMeasurement;
map<string *,_UnitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.begin();
while(i!=dataModel.titleWiseMap.end())
{
unitOfMeasurement=i->second;
delete unitOfMeasurement->title;
delete unitOfMeasurement;
++i;
}
dataModel.titleWiseMap.clear();
dataModel.codeWiseMap.clear();
}
void UnitOfMeasurementManager::DataModel::populateDataStructure()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *list;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
inventory::data_layer::abc::IUnitOfMeasurement *unitOfMeasurementDL;
_UnitOfMeasurement *unitOfMeasurementBL;
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
string *title;
int code;
try
{
list=unitOfMeasurementDAO.getAll();
for(i=list->begin();i!=list->end();++i)
{
unitOfMeasurementDL=*i;
title=new string(unitOfMeasurementDL->getTitle());
code=unitOfMeasurementDL->getCode();
unitOfMeasurementBL=new _UnitOfMeasurement;
unitOfMeasurementBL->code=code;
unitOfMeasurementBL->title=title;
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(unitOfMeasurementBL->title,unitOfMeasurementBL));
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code,unitOfMeasurementBL));
delete unitOfMeasurementDL;
}
list->clear();
delete list;
}catch(inventory::data_layer::DAOException daoException)
{
// do nothing
}
}
UnitOfMeasurementManager::UnitOfMeasurementManager()
{

}
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{
BLException blException;
if(unitOfMeasurement==NULL)
{
blException.setGenericException("Unit of measurement required, Null encountered");
throw blException;
}
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0) blException.addPropertyException("title","Title required, length of title is zero");
if(title.length()>50) blException.addPropertyException("title","Title should not exceed 50 characters");
int code=unitOfMeasurement->getCode();
if(code!=0) blException.addPropertyException("code","Code should be zero");
if(blException.hasException())
{
throw blException;
}
map<string *,_UnitOfMeasurement *,UnitOfMeasurementManagerTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Given title exist");
throw blException;
}
_UnitOfMeasurement *_unitOfMeasurement;
string *t;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *unitOfMeasurementDL;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
unitOfMeasurementDL=new inventory::data_layer::UnitOfMeasurement;
unitOfMeasurementDL->setCode(0);
unitOfMeasurementDL->setTitle(title);
unitOfMeasurementDAO.add(unitOfMeasurementDL);
code=unitOfMeasurementDL->getCode();
t=new string(title);
delete unitOfMeasurementDL;
_unitOfMeasurement=new _UnitOfMeasurement;
_unitOfMeasurement->code=code;
_unitOfMeasurement->title=t;
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(t,_unitOfMeasurement));
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code,_unitOfMeasurement));
unitOfMeasurement->setCode(code);
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{
BLException blException;
if(unitOfMeasurement==NULL)
{
blException.setGenericException("Unit of measurement required, Null encountered");
throw blException;
}
int code=unitOfMeasurement->getCode();
char arr[51];
sprintf(arr,"%d",code);
if(code<=0) blException.addPropertyException("code",string("Invalid code: ")+string(arr));
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0) blException.addPropertyException("title","Title required, length of title is zero");
if(title.length()>50) blException.addPropertyException("title","Title should not exceed 50 characters");
if(blException.hasException())
{
throw blException;
}
map<int,_UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.addPropertyException("code",string("Given code ")+string(arr)+string(" does not exist"));
throw blException;
}
map<string *,_UnitOfMeasurement *,UnitOfMeasurementManagerTitleComparator>::iterator j;
j=dataModel.titleWiseMap.find(&title);
if(j!=dataModel.titleWiseMap.end() && j->second->code!=code)
{
blException.addPropertyException("title",string("Given titel ")+title+string(" already exist towards another code"));
throw blException;
}
_UnitOfMeasurement *blUnitOfMeasurement;
string *t;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *unitOfMeasurementDL;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
unitOfMeasurementDL=new inventory::data_layer::UnitOfMeasurement;
unitOfMeasurementDL->setCode(code);
unitOfMeasurementDL->setTitle(title);
unitOfMeasurementDAO.update(unitOfMeasurementDL);
blUnitOfMeasurement=i->second;
t=blUnitOfMeasurement->title;
//Memory releasing
dataModel.codeWiseMap.erase(code);
dataModel.titleWiseMap.erase(t);	//TitleWiseMapUpdate
delete unitOfMeasurementDL;
delete t;
delete blUnitOfMeasurement;
//Data erased from maps

t=new string(title);
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=t;	// codeWiseMap Update
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(t,blUnitOfMeasurement));
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code,blUnitOfMeasurement));
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) noexcept(false)
{
BLException blException;
char arr[51];
sprintf(arr,"%d",code);
if(code<=0) blException.addPropertyException("code",string("Invalid code: ")+string(arr));
if(blException.hasException()) throw blException;
map<int,_UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.addPropertyException("code",string("Given code ")+string(arr)+string(" does not exist"));
throw blException;
}
_UnitOfMeasurement *blUnitOfMeasurement;
string *t;
try
{
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
unitOfMeasurementDAO.remove(code);
//Memory releasing
blUnitOfMeasurement=i->second;
t=blUnitOfMeasurement->title;
dataModel.codeWiseMap.erase(code);
dataModel.titleWiseMap.erase(t);	//TitleWiseMapUpdate
delete t;
delete blUnitOfMeasurement;
//Data erased from maps
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &vTitle) noexcept(false)
{
BLException blException;
string title=trimmed(vTitle);
if(title.length()==0) blException.addPropertyException("title","Title required, length of title is zero");
if(title.length()>50) blException.addPropertyException("title","Title should not exceed 50 characters");
if(blException.hasException())
{
throw blException;
}
map<string *,_UnitOfMeasurement *,UnitOfMeasurementManagerTitleComparator>::iterator j;
j=dataModel.titleWiseMap.find(&title);
if(j==dataModel.titleWiseMap.end())
{
blException.addPropertyException("title",string("Given titel ")+title+string(" does not exist"));
throw blException;
}
_UnitOfMeasurement *blUnitOfMeasurement;
string *t;
int code;
try
{
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
blUnitOfMeasurement=j->second;
code=blUnitOfMeasurement->code;
t=blUnitOfMeasurement->title;
unitOfMeasurementDAO.remove(code);
//Memory releasing
dataModel.codeWiseMap.erase(code);
dataModel.titleWiseMap.erase(t);	//TitleWiseMapUpdate
delete t;
delete blUnitOfMeasurement;
//Data erased from maps
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) noexcept(false)
{
BLException blException;
char arr[51];
sprintf(arr,"%d",code);
if(code<=0) blException.addPropertyException("code",string("Invalid code: ")+string(arr));
if(blException.hasException()) throw blException;
map<int,_UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.addPropertyException("code",string("Given code ")+string(arr)+string(" does not exist"));
throw blException;
}
_UnitOfMeasurement *blUnitOfMeasurement;
abc::IUnitOfMeasurement *unitOfMeasurement;
blUnitOfMeasurement=i->second;
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(blUnitOfMeasurement->code);
unitOfMeasurement->setTitle(string(*(blUnitOfMeasurement->title)));
return unitOfMeasurement;
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &vTitle) noexcept(false)
{
BLException blException;
string title=trimmed(vTitle);
if(title.length()==0) blException.addPropertyException("title","Title required, length of title is zero");
if(title.length()>50) blException.addPropertyException("title","Title should not exceed 50 characters");
if(blException.hasException())
{
throw blException;
}
map<string *,_UnitOfMeasurement *,UnitOfMeasurementManagerTitleComparator>::iterator j;
j=dataModel.titleWiseMap.find(&title);
if(j==dataModel.titleWiseMap.end())
{
blException.addPropertyException("title",string("Given titel ")+title+string(" does not exist"));
throw blException;
}
_UnitOfMeasurement *blUnitOfMeasurement;
abc::IUnitOfMeasurement *unitOfMeasurement;
blUnitOfMeasurement=j->second;
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(blUnitOfMeasurement->code);
unitOfMeasurement->setTitle(string(*(blUnitOfMeasurement->title)));
return unitOfMeasurement;
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementManager::getUnitOfMeasurements() noexcept(false)
{
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
unitOfMeasurements=new forward_list<abc::IUnitOfMeasurement *>;
forward_list<abc::IUnitOfMeasurement *>::iterator listi;
listi=unitOfMeasurements->before_begin();

abc::IUnitOfMeasurement *unitOfMeasurement;
_UnitOfMeasurement *blUnitOfMeasurement;
map<string *,_UnitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.begin();
while(i!=dataModel.titleWiseMap.end())
{
blUnitOfMeasurement=i->second;
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(blUnitOfMeasurement->code);
unitOfMeasurement->setTitle(string(*(blUnitOfMeasurement->title)));
listi=unitOfMeasurements->insert_after(listi,unitOfMeasurement);
++i;
}
return unitOfMeasurements;
}
int UnitOfMeasurementManager::unitOfMeasurementCodeExist(int code) noexcept(false)
{
map<int,_UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i!=dataModel.codeWiseMap.end()) return true;
return false;
}
int UnitOfMeasurementManager::unitOfMeasurementTitleExist(string &title) noexcept(false)
{
map<string*,_UnitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end()) return true;
return false;
}
int UnitOfMeasurementManager::getUnitOfMeasurementCount() noexcept(false)
{
return dataModel.titleWiseMap.size();
}
