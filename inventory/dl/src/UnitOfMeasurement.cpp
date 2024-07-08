
#include<iuom>
#include<uom>
using namespace inventory;
using namespace data_layer;
UnitOfMeasurement::UnitOfMeasurement()
{
this->code=0;
this->tital="";
}
UnitOfMeasurement::UnitOfMeasurement(const UnitOfMeasurement &other)
{
this->code=other.code;
this->tital=other.tital;
}
UnitOfMeasurement::UnitOfMeasurement(int code,string tital)
{
this->code=code;
this->tital=tital;
}
void UnitOfMeasurement::setCode(int code)
{
this->code=code;
}
void UnitOfMeasurement::setTital(string tital)
{
this->tital=tital;
}
string UnitOfMeasurement::getTital() const
{
return this->tital;
}
int UnitOfMeasurement::getcode() const
{
return this->code;
}
abc::IUnitOfMeasurement& UnitOfMeasurement::operator=(const abc::IUnitOfMeasurement &other)
{
this->code=other.getCode();
this->tital=other.getTital();
return *this;
}
int UnitOfMeasurement::operator<(const IUnitOfMeasurement &other)
{
return this->code<other.getCode();
}
int UnitOfMeasurement::operator>(const IUnitOfMeasurement &other)
{
return this->code>other.getCode();
}
int UnitOfMeasurement::operator<=(const IUnitOfMeasurement &other)
{
return this->code<=other.getCode();
}
int UnitOfMeasurement::operator>=(const IUnitOfMeasurement &other)
{
return this->code>=other.getCode();
}
int UnitOfMeasurement::operator==(const IUnitOfMeasurement &other)
{
return this->code==other.getCode();
}
int UnitOfMeasurement::operator!=(const IUnitOfMeasurement &other)
{
return this->code!=other.getCode();
}
UnitOfMeasurement::~UnitOfMeasurement()
{
//Do nothing
}