#ifndef __ULOADER__
#define __ULOADER__

#include "ILoader.hh"
#include <dlfcn.h>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>

typedef IEnemy *(*load_func)();

class ULoader : public ILoader
{
public:
  explicit ULoader();
  virtual ~ULoader();
  virtual bool openLibrary(const std::string &);
  virtual void closeLibrary() const;
  virtual IEnemy *getInstance() const;
private:
  void       *_handle;
  load_func   _loadf;
};

#endif /*__ULOADER__*/
