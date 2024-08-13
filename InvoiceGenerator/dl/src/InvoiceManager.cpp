#include<dl/icustomer>
#include<dl/customer>
#include<dl/icustomermanager>
#include<dl/customermanager>
#include<dl/daoexception>
#include<dl/icompany>
#include<dl/company>
#include<dl/icompanymanager>
#include<dl/companymanager>
#include<dl/invoice>
#include<dl/iinvoice>
#include<dl/iinvoicemanager>
#include<dl/invoicemanager>
#include<fstream>
#include<string.h>
#include<forward_list>
#include<common/stringutils>
using namespace stringutils;
using namespace invoicegenerator;
using namespace data_layer;
void InvoiceManager::addInvoice(abc::IInvoice *invoice) noexcept(false)
{
if(invoice==NULL) throw DAOException("Required invoice data, NULL encountered");
if(invoice->getInvoiceCode()!=0) throw DAOException("Required: Code should be zero");
string companyEmail=validateEmail(invoice->getCompanyEmail());
if(companyEmail.size()==0 || companyEmail.size()>80) throw DAOException("Invalid Company Email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email is not exist");
string customerEmail=validateEmail(invoice->getCustomerEmail());
if(customerEmail.size()==0 || customerEmail.size()>80) throw DAOException("Invalid Customer Email");
CustomerManager customerManager;
exist=customerManager.isCustomerWithEmailExist(customerEmail);
if(!exist) throw DAOException("Customer with given email is not exist, First to add customer");
time_t t;
forward_list<abc::IItem *> *itemList;
itemList=invoice->getItemList();
if(itemList==NULL) throw DAOException("Required item list");
forward_list<abc::IItem *>::iterator i=itemList->begin();
if(i==itemList->end()) throw DAOException("Required items, Invoice with zero items are not allowed");
//Variables declared
int numberOfItems=0;
double totalAmount=0;
abc::IItem *item;
string itemName;
int itemCode;
double netRate;
int quantity;
for(;i!=itemList->end();++i)
{
item=*i;
itemName=item->getItemName();
int size=itemName.size();
if(size==0 ) throw DAOException("Item name Required");
if(size>150) throw DAOException("Item name size cannot exceed 150 characters");
itemCode=item->getItemCode();
if(itemCode<=0) throw DAOException(string("Invalid item code Against item:")+itemName);
netRate=item->getNetRate();
if(netRate<=0) throw DAOException(itemName+string(" item rate can never be zero or negative"));
quantity=item->getQuantity();
if(quantity<=0) throw DAOException(itemName+string(" quantity cannot be zero or negative"));
if(quantity>ITEM_MAX_QUANTITY) throw DAOException(itemName+string(" item max quantity (50) reached"));
totalAmount+=(item->getNetRate()*item->getQuantity());
numberOfItems++;
}
double discount=invoice->getDiscount();
double tax=invoice->getTax();
if(tax<=0) tax=TAX_DEFAULT;	
else if(tax>=1) throw DAOException("Tax (in %) can never be more than equal to 1");
if(discount<=0) discount=DISCOUNT_DEFAULT;
else if(discount>=1) throw DAOException("Discount (in %) can never be more than equal to 1");
double amountPaid=invoice->getAmountPaid();
double amountDue=0;
double taxAmount=totalAmount*tax;
double discountAmount=totalAmount*discount;
totalAmount=totalAmount+taxAmount-discountAmount;
if(amountPaid<0) throw DAOException("Paid amount can never be negative");
if(amountPaid>totalAmount) 
{
char amount[10];
sprintf(amount,"%lf rs",amountPaid-totalAmount);
throw DAOException("You paid extra money of amount "+string(amount)+" more than total amount");
}
InvoiceManager::Header header;
_Invoice _invoice;
_Item _item;
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
ofstream dFile(INVOICE_FILE_NAME,ios::app | ios::binary);
header.numberOfRecords=1;
header.lastGeneratedInvoiceCode=1;
_invoice.invoiceCode=1;
strcpy(_invoice.companyEmail,companyEmail.c_str());
strcpy(_invoice.customerEmail,customerEmail.c_str());
time(&t);
_invoice.date=t;
_invoice.amountPaid=amountPaid;
_invoice.tax=tax;
_invoice.discount=discount;
amountDue=totalAmount-amountPaid;
_invoice.amountDue=amountDue;
_invoice.numberOfItems=numberOfItems;
dFile.write((char *)&header,sizeof(Header));
dFile.write((char *)&_invoice,sizeof(_Invoice));
for(i=itemList->begin();i!=itemList->end();++i)
{
item=*i;
itemName=item->getItemName();
itemCode=item->getItemCode();
netRate=item->getNetRate();
quantity=item->getQuantity();
sprintf(_item.itemName,itemName.c_str());
_item.itemCode=itemCode;
_item.quantity=quantity;
_item.netRate=netRate;
dFile.write((char *)&_item,sizeof(_Item));
}
dFile.close();
invoice->setInvoiceCode(header.lastGeneratedInvoiceCode);
invoice->setAmountDue(amountDue);
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.seekp(0,ios::beg);
header.numberOfRecords=1;
header.lastGeneratedInvoiceCode=1;
_invoice.invoiceCode=1;
strcpy(_invoice.companyEmail,companyEmail.c_str());
strcpy(_invoice.customerEmail,customerEmail.c_str());
time(&t);
_invoice.date=t;
_invoice.amountPaid=amountPaid;
_invoice.tax=tax;
_invoice.discount=discount;
amountDue=totalAmount-amountPaid;
_invoice.amountDue=amountDue;
_invoice.numberOfItems=numberOfItems;
dataFile.write((char *)&header,sizeof(Header));
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(i=itemList->begin();i!=itemList->end();++i)
{
item=*i;
itemName=item->getItemName();
itemCode=item->getItemCode();
netRate=item->getNetRate();
quantity=item->getQuantity();
sprintf(_item.itemName,itemName.c_str());
_item.itemCode=itemCode;
_item.quantity=quantity;
_item.netRate=netRate;
dataFile.write((char *)&_item,sizeof(_Item));
}
dataFile.close();
invoice->setInvoiceCode(header.lastGeneratedInvoiceCode);
invoice->setAmountDue(amountDue);
return;
}
dataFile.clear();
dataFile.seekp(0,ios::end);
header.lastGeneratedInvoiceCode++;
header.numberOfRecords++;
strcpy(_invoice.companyEmail,companyEmail.c_str());
strcpy(_invoice.customerEmail,customerEmail.c_str());
_invoice.invoiceCode=header.lastGeneratedInvoiceCode;
time(&t);
_invoice.date=t;
_invoice.amountPaid=amountPaid;
_invoice.tax=tax;
_invoice.discount=discount;
amountDue=totalAmount-amountPaid;
_invoice.amountDue=amountDue;
_invoice.numberOfItems=numberOfItems;
dataFile.seekp(0,ios::end);
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(i=itemList->begin();i!=itemList->end();++i)
{
item=*i;
itemName=item->getItemName();
itemCode=item->getItemCode();
netRate=item->getNetRate();
quantity=item->getQuantity();
sprintf(_item.itemName,itemName.c_str());
_item.itemCode=itemCode;
_item.quantity=quantity;
_item.netRate=netRate;
dataFile.write((char *)&_item,sizeof(_Item));
}
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close();
invoice->setInvoiceCode(header.lastGeneratedInvoiceCode);
invoice->setAmountDue(amountDue);
}
void InvoiceManager::updateInvoiceByInvoiceCode(abc::IInvoice *invoice) noexcept(false)
{
if(invoice==NULL) throw DAOException("Required invoice data, NULL encountered");
int invoiceCode=invoice->getInvoiceCode();
if(invoiceCode<=0) throw DAOException("Invalid invoice code");
string companyEmail=validateEmail(invoice->getCompanyEmail());
if(companyEmail.size()==0 || companyEmail.size()>80) throw DAOException("Invalid Company Email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email is not exist");
string customerEmail=validateEmail(invoice->getCustomerEmail());
if(customerEmail.size()==0 || customerEmail.size()>80) throw DAOException("Invalid Customer Email");
CustomerManager customerManager;
exist=customerManager.isCustomerWithEmailExist(customerEmail);
if(!exist) throw DAOException("Customer with given email is not exist, First to add customer");
time_t t;
forward_list<abc::IItem *> *itemList;
itemList=invoice->getItemList();
if(itemList==NULL) throw DAOException("Required item list");
forward_list<abc::IItem *>::iterator ii=itemList->begin();
if(ii==itemList->end()) throw DAOException("Required items, Invoice with zero items are not allowed");
//Variables declared
int numberOfItems=0;
double totalAmount=0;
abc::IItem *item;
string itemName;
int itemCode;
double netRate;
int quantity;
for(;ii!=itemList->end();++ii)
{
item=*ii;
itemName=item->getItemName();
int size=itemName.size();
if(size==0 ) throw DAOException("Item name Required");
if(size>150) throw DAOException("Item name size cannot exceed 150 characters");
itemCode=item->getItemCode();
if(itemCode<=0) throw DAOException(string("Invalid item code Against item:")+itemName);
netRate=item->getNetRate();
if(netRate<=0) throw DAOException(itemName+string(" item rate can never be zero or negative"));
quantity=item->getQuantity();
if(quantity<=0) throw DAOException(itemName+string(" quantity cannot be zero or negative"));
if(quantity>ITEM_MAX_QUANTITY) throw DAOException(itemName+string(" item max quantity (50) reached"));
totalAmount+=(item->getNetRate()*item->getQuantity());
numberOfItems++;
}
double discount=invoice->getDiscount();
double tax=invoice->getTax();
if(tax<=0) tax=TAX_DEFAULT;	
else if(tax>=1) throw DAOException("Tax (in %) can never be more than equal to 1");
if(discount<=0) discount=DISCOUNT_DEFAULT;
else if(discount>=1) throw DAOException("Discount (in %) can never be more than equal to 1");
double amountPaid=invoice->getAmountPaid();
double amountDue=0;
double taxAmount=totalAmount*tax;
double discountAmount=totalAmount*discount;
totalAmount=totalAmount+taxAmount-discountAmount;
if(amountPaid<0) throw DAOException("Paid amount can never be negative");
if(amountPaid>totalAmount) 
{
char amount[10];
sprintf(amount,"%d rs",amountPaid-totalAmount);
throw DAOException("You paid extra money of amount "+string(amount)+" more than total amount");
}
InvoiceManager::Header header;
_Invoice _invoice;
_Item _item;
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invalid invoice code");
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
dataFile.clear();
dataFile.seekg(sizeof(Header),ios::beg);
int found=0;
while(1)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(_invoice.invoiceCode==invoiceCode)
{
found=1;
break;
}
dataFile.seekg(sizeof(_Item)*_invoice.numberOfItems,ios::cur);
}
if(!found)
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
dataFile.clear();
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
if(tmpFile.fail()) 
{
dataFile.close();
throw DAOException("Unable to open file");
}
tmpFile.write((char *)&header,sizeof(Header));
dataFile.seekp(sizeof(Header),ios::beg);
while(1)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(_invoice.invoiceCode!=invoiceCode)
{
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
tmpFile.write((char *)&_item,sizeof(_Item));
}
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
strcpy(_invoice.companyEmail,companyEmail.c_str());
strcpy(_invoice.customerEmail,customerEmail.c_str());
time(&t);
_invoice.date=t;
_invoice.amountPaid=amountPaid;
_invoice.tax=tax;
_invoice.discount=discount;
amountDue=totalAmount-amountPaid;
_invoice.amountDue=amountDue;
_invoice.numberOfItems=numberOfItems;
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(ii=itemList->begin();ii!=itemList->end();++ii)
{
item=*ii;
itemName=item->getItemName();
itemCode=item->getItemCode();
netRate=item->getNetRate();
quantity=item->getQuantity();
sprintf(_item.itemName,itemName.c_str());
_item.itemCode=itemCode;
_item.quantity=quantity;
_item.netRate=netRate;
tmpFile.write((char *)&_item,sizeof(_Item));
}
invoice->setAmountDue(amountDue);
}
if(dataFile.fail()) break;
}
tmpFile.clear();
dataFile.clear();
dataFile.close();
tmpFile.close();
dataFile.open(INVOICE_FILE_NAME,ios::out | ios::binary);
tmpFile.open("tmp.tmp",ios::in | ios::binary);
tmpFile.seekp(0,ios::beg);
dataFile.seekg(0,ios::beg);
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: Unable to read");
dataFile.write((char *)&header,sizeof(Header));
while(1)
{
tmpFile.read((char *)&_invoice,sizeof(_Invoice));
if(tmpFile.fail()) break;
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
tmpFile.read((char *)&_item,sizeof(_Item));
if(tmpFile.fail()) break;
dataFile.write((char *)&_item,sizeof(_Item));
}
if(tmpFile.fail()) break;
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
void InvoiceManager::removeInvoiceByInvoiceCode(int invoiceCode) noexcept(false)
{
if(invoiceCode<=0) throw DAOException("Invalid invoice code");
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invalid invoice code");
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
if(header.numberOfRecords==0 || invoiceCode>header.lastGeneratedInvoiceCode)
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
header.numberOfRecords--;
tmpFile.write((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(_invoice.invoiceCode!=invoiceCode)
{
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
tmpFile.write((char *)&_item,sizeof(_Item));
}
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
}
if(dataFile.fail()) break;
}
dataFile.close();
tmpFile.close();
dataFile.open(INVOICE_FILE_NAME,ios::out | ios::binary);
if(dataFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.open("tmp.tmp",ios::in | ios::binary);
if(tmpFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);	
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: failed to read header");
dataFile.write((char *)&header,sizeof(Header));
while(true)
{
tmpFile.read((char *)&_invoice,sizeof(_Invoice));
if(tmpFile.fail()) break;
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
tmpFile.read((char *)&_item,sizeof(_Item));
if(tmpFile.fail()) break;
dataFile.write((char *)&_item,sizeof(_Item));
}
if(tmpFile.fail()) break;
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
void InvoiceManager::removeInvoiceByCustomerEmail(string &vCustomerEmail) noexcept(false)
{
string customerEmail=validateEmail(vCustomerEmail);
if(customerEmail.size()<=0 || customerEmail.size()>81) throw DAOException("Invalid email");
int exist;
CustomerManager customerManager;
exist=customerManager.isCustomerWithEmailExist(customerEmail);
if(!exist) throw DAOException("Customer with given email does not exist");
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invoice not available");
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invoice not available");
}
if(header.numberOfRecords==0 )
{
dataFile.close();
throw DAOException("Invoice not available");
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
tmpFile.write((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_invoice.customerEmail,customerEmail.c_str())!=0)
{
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
tmpFile.write((char *)&_item,sizeof(_Item));
}
}
else
{
header.numberOfRecords--;
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
}
if(dataFile.fail()) break;
}
tmpFile.clear();
tmpFile.seekp(0,ios::beg);
tmpFile.write((char *)&header,sizeof(Header));
dataFile.close();
tmpFile.close();
dataFile.open(INVOICE_FILE_NAME,ios::out | ios::binary);
if(dataFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.open("tmp.tmp",ios::in | ios::binary);
if(tmpFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);	
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: failed to read header");
dataFile.write((char *)&header,sizeof(Header));
while(true)
{
tmpFile.read((char *)&_invoice,sizeof(_Invoice));
if(tmpFile.fail()) break;
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
tmpFile.read((char *)&_item,sizeof(_Item));
if(tmpFile.fail()) break;
dataFile.write((char *)&_item,sizeof(_Item));
}
if(tmpFile.fail()) break;
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
void InvoiceManager::removeInvoiceByCompanyEmail(string &vCompanyEmail) noexcept(false)
{
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()<=0 || companyEmail.size()>81) throw DAOException("Invalid company email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email does not exist");
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invoice not available");
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invoice not available");
}
if(header.numberOfRecords==0 )
{
dataFile.close();
throw DAOException("Invoice not available");
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
tmpFile.write((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_invoice.companyEmail,companyEmail.c_str())!=0)
{
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
tmpFile.write((char *)&_item,sizeof(_Item));
}
}
else
{
header.numberOfRecords--;
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
}
if(dataFile.fail()) break;
}
tmpFile.clear();
tmpFile.seekp(0,ios::beg);
tmpFile.write((char *)&header,sizeof(Header));
dataFile.close();
tmpFile.close();
dataFile.open(INVOICE_FILE_NAME,ios::out | ios::binary);
if(dataFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.open("tmp.tmp",ios::in | ios::binary);
if(tmpFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);	
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: failed to read header");
dataFile.write((char *)&header,sizeof(Header));
while(true)
{
tmpFile.read((char *)&_invoice,sizeof(_Invoice));
if(tmpFile.fail()) break;
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
tmpFile.read((char *)&_item,sizeof(_Item));
if(tmpFile.fail()) break;
dataFile.write((char *)&_item,sizeof(_Item));
}
if(tmpFile.fail()) break;
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
forward_list<abc::IInvoice *> *InvoiceManager::getAllInvoice() noexcept(false)
{
Header header;
ifstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) throw DAOException("Zero invoice added");
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("Zero Invoice exist");
}
if(header.numberOfRecords==0) 
{
dataFile.close();
throw DAOException("Zero Invoice exist");
}
_Invoice _invoice;
_Item _item;
abc::IInvoice *invoice;
abc::IItem *item;
forward_list<abc::IInvoice *> *invoiceList;
invoiceList=new forward_list<abc::IInvoice *>;
forward_list<abc::IInvoice *>::iterator invoiceListIterator=invoiceList->before_begin();
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
int numberOfItems;
invoice=new Invoice;
invoice->setInvoiceCode(_invoice.invoiceCode);
invoice->setCustomerEmail(string(_invoice.customerEmail));
invoice->setCompanyEmail(string(_invoice.companyEmail));
invoice->setDate(_invoice.date);
invoice->setTax(_invoice.tax);
invoice->setDiscount(_invoice.discount);
numberOfItems=_invoice.numberOfItems;
invoice->setNumberOfItems(numberOfItems);
invoice->setAmountPaid(_invoice.amountPaid);
invoice->setAmountDue(_invoice.amountDue);

