#include "WThread.hpp"

typedef void			*(*thr_func)(void*);

Thread::Thread(thr_func action)
{
  this->thread_start = action;
  this->working = false;
}

Thread::~Thread()
{
  CloseHandle(this->thread_handle);
}

int		Thread::start(void *data)
{
  this->working = true;
  this->thread_handle = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(this->thread_start), data, 0, reinterpret_cast<LPDWORD>(&this->thread_id));
  return (!(this->thread_handle == NULL));
}

void		*Thread::join(void)
{
  void		*retval;

  if (WaitForSingleObject(this->thread_handle, INFINITE) != WAIT_OBJECT_0)
    {
      this->working = false;
      return (NULL);
    }
  this->working = false;
  return (NULL);
}

bool		Thread::isWorking(void) const
{
  return (this->working);
}

void		Thread::exit()
{
  ExitThread(0);
}
