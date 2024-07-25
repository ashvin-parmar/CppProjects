#include<dl/icompany>
#include<dl/company>
#include<dl/icompanymanager>
#include<dl/companymanager>
#include<dl/daoexception>
#include<fstream>
#include<string.h>
#include<common/stringutils>
using namespace stringutils;
using namespace invoicegenerator;
using namespace data_layer;
void CompanyManager::addCompany(abc::ICompany *company) noexcept(false)
{
if(company==NULL) throw DAOException("NULL value return.");
if(company->getCode()!=0) throw DAOException("Required: Code should be zero");
const string vName=company->getName();
string name=trimmed(vName);
if(name.size()==0) throw DAOException("Name required, Name size zero");
if(name.size()>50) throw DAOException("Name should not exeed 50 character");
string contactNumber=validateContactNumber(company->getContactNumber());
if(contactNumber.size()==0) throw DAOException("Invalid contact number");
string email=validateEmail(company->getEmail());
if(email.size()==0 || email.size()>100) throw DAOException("Invalid email");
string UPIID=validateUPIID(company->getUPIID());
if(UPIID.size()==0) throw DAOException("Invalid UPI ID");
string GSTNumber=validateGSTNumber(company->getGSTNumber());
if(GSTNumber.size()==0 || GSTNumber.size()>15) throw DAOException("Invalid GST Number");
string street=company->getStreet();
if(street.size()==0) throw DAOException("Please enter street address");
string city=company->getCity();
if(city.size()==0) throw DAOException("Please enter city address");
string state=company->getState();
if(state.size()==0) throw DAOException("Please enter state address");
string country=company->getCountry();
if(country.size()==0) throw DAOException("Please enter country address");
int pinCode=company->getPinCode();
if(pinCode>999999 || pinCode<100000) throw DAOException("Please enter correct Pin Code");
// done done: Later conveting password in hashing algoritm 
const string password=company->getPassword();
if(password.size()==0) throw DAOException("Please enter password, Empty password.");
//Other All Type Of Validation
Header header;
_Company _company;
fstream dataFile(FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
ofstream dFile(FILE_NAME,ios::app | ios::binary);
header.numberOfRecords=1;
header.lastGeneratedCode=1;
strcpy(_company.name,name.c_str());
strcpy(_company.email,email.c_str());
strcpy(_company.contactNumber,contactNumber.c_str());
strcpy(_company.street,street.c_str());
strcpy(_company.city,city.c_str());
strcpy(_company.state,state.c_str());
strcpy(_company.country,country.c_str());
strcpy(_company.GSTNumber,GSTNumber.c_str());
strcpy(_company.UPIID,UPIID.c_str());
strcpy(_company.password,password.c_str());
_company.pinCode=pinCode;
_company.code=1;
dFile.write((char *)&header,sizeof(Header));
dFile.write((char *)&_company,sizeof(_Company));
dFile.close();
company->setCode(header.lastGeneratedCode);
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.seekp(0,ios::beg);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
strcpy(_company.name,name.c_str());
strcpy(_company.email,email.c_str());
strcpy(_company.contactNumber,contactNumber.c_str());
strcpy(_company.street,street.c_str());
strcpy(_company.city,city.c_str());
strcpy(_company.state,state.c_str());
strcpy(_company.country,country.c_str());
strcpy(_company.GSTNumber,GSTNumber.c_str());
strcpy(_company.UPIID,UPIID.c_str());
strcpy(_company.password,password.c_str());
_company.pinCode=pinCode;
_company.code=1;
dataFile.write((char *)&header,sizeof(Header));
dataFile.write((char *)&_company,sizeof(_Company));
dataFile.close();
company->setCode(header.lastGeneratedCode);
return;
}
while(true)
{
dataFile.read((char *)&_company,sizeof(_Company));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_company.email,email.c_str())==0)
{
dataFile.close();
throw DAOException(string("Company already exist with email "+email));
}
}
dataFile.clear();
header.lastGeneratedCode++;
header.numberOfRecords++;
strcpy(_company.name,name.c_str());
strcpy(_company.email,email.c_str());
strcpy(_company.contactNumber,contactNumber.c_str());
strcpy(_company.street,street.c_str());
strcpy(_company.city,city.c_str());
strcpy(_company.state,state.c_str());
strcpy(_company.country,country.c_str());
strcpy(_company.GSTNumber,GSTNumber.c_str());
strcpy(_company.UPIID,UPIID.c_str());
strcpy(_company.password,password.c_str());
_company.pinCode=pinCode;
_company.code=header.lastGeneratedCode;
dataFile.seekp(0,ios::end);
dataFile.write((char *)&_company,sizeof(_Company));
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close();
company->setCode(header.lastGeneratedCode);
}
