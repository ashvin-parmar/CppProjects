#include<dbdl/daoexception>
using namespace inventory;
using namespace data_layer_db;

DAOException::DAOException()
{
this->messege="";
}
DAOException::DAOException(const DAOException &other)
{
this->messege=other.messege;
}
DAOException::DAOException(string messege)
{
this->messege=messege;
}
DAOException& DAOException::operator=(const DAOException &other)
{
this->messege=other.messege;
return *this;
}
DAOException::~DAOException() throw()
{
// Do Nothing
}
const char * DAOException::what() const throw()
{
return this->messege.c_str();
}