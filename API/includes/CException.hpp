#ifndef __CEXPETION_HPP
#define __CEXPETION_HPP

#include <iostream>
#include <exception>

class	FileError : public std::exception
{
private:
  std::string	type;
  std::string	file;

public:
  FileError(std::string const &_type = "", std::string const &_file="") throw() : type(_type), file(_file) {}
  virtual ~FileError() throw () {}

  virtual const char *what() const throw()
  {
    return type.c_str();
  }

  std::string	where() const throw()
  {
    return file;
  }
};

#endif
