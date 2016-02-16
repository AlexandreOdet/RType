#ifndef WMUTEX_HH_
#define WMUTEX_HH_

#include <windows.h>
#include "IMutex.hpp"

class Mutex : public IMutex
{
public:
  Mutex(void);
  virtual                       ~Mutex(void);
  virtual void                  lock(void);
  virtual void                  unlock(void);
  virtual bool                  trylock(void);
  virtual HANDLE		*handle();

protected:
  HANDLE			mutex;
};

#endif
