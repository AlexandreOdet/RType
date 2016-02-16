#ifndef _WLOADER_
#define _WLOADER_

#include <iostream>
#include <windows.h>

typedef IEnemy *(*load_func)();
typedef void (*unload_func)(IEnemy *);

class WLoader : public ILoader
{
public:
  explicit WLoader();
  virtual ~WLoader();
  virtual bool openLibrary(const std::string &);
  virtual void closeLibrary()const;
  virtual IEnemy *getInstance() const;
private:
  HMODULE _library;
  load_func load_func_ptr;
  unload_func unload_func_ptr;
};

#endif
