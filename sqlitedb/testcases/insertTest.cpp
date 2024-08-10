#include<sqlitedb>
#include<iostream>
using namespace std;
using namespace sqlitedb;
int main()
{
SqliteDB sqliteDB;
try
{
sqliteDB.open("student.db")
string sql="insert into student values(101,'sam','M');";
sqliteDB.executeInsert(sql);
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}