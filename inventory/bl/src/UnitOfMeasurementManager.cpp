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

}
void UnitOfMeasurementManager::DataModel::populateDataStructure()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *list;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
inventory::data_layer::abc::IUnitOfMeasurement *unitOfMeasurementBL;
abc::IUnitOfMeasurement *unitOfMeasurement;
list=unitOfMeasurementDAO.getAll();
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
for(i=list->begin();i!=list->end();++i)
{
unitOfMeasurementBL=*i;
string title=unitOfMeasurementBL->getTitle();
int code=unitOfMeasurementBL->getCode();
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(code);
unitOfMeasurement->setTitle(title);
dataModel.titleWiseMap.insert(pair<string *,abc::IUnitOfMeasurement *>(&title,unitOfMeasurement));
dataModel.codeWiseMap.insert(pair<int,abc::IUnitOfMeasurement *>(code,unitOfMeasurement));
delete unitOfMeasurementBL;
}
}
UnitOfMeasurementManager::UnitOfMeasurementManager()
{

}
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement)
{
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0) throw BLException("Title required, length of title is zero");
if(title.length()>50) throw BLException("Title cannot exceed 50 characters");
map<string *,abc::IUnitOfMeasurement *,UnitOfMeasurementManagerTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end()) throw BLException(title+string(" exist"));
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
inventory::data_layer::UnitOfMeasurement *unitOfMeasurementDL;
try
{
unitOfMeasurementDL->setTitle(title);
unitOfMeasurementDAO.add(unitOfMeasurementDL);
}catch(inventory::data_layer::DAOException daoException)
{
throw BLException(string(daoException.what()));
}
int code;
code=unitOfMeasurementDL->getCode();
UnitOfMeasurement _unitOfMeasurement;
_unitOfMeasurement.setTitle(title);
_unitOfMeasurement.setCode(code);
dataModel.titleWiseMap.insert(pair<string *,abc::IUnitOfMeasurement *>(&title,&_unitOfMeasurement));
dataModel.codeWiseMap.insert(pair<int,abc::IUnitOfMeasurement *>(code,&_unitOfMeasurement));
unitOfMeasurement->setCode(code);
}
void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{

}
void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) noexcept(false)
{

}
void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) noexcept(false)
{

}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) noexcept(false)
{
return NULL;
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) noexcept(false)
{
return NULL;
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementManager::getUnitOfMeasurements() noexcept(false)
{
return NULL;
}
int UnitOfMeasurementManager::unitOfMeasurementCodeExist(int code) noexcept(false)
{

return 0;
}
int UnitOfMeasurementManager::unitOfMeasurementTitleExist(string &title) noexcept(false)
{
return 0;

}
int UnitOfMeasurementManager::getUnitOfMeasurementCount() noexcept(false)
{
return 0;
}
