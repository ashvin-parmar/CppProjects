#include<icompanyowner>
#include<companyowner>
using namespace invoicegenerator;
using namespace data_layer;

CompanyOwner::CompanyOwner()
{
this->name="";
this->email="";
this->contactNumber="";
this->street="";
this->state="";
this->code=0;
this->city="";
this->GSTNumber="";
this->pinCode=0;
this->password="";
}
CompanyOwner::CompanyOwner(const CompanyOwner &other)
{
this->name=other.name;
this->email=other.email;
this->contactNumber=other.contactNumber;
this->street=other.street;
this->state=other.state;
this->code=other.code;
this->city=other.city;
this->GSTNumber=other.GSTNumber;
this->pinCode=other.pinCode;
this->password=other.password;
}
CompanyOwner::CompanyOwner(string email,string password)
{
this->email=email;
this->password=password;
}
CompanyOwner::~CompanyOwner()
{
//Nothing to do
}
void CompanyOwner::setName(string Name)
{
this->name=name;
}
void CompanyOwner::setStreet(string street)
{
this->street=street;
}
void CompanyOwner::setCity(string city)
{
this->city=city;
}
void CompanyOwner::setState(string state)
{
this->state=state;
}
void CompanyOwner::setPinCode(int pinCode)
{
this->pinCode=pinCode;
}
void CompanyOwner::setContactNumber(string contactNumber)
{
int i;
for(i=0;contactNumber[i] && contactNumber[i]<=57 && contactNumber[i]>=48;i++);
if(contactNumber[i]=='\0') this->contactNumber=contactNumber;
else this->contactNumber=string("");
}
void CompanyOwner::setEmail(string email)
{
int found=false;
for(int i=0;i<email.size();i++)
{
if(email[i]=='@') 
{
found=true;
break;
}
}
if(found==false)
{
this->email="";
}
else
{
this->email=email;
}
}
void CompanyOwner::setGSTNumber(string gstNumber)
{
this->GSTNumber=gstNumber;
}
void CompanyOwner::setPassword(string password)
{
this->password=password;	//Increption applied after learning increption process
}
string CompanyOwner::getName() const
{
return this->name;
}
string CompanyOwner::getStreet() const
{
return this->street;
}
string CompanyOwner::getCity() const 
{
return this->city;
}
int CompanyOwner::getPinCode() const
{
return this->pinCode;
}
string CompanyOwner::getState() const
{
return this->state;
}
string CompanyOwner::getEmail() const
{
return this->email;
}
string CompanyOwner::getContactNumber() const
{
return this->contactNumber;
}
string CompanyOwner::getGSTNumber() const
{
return this->GSTNumber;
}
void CompanyOwner::setCode(int code)
{
this->code=code;
}
int CompanyOwner::getCode() const
{
return this->code;
}
string CompanyOwner::getPassword() const
{
return this->password;
}
abc::ICompanyOwner & CompanyOwner::operator=(const abc::ICompanyOwner &other)
{
this->name=other.getName();
this->email=other.getEmail();
this->contactNumber=other.getContactNumber();
this->street=other.getStreet();
this->state=other.getState();
this->code=other.getCode();
this->city=other.getCity();
this->GSTNumber=other.getGSTNumber();
this->pinCode=other.getPinCode();
this->password=other.getPassword();
return *this;
}
int CompanyOwner::operator==(const abc::ICompanyOwner &other)
{
return this->code==other.getCode();
}
int CompanyOwner::operator<=(const abc::ICompanyOwner &other)
{
return this->code<=other.getCode();
}
int CompanyOwner::operator>=(const abc::ICompanyOwner &other)
{
return this->code>=other.getCode();
}
int CompanyOwner::operator!=(const abc::ICompanyOwner &other)
{
return this->code!=other.getCode();
}
int CompanyOwner::operator<(const abc::ICompanyOwner &other)
{
return this->code<other.getCode();
}
int CompanyOwner::operator>(const abc::ICompanyOwner &other)
{
return this->code>other.getCode();
}