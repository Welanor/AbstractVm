#include "Exception.hpp"

Exception::Exception(std::string const &what, std::string const &where) throw() : exception()
{
  _what = what;
  _where = where;
}

Exception::Exception(const Exception &cpy) throw() : exception()
{
  _what = cpy.what();
  _where = cpy.where();
}

Exception &Exception::operator= (const Exception &cpy) throw()
{
  _what = cpy.what();
  _where = cpy.where();
  return (*this);
}

Exception::~Exception() throw()
{

}

const char *Exception::what() const throw()
{
  return (_what.c_str());
}

const char *Exception::where() const throw()
{
  return (_where.c_str());
}