forward_list<abc::IItem *> itemList;
forward_list<abc::IItem *>::iterator itemListIterator=itemList.before_begin();
for(int i=0;i<numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
item=new Item;
item->setItemName(_item.itemName);
item->setItemCode(_item.itemCode);
item->setQuantity(_item.quantity);
item->setNetRate(_item.netRate);
itemListIterator=itemList.insert_after(itemListIterator,item);
}
invoice->setItemList(itemList);
for(itemListIterator=itemList.begin();itemListIterator!=itemList.end();++itemListIterator) delete *itemListIterator;
itemList.clear();
invoiceListIterator=invoiceList->insert_after(invoiceListIterator,invoice);
}
dataFile.close();
return invoiceList;
}
forward_list<abc::IInvoice *> * InvoiceManager::getInvoiceByCustomerEmail(string &customerEmail) noexcept(false)
{
return NULL;
}
forward_list<abc::IInvoice *> * InvoiceManager::getInvoiceByCompanyEmail(string &companyEmail) noexcept(false)
{
return NULL;
}
abc::IInvoice * InvoiceManager::getInvoiceByInvoiceCode(int invoiceCode) noexcept(false)
{
return NULL;
}
int InvoiceManager::isInvoiceWithCompanyEmailExist(const string &CompanyEmail) noexcept(false)
{
return 0;
}
int InvoiceManager::isInvoiceWithCustomerEmailExist(const string &customerEmail) noexcept(false)
{
return 0;
}

