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
if(company==NULL) throw DAOException("Required company data, NULL encountered");
if(company->getCode()!=0) throw DAOException("Required: Code should be zero");
const string vName=company->getName();
string name=trimmed(vName);
if(name.size()==0) throw DAOException("Name required, Name size zero");
if(name.size()>50) throw DAOException("Name should not exeed 50 character");
string contactNumber=validateContactNumber(company->getContactNumber());
if(contactNumber.size()==0) throw DAOException("Invalid contact number");
string email=validateEmail(company->getEmail());
if(email.size()==0 || email.size()>80) throw DAOException("Invalid email");
// done done: Later conveting password in hashing algoritm 
const string password=company->getPassword();
if(password.size()==0) throw DAOException("Please enter password, Empty password");
if(password.size()>100) throw DAOException("Password size can not exceed 100 characters");
string UPIID=validateUPIID(company->getUPIID());
if(UPIID.size()==0 || UPIID.size()>80) throw DAOException("Invalid UPI ID");
string GSTNumber=validateGSTNumber(company->getGSTNumber());
if(GSTNumber.size()==0 || GSTNumber.size()>15) throw DAOException("Invalid GST Number");
string street=company->getStreet();
if(street.size()==0) throw DAOException("Please enter street address");
if(street.size()>50) throw DAOException("Street address can not exceed 50 character");
string city=company->getCity();
if(city.size()==0) throw DAOException("Please enter city address");
if(city.size()>50) throw DAOException("City address can not exceed 50 character");
string state=company->getState();
if(state.size()==0) throw DAOException("Please enter state address");
if(state.size()>50) throw DAOException("State address can not exceed 50 character");
string country=company->getCountry();
if(country.size()==0) throw DAOException("Please enter country address");
if(country.size()>50) throw DAOException("Country address can not exceed 50 character");
int pinCode=company->getPinCode();
if(pinCode>999999 || pinCode<100000) throw DAOException("Please enter correct Pin Code");
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
void CompanyManager::updateCompany(abc::ICompany *company) noexcept(false)
{

if(company==NULL) throw DAOException("Required company data, NULL encountered");
if(company->getCode()!=0) throw DAOException("Required: Code already alloted, Code should be empty or zero");
const string vName=company->getName();
string name=trimmed(vName);
if(name.size()==0) throw DAOException("Name required, Name size zero");
if(name.size()>50) throw DAOException("Name should not exeed 50 character");
string contactNumber=validateContactNumber(company->getContactNumber());
if(contactNumber.size()==0) throw DAOException("Invalid contact number");
string email=validateEmail(company->getEmail());
if(email.size()==0 || email.size()>80) throw DAOException("Invalid email");
// done done: Later conveting password in hashing algoritm 
const string password=company->getPassword();
if(password.size()==0) throw DAOException("Please enter password, Empty password");
if(password.size()>100) throw DAOException("Password size can not exceed 100 characters");
string UPIID=validateUPIID(company->getUPIID());
if(UPIID.size()==0 || UPIID.size()>80) throw DAOException("Invalid UPI ID");
string GSTNumber=validateGSTNumber(company->getGSTNumber());
if(GSTNumber.size()==0 || GSTNumber.size()>15) throw DAOException("Invalid GST Number");
string street=company->getStreet();
if(street.size()==0) throw DAOException("Please enter street address");
if(street.size()>50) throw DAOException("Street address can not exceed 50 character");
string city=company->getCity();
if(city.size()==0) throw DAOException("Please enter city address");
if(city.size()>50) throw DAOException("City address can not exceed 50 character");
string state=company->getState();
if(state.size()==0) throw DAOException("Please enter state address");
if(state.size()>50) throw DAOException("State address can not exceed 50 character");
string country=company->getCountry();
if(country.size()==0) throw DAOException("Please enter country address");
if(country.size()>50) throw DAOException("Country address can not exceed 50 character");
int pinCode=company->getPinCode();
if(pinCode>999999 || pinCode<100000) throw DAOException("Please enter correct Pin Code");




}
void CompanyManager::updateCompanyAddress(abc::ICompany *company) noexcept(false)
{


}
void CompanyManager::removeCompany(string &email) noexcept(false)
{
}
forward_list<abc::ICompany *> * CompanyManager::getAllCompany() noexcept(false)
{
Header header;
ifstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) throw DAOException("Company does not exist");
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("Company does not exist");
}
if(header.numberOfRecords==0) 
{
dataFile.close();
throw DAOException("Company does not exist");
}
_Company _company;
abc::ICompany *company;
forward_list<abc::ICompany *> *companyList;
companyList=new forward_list<abc::ICompany *>;
forward_list<abc::ICompany *>::iterator listi=companyList->before_begin();
while(true)
{
dataFile.read((char *)&_company,sizeof(_Company));
if(dataFile.fail()) break;
company=new Company;
company->setName(string(_company.name));
company->setEmail(string(_company.email));
company->setContactNumber(string(_company.contactNumber));
company->setStreet(string(_company.street));
company->setCity(string(_company.city));
company->setCountry(string(_company.country));
company->setState(string(_company.state));
company->setGSTNumber(string(_company.GSTNumber));
company->setUPIID(string(_company.UPIID));
company->setPinCode(_company.pinCode);
company->setCode(_company.code);
listi=companyList->insert_after(listi,company);
}
dataFile.close();
return companyList;
}
abc::ICompany * CompanyManager::getCompany(string &vEmail) noexcept(false)
{
string email=validateEmail(vEmail);
if(email.size()==0) throw DAOException("Invalid Email");
if(email.size()>80) throw DAOException("Email can not exceed 80 characters");
ifstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) throw DAOException("Invalid company email");
Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("Invalid company email");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Invalid company email");
}
_Company _company;
abc::ICompany *company;
while(1)
{
dataFile.read((char *)&_company,sizeof(_Company));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_company.email,email.c_str())==0)
{
company=new Company;
company->setName(string(_company.name));
company->setEmail(string(_company.email));
company->setContactNumber(string(_company.contactNumber));
company->setStreet(string(_company.street));
company->setCity(string(_company.city));
company->setCountry(string(_company.country));
company->setState(string(_company.state));
company->setGSTNumber(string(_company.GSTNumber));
company->setUPIID(string(_company.UPIID));
company->setPinCode(_company.pinCode);
company->setCode(_company.code);
dataFile.close();
return company;
}
}
dataFile.close();
throw DAOException("Invalid email");
}
void CompanyManager::resetPassword(string email,string previousPassword,string newPassword) noexcept(false)
{

}
int CompanyManager::isCompanyExist(const string &vEmail) noexcept(false)
{
string email=validateEmail(vEmail);
if(email.size()==0) return 0;
if(email.size()>80) return 0;
ifstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) return 0;
Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
return 0;
}
if(header.numberOfRecords==0)
{
dataFile.close();
return 0;
}
_Company _company;
abc::ICompany *company;
while(1)
{
dataFile.read((char *)&_company,sizeof(_Company));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_company.email,email.c_str())==0)
{
dataFile.close();
return 1;
}
}
dataFile.close();
return 0;
}
void getLine(int size,char m);
void CompanyManager::showProfile(const string &vEmail) noexcept(false)
{
void getLine(int size,char m)
{
for(int i=0;i<size;i++) cout<<m;
cout<<endl;
}
CompanyManager companyManager;
abc::ICompany *company;
string email=vEmail;
try
{
company=companyManager.getCompany(email);
}catch(DAOException daoException)
{
throw DAOException(daoException.what());
}
getLine(120,'_');
cout<<"----------Company Login Details----------"<<endl;
printf("Company Name: %-80s    Company Code: %-15d\n",company->getName().c_str(),company->getCode());
printf("Email: %-80s           Contact Number: %-15s\n\n",company->getEmail().c_str(),company->getContactNumber().c_str());

cout<<"----------Company Address----------"<<endl;
printf("Street:  %-50s    City   : %-50s\n",company->getStreet().c_str(),company->getCity().c_str());
printf("State :  %-50s    Country: %-50s\n",company->getState().c_str(),company->getCountry().c_str());
printf("Pin Code: %-15d\n\n",company->getPinCode());

cout<<"----------Bank Detail----------"<<endl;
printf("GST Number: %-50s UPIID: %-50s\n",company->getGSTNumber().c_str(),company->getUPIID().c_str());
getLine(120,'_');
cout<<endl;
delete company;
}
