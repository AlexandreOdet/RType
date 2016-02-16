#include "WMutex.hh"


Mutex::Mutex(void)
{
  this->mutex = CreateMutex(NULL, false, NULL);
}

Mutex::~Mutex(void)
{
  CloseHandle(this->mutex);
}

void    Mutex::lock(void)
{
  WaitForSingleObject(this->mutex, INFINITE);
}

void    Mutex::unlock(void)
{
  ReleaseMutex(this->mutex);
}

bool    Mutex::trylock(void)
{
  int	res;

  res = WaitForSingleObject(this->mutex, 0);
  if (res == WAIT_OBJECT_0)
    return (true);
  else
    return (false);
}

HANDLE *Mutex::handle()
{
  return (&this->mutex);
}
