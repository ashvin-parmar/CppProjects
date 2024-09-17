#include<sqlitedb>
#include<iostream>

using namespace std;
using namespace sqlitedb;
SQLiteDB::SQLiteDB()
{

}
SQLiteDB::SQLiteDB(string filename)
{
this->filename=filename;
}
SQLiteDB::SQLiteDB(const SQLiteDB &other)
{
this->filename=other.filename;
}
SQLiteDB & SQLiteDB::operator=(const SQLiteDB &other)
{
this->filename=other.filename;
return *this;
}
void SQLiteDB::open(string filename) noexcept(false)
{
sqlite3 *db;
int result;
result=sqlite3_open(filename,&db);
if(result!=SQLITE_OK)
{
throw SQLiteException(string("Cannot connect to ")+filename+string(" Reason : ")+string(sqlite3_errmsg(db)));
sqlite3_close()
}


}
void SQLiteDB::close() noexcept(false)
{

}
void SQLiteDB::createTable(string sql) noexcept(false)
{

}
void SQLiteDB::executeInsert(string sql) noexcept(false)
{

}
void SQLiteDB::executeUpdate(string sql) noexcept(false)
{

}
void SQLiteDB::executeDelete(string sql) noexcept(false)
{

}
