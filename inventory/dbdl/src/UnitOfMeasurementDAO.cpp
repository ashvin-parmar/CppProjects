//Compilation: g++ -c *.cpp -I ..\include -I ..\..\..\tmcommon\include

#include<stdio.h>
#include<dbdl/iuom>
#include<dbdl/uom>
#include<dbdl/iuomdao>
#include<dbdl/uomdao>
#include<dbdl/daoexception>
#include<sqlite3.h>
#include<string.h>
#include<common/stringutils>
#include<fstream>
using namespace inventory;
using namespace data_layer_db;
using namespace stringutils;
void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
int resultCode;
sqlite3 *db;
char *errorMessege=NULL;
char sql[1001];
if(title.length()==0) throw DAOException("Title required, Length of title is zero");
if(title.length()>50) throw DAOException("Title cannot exceed 50 characters");
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
sqlite3_close(db);
throw DAOException(string("Unable to connect file, Reason: ")+string(sqlite3_errmsg(db)));
}
//To Create table start here
ifstream dataFile(FILE_NAME);
char m;
dataFile>>m;
if(dataFile.fail())
{
strcpy(sql,"create table unitofmeasurement(code INTEGER PRIMARY KEY AUTOINCREMENT, title char(50) not null unique);");
resultCode=sqlite3_exec(db,sql,0,0,&errorMessege);
if(resultCode!=SQLITE_OK)
{
string terminateMessege=string("Unable to create table, Reason: ")+string(errorMessege);
sqlite3_free(errorMessege);
sqlite3_close(db);
throw DAOException(terminateMessege);
}
}
dataFile.close();
//To Create table ends here
sprintf(sql,"insert into unitofmeasurement (title) values('%s');",title.c_str());
resultCode=sqlite3_exec(db,sql,0,0,&errorMessege);
if(resultCode!=SQLITE_OK)
{
string terminateMessege=string("Unable to insert record, Reason: ")+string(errorMessege);
sqlite3_free(errorMessege);
sqlite3_close(db);
throw DAOException(terminateMessege);
}
unitOfMeasurement->setCode(sqlite3_last_insert_rowid(db));
sqlite3_close(db);
}
void UnitOfMeasurementDAO::update(abc::IUnitOfMeasurement *unitOfMeasurement) noexcept(false)
{
char arr[100];
int code;
int resultCode;
char *errorMessege=NULL;
char sql[1000];
sqlite3 *db;
code=unitOfMeasurement->getCode();
if(code<=0) 
{
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0) throw DAOException("Title required, length is zero.");
if(title.length()>50) throw DAOException("Length of title cannot exceed 50 characters.");
ifstream dataFile(FILE_NAME);
if(dataFile.fail()) 
{
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
dataFile.close();
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
sprintf(arr,"Unable to connect file, Reason: %s",sqlite3_errmsg(db));
sqlite3_close(db);
throw DAOException(string(arr));
}
sprintf(sql,"update unitofmeasurement set title='%s' where code=%d;",title.c_str(),code);
resultCode=sqlite3_exec(db,sql,0,0,&errorMessege);
if(resultCode==SQLITE_OK)
{
sqlite3_close(db);
return;
}
sprintf(arr,"Invalid code: %d",code);
sqlite3_close(db);
throw DAOException(string(arr));
}
void UnitOfMeasurementDAO::remove(int code) noexcept(false)
{
char arr[100];
if(code<=0)
{
sprintf(arr,"Invalid code: %d",code);
throw DAOException(string(arr));
}
ifstream dataFile(FILE_NAME);
if(dataFile.fail())
{
sprintf(arr,"Invalid code: %d",code);
throw DAOException(string(arr));
}
dataFile.close();
int resultCode;
char *errorMessege;
char sql[1000];
sqlite3 *db;
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
sprintf(arr,"Invalid code: %d",code);
throw DAOException(string(arr));
sqlite3_close(db);
throw DAOException(arr);
}
sprintf(sql,"delete from unitofmeasurement where code='%d';",code);
resultCode=sqlite3_exec(db,sql,0,0,&errorMessege);
if(resultCode==SQLITE_OK)
{
sqlite3_close(db);
return ;
}
sqlite3_free(errorMessege);
sqlite3_close(db);
throw DAOException(string("Unable to fetch data, Reason: Invalid code"));
}
abc::IUnitOfMeasurement *UnitOfMeasurementDAO::getByTitle(string vTitle) noexcept(false)
{
string title=trimmed(vTitle);
if(title.length()==0) throw DAOException("Title required, Length of title is zero");
if(title.length()>50) throw DAOException("Title cannot exceed 50 characters");
sqlite3 *db;
char *errorMessege;
int resultCode;
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
string terminateMessege=string("Unable to fetch data, Reason: ")+string(sqlite3_errmsg(db));
sqlite3_close(db);
throw DAOException(terminateMessege);
}
char sql[1000];
sprintf(sql,"select code,title from unitofmeasurement where UPPER(title)=UPPER('%s');",title.c_str());
sqlite3_stmt *stmt;
resultCode=sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
if(resultCode!=SQLITE_OK)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
throw DAOException(string("Unable to fetch data, Reason: Invalid title"));
}
abc::IUnitOfMeasurement *unitOfMeasurement;
resultCode=sqlite3_step(stmt);
if(resultCode!=SQLITE_ROW)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
throw DAOException("Unable to fetch data, Reason: Invalid title");
}
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(sqlite3_column_int(stmt,0));
unitOfMeasurement->setTitle(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt,1))));
sqlite3_finalize(stmt);
sqlite3_close(db);
return unitOfMeasurement;
}
abc::IUnitOfMeasurement *UnitOfMeasurementDAO::getByCode(int code) noexcept(false)
{
char arr[100];
if(code<=0)
{
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
sqlite3 *db;
char *errorMessege;
int resultCode;
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
string terminateMessege=string("Unable to fetch data, Reason: ")+string(sqlite3_errmsg(db));
sqlite3_close(db);
throw DAOException(terminateMessege);
}
char sql[1000];
sprintf(sql,"select code , title from unitofmeasurement where code=%d;",code);
sqlite3_stmt *stmt;
resultCode=sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
if(resultCode!=SQLITE_OK)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
throw DAOException("Unable to fetch data, Reason: Invalid code");
}
abc::IUnitOfMeasurement *unitOfMeasurement;
resultCode=sqlite3_step(stmt);
if(resultCode!=SQLITE_ROW)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
throw DAOException("Unable to fetch data, Reason: Invalid code");
}
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(sqlite3_column_int(stmt,0));
unitOfMeasurement->setTitle(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt,1))));
sqlite3_finalize(stmt);
sqlite3_close(db);
return unitOfMeasurement;
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() noexcept(false)
{
sqlite3 *db;
char *errorMessege;
int resultCode;
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
string terminateMessege=string("Unable to fetch data, Reason: ")+string(sqlite3_errmsg(db));
sqlite3_close(db);
throw DAOException(terminateMessege);
}
string sql="select code , title from unitofmeasurement";
sqlite3_stmt *stmt;
resultCode=sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,NULL);
if(resultCode!=SQLITE_OK)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
throw DAOException("Unable to fetch data, Reason: Data not available");
}
abc::IUnitOfMeasurement *unitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *> *list;
list=new forward_list<abc::IUnitOfMeasurement*>;
forward_list<abc::IUnitOfMeasurement *>::iterator i=list->before_begin();
while(sqlite3_step(stmt)==SQLITE_ROW)
{
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(sqlite3_column_int(stmt,0));
unitOfMeasurement->setTitle(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt,1))));
i=list->insert_after(i,unitOfMeasurement);
}
sqlite3_finalize(stmt);
sqlite3_close(db);
return list;
}
int UnitOfMeasurementDAO::getCount() noexcept(false)
{
sqlite3 *db;
char *errorMessege;
int resultCode;
int count=0;
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
sqlite3_close(db);
return count;
}
string sql="select count(*) from unitofmeasurement";
sqlite3_stmt *stmt;
resultCode=sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,NULL);
if(resultCode!=SQLITE_OK)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
return count;
}
if(sqlite3_step(stmt)==SQLITE_ROW)
{
count=sqlite3_column_int(stmt,0);
}
sqlite3_finalize(stmt);
sqlite3_close(db);
return count;
}
int UnitOfMeasurementDAO::titleExist(string vTitle) noexcept(false)
{
string title=trimmed(vTitle);
if(title.length()==0) return false;
if(title.length()>50) return false;
sqlite3 *db;
int resultCode;
int exist=0;
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
sqlite3_close(db);
return false;
}
char sql[1000];
sprintf(sql,"select title from unitofmeasurement where UPPER(title)=UPPER('%s');",title.c_str());
sqlite3_stmt *stmt;
resultCode=sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
if(resultCode!=SQLITE_OK)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
return false;
}
if(sqlite3_step(stmt)==SQLITE_ROW)
{
exist=1;
}
sqlite3_finalize(stmt);
sqlite3_close(db);
return exist;
}
int UnitOfMeasurementDAO::codeExist(int code) noexcept(false)
{
char arr[100];
if(code<=0)
{
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
sqlite3 *db;
int resultCode;
int exist=0;
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
sqlite3_close(db);
return exist;
}
char sql[1000];
sprintf(sql,"select code from unitofmeasurement where code=%d;",code);
sqlite3_stmt *stmt;
resultCode=sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
if(resultCode!=SQLITE_OK)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
return exist;
}
if(sqlite3_step(stmt)==SQLITE_ROW)
{
exist=1;
}
sqlite3_finalize(stmt);
sqlite3_close(db);
return exist;
}