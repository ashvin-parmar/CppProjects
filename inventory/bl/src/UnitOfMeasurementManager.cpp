#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
#include<common/stringutils>
using namespace inventory;
using namespace business_layer;
void addUnitOfMeasurement(const abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0)
{
 BLException("Title should not been negative")
} 
}
void updateUnitOfMeasurement(const abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{

}
void removeUnitOfMeasurementByCode(int code) noexcept(false)
{

}
void removeUnitOfMeasurementByTitle(string &title) noexcept(false)
{

}
abc::IUnitOfMeasurement * getUnitOfMeasurementByCode(int code) noexcept(false)
{
return NULL;
}
abc::IUnitOfMeasurement * getUnitOfMeasurementByTitle(string &title) noexcept(false)
{
return NULL;
}
forward_list<abc::IUnitOfMeasurement *> * getUnitOfMeasurements() noexcept(false)
{
return NULL;
}
int unitOfMeasurementCodeExist(int code) noexcept(false)
{

return 0;
}
int unitOfMeasurementTitleExist(string &title) noexcept(false)
{
return 0;

}
int getUnitOfMeasurementCount() noexcept(false)
{
return 0;
}
