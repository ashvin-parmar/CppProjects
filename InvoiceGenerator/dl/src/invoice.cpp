#include<iostream>
#include<dl/iinvoice>
#include<dl/invoice>
using namespace invoicegenerator;
using namespace data_layer;
using namespace std;
Invoice::Invoice()
{
this->code=0;
this->customerName="";
this->contactNumber="";
this->email="";
this->street="";
this->city="";
this->state="";
this->country="";
this->pinCode=0;
}
Invoice::Invoice(const Invoice &other)
{
this->code=other.code;
this->customerName=other.customerName;
this->contactNumber=other.contactNumber;
this->email=other.email;
this->street=other.street;
this->city=other.city;
this->state=other.state;
this->country=other.country;
this->pinCode=other.pinCode;
}
Invoice::~Invoice()
{
// For now do nothing
}
void Invoice::setCode(int code)
{
this->code=code;
}
void Invoice::setCustomerName(string customerName)
{
this->customerName=customerName;
}
void Invoice::setContactNumber(string contactNumber)
{
this->contactNumber=contactNumber;
}
void Invoice::setEmail(string email)
{
this->email=email;
}
void Invoice::setStreet(string street)
{
this->street=street;
}
void Invoice::setCity(string city)
{
this->city=city;
}
void Invoice::setState(string state)
{
this->state=state;
}
void Invoice::setCountry(string country)
{
this->country=country;
}
void Invoice::setPinCode(int pinCode)
{
this->pinCode=pinCode;
}
int Invoice::getCode() const
{
return this->code;
}
string Invoice::getcustomerName() const
{
return this->customerName;
}
string Invoice::getStreet() const
{
return this->street;
}
string Invoice::getCity() const
{
return this->city;
}
string Invoice::getState() const
{
return this->state;
}
string Invoice::getEmail() const
{
return this->email;
}
string Invoice::getContactNumber() const
{
return this->contactNumber;
}
string Invoice::getCountry() const
{
return this->country;
}
int Invoice::getPinCode() const
{
return this->pinCode;
}
abc::IInvoice & Invoice::operator=(const abc::IInvoice &other)
{
this->code=other.getCode();
this->customerName=other.getCustomerName();
this->contactNumber=other.getContactNumber();
this->email=other.getEmail();
this->street=other.getStreet();
this->city=other.getCity();
this->state=other.getState();
this->country=other.getCountry();
this->pinCode=other.getPinCode();
return *this;
}
int Invoice::operator==(const abc::IInvoice &other)
{
return this->code==other.getCode();
}
int Invoice::operator<=(const abc::IInvoice &other)
{
return this->code<=other.getCode();
}
int Invoice::operator>=(const abc::IInvoice &other)
{
return this->code>=other.getCode();
}
int Invoice::operator!=(const abc::IInvoice &other)
{
return this->code!=other.getCode();
}
int Invoice::operator<(const abc::IInvoice &other)
{
return this->code<other.getCode();
}
int Invoice::operator>(const abc::IInvoice &other)
{
return this->code>other.getCode();
}