/*
void CustomerManager::updateCustomer(abc::ICustomer *customer) noexcept(false)
{
if(customer==NULL) throw DAOException("Required customer data, NULL encountered");
int customerCode=customer->getCustomerCode();
if(customerCode<=0) throw DAOException("Invalid customer code");
const string vName=customer->getCustomerName();
string customerName=trimmed(vName);
if(customerName.size()==0) throw DAOException("Customer name required, Name size zero");
if(customerName.size()>50) throw DAOException("Customer Name should not exeed 50 character");
string contactNumber=validateContactNumber(customer->getContactNumber());
if(contactNumber.size()==0) throw DAOException("Invalid contact number");
string email=validateEmail(customer->getEmail());
if(email.size()==0 || email.size()>80) throw DAOException("Invalid email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(email);
if(exist) throw DAOException("A company exist with given email, Use another email for customer use");
string street=trimmed(customer->getStreet());
if(street.size()==0) throw DAOException("Please enter street address");
if(street.size()>50) throw DAOException("Street address can not exceed 50 character");
string city=trimmed(customer->getCity());
if(city.size()==0) throw DAOException("Please enter city address");
if(city.size()>50) throw DAOException("City address can not exceed 50 character");
string state=trimmed(customer->getState());
if(state.size()==0) throw DAOException("Please enter state address");
if(state.size()>50) throw DAOException("State address can not exceed 50 character");
string country=trimmed(customer->getCountry());
if(country.size()==0) throw DAOException("Please enter country address");
if(country.size()>50) throw DAOException("Country address can not exceed 50 character");
int pinCode=customer->getPinCode();
if(pinCode>999999 || pinCode<100000) throw DAOException("Please enter correct Pin Code");
//Other All Type Of Validation
Header header;
_Customer _customer;
fstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invalid Customer code data");
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invalid customer code detail");
}
if(header.numberOfRecords==0 || customerCode>header.lastGeneratedCustomerCode)
{
dataFile.close();
throw DAOException("Invalid customer code detail");
}
int pos;
int found=0;
while(true)
{
pos=dataFile.tellg();
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(_customer.customerCode==customerCode)
{
found=1;
break;
}
}
if(!found)
{
dataFile.close();
throw DAOException("Customer with given code not found");
}
dataFile.clear();
dataFile.seekg(sizeof(Header),ios::beg);
while(true)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.email,email.c_str())==0 && _customer.customerCode!=customerCode)
{
dataFile.close();
throw DAOException(string("Customer already exist with email "+email));
}
if(compareStringIgnoreCase(_customer.contactNumber,contactNumber.c_str())==0 && _customer.customerCode!=customerCode)
{
dataFile.close();
throw DAOException(string("Customer already exist with contact number "+contactNumber));
}
}
dataFile.clear();
dataFile.seekp(pos,ios::beg);
strcpy(_customer.customerName,customerName.c_str());
strcpy(_customer.email,email.c_str());
strcpy(_customer.contactNumber,contactNumber.c_str());
strcpy(_customer.street,street.c_str());
strcpy(_customer.city,city.c_str());
strcpy(_customer.state,state.c_str());
strcpy(_customer.country,country.c_str());
_customer.pinCode=pinCode;
_customer.customerCode=customerCode;
dataFile.write((char *)&_customer,sizeof(_Customer));
dataFile.close();
}
void CustomerManager::updateCustomerAddressByEmail(abc::ICustomer *customer) noexcept(false)
{
string email=validateEmail(customer->getEmail());
if(email.size()==0 || email.size()>80) throw DAOException("Invalid email");
// done done: Later conveting password in hashing algoritm 
string street=trimmed(customer->getStreet());
if(street.size()==0) throw DAOException("Please enter street address");
if(street.size()>50) throw DAOException("Street address can not exceed 50 character");
string city=trimmed(customer->getCity());
if(city.size()==0) throw DAOException("Please enter city address");
if(city.size()>50) throw DAOException("City address can not exceed 50 character");
string state=trimmed(customer->getState());
if(state.size()==0) throw DAOException("Please enter state address");
if(state.size()>50) throw DAOException("State address can not exceed 50 character");
string country=trimmed(customer->getCountry());
if(country.size()==0) throw DAOException("Please enter country address");
if(country.size()>50) throw DAOException("Country address can not exceed 50 character");
int pinCode=customer->getPinCode();
if(pinCode>999999 || pinCode<100000) throw DAOException("Please enter correct Pin Code");
//Other All Type Of Validation
Header header;
_Customer _customer;
fstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invalid customer email id");
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invalid customer email id");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Invalid customer email id");
}
int pos;
int found=0;
while(true)
{
pos=dataFile.tellg();
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.email,email.c_str())==0)
{
found=1;
break;
}
}
if(!found)
{
dataFile.close();
throw DAOException("Invalid Email");
}
dataFile.clear();
dataFile.seekp(pos,ios::beg);
strcpy(_customer.street,street.c_str());
strcpy(_customer.city,city.c_str());
strcpy(_customer.state,state.c_str());
strcpy(_customer.country,country.c_str());
_customer.pinCode=pinCode;
dataFile.write((char *)&_customer,sizeof(_Customer));
dataFile.close();
}
void CustomerManager::removeCustomer(string &vEmail) noexcept(false)
{
string email=trimmed(vEmail);
if(email.size()==0) throw DAOException("Required email, email size cannot be zero");
if(email.size()>80) throw DAOException("Email size cannot exceed 80 characters");
_Customer _customer;
Header header;
fstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException(string("Invalid email")+email);
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException(string("Invalid email")+email);
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException(string("Invalid email")+email);
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
header.numberOfRecords--;
tmpFile.write((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.email,email.c_str())!=0)
{
tmpFile.write((char *)&_customer,sizeof(_customer));
}
}
tmpFile.close();
dataFile.close();
tmpFile.clear();
dataFile.clear();
dataFile.open(CUSTOMER_FILE_NAME,ios::out | ios::binary);
tmpFile.open("tmp.tmp",ios::in | ios::binary);
tmpFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);	
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: failed to read header");
dataFile.write((char *)&header,sizeof(Header));
while(true)
{
tmpFile.read((char *)&_customer,sizeof(_Customer));
if(tmpFile.fail()) break;
dataFile.write((char *)&_customer,sizeof(_Customer));
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
forward_list<abc::ICustomer *> * CustomerManager::getAllCustomer() noexcept(false)
{
Header header;
ifstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) throw DAOException("Customer does not exist");
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("Customer does not exist");
}
if(header.numberOfRecords==0) 
{
dataFile.close();
throw DAOException("Customer does not exist");
}
_Customer _customer;
abc::ICustomer *customer;
forward_list<abc::ICustomer *> *customerList;
customerList=new forward_list<abc::ICustomer *>;
forward_list<abc::ICustomer *>::iterator listi=customerList->before_begin();
while(true)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
customer=new Customer;
customer->setCustomerName(string(_customer.customerName));
customer->setEmail(string(_customer.email));
customer->setContactNumber(string(_customer.contactNumber));
customer->setStreet(string(_customer.street));
customer->setCity(string(_customer.city));
customer->setCountry(string(_customer.country));
customer->setState(string(_customer.state));
customer->setPinCode(_customer.pinCode);
customer->setCustomerCode(_customer.customerCode);
listi=customerList->insert_after(listi,customer);
}
dataFile.close();
return customerList;
}
abc::ICustomer * CustomerManager::getCustomerByEmail(string &vEmail) noexcept(false)
{
string email=validateEmail(vEmail);
if(email.size()==0) throw DAOException("Invalid Email");
if(email.size()>80) throw DAOException("Email can not exceed 80 characters");
ifstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) throw DAOException("Invalid customer email");
Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("Invalid customer email");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Invalid customer email");
}
_Customer _customer;
abc::ICustomer *customer;
while(1)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.email,email.c_str())==0)
{
customer=new Customer;
customer->setCustomerName(string(_customer.customerName));
customer->setEmail(string(_customer.email));
customer->setContactNumber(string(_customer.contactNumber));
customer->setStreet(string(_customer.street));
customer->setCity(string(_customer.city));
customer->setCountry(string(_customer.country));
customer->setState(string(_customer.state));
customer->setPinCode(_customer.pinCode);
customer->setCustomerCode(_customer.customerCode);
dataFile.close();
return customer;
}
}
dataFile.close();
throw DAOException("Invalid email");
}
int CustomerManager::isCustomerWithEmailExist(const string &vEmail) noexcept(false)
{
string email=validateEmail(vEmail);
if(email.size()==0) return 0;
if(email.size()>80) return 0;
ifstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::binary);
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
_Customer _customer;
abc::ICustomer *customer;
while(1)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.email,email.c_str())==0)
{
dataFile.close();
return 1;
}
}
dataFile.close();
return 0;
}
void CustomerManager::showCustomerProfile(const string &vEmail) noexcept(false)
{
CustomerManager customerManager;
abc::ICustomer *customer;
string email=vEmail;
try
{
customer=customerManager.getCustomerByEmail(email);
}catch(DAOException daoException)
{
throw DAOException(daoException.what());
}
for(int i=0;i<120;i++) cout<<"_";
cout<<endl;
cout<<"----------Customer Login Details----------"<<endl;
printf("Customer Name: %-80s    Customer Code: %-15d\n",customer->getCustomerName().c_str(),customer->getCustomerCode());
printf("Email: %-80s           Contact Number: %-15s\n\n",customer->getEmail().c_str(),customer->getContactNumber().c_str());

cout<<"----------Customer Address----------"<<endl;
printf("Street:  %-50s    City   : %-50s\n",customer->getStreet().c_str(),customer->getCity().c_str());
printf("State :  %-50s    Country: %-50s\n",customer->getState().c_str(),customer->getCountry().c_str());
printf("Pin Code: %-15d\n\n",customer->getPinCode());

for(int i=0;i<120;i++) cout<<"_";
cout<<endl;
cout<<endl;
delete customer;
}
*/