#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
#include <exception>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

class Exception : public std::exception
{
public:
  Exception(std::string const &, std::string const &) throw();
  Exception(const Exception &) throw();
  Exception &operator=(const Exception &) throw();
  virtual ~Exception() throw();

  virtual const char *what() const throw();
  virtual const char *where() const throw();

private:
  std::string	_what;
  std::string	_where;
};

#endif /* _EXCEPTION_H_ */
