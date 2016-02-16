#include "LThread.hpp"

Thread::Thread(thr_func action)
{
  this->thread_start = action;
  this->working = false;
}

Thread::~Thread() {}

int		Thread::start(void *data)
{
  this->working = true;
  return (pthread_create(&this->thread_id, NULL, this->thread_start, data));
}

void		*Thread::join(void)
{
  void		*retval;

  if (pthread_join(this->thread_id, &retval) != 0)
    {
      this->working = false;
      return (NULL);
    }
  this->working = false;
  return (retval);
}

bool		Thread::isWorking(void) const
{
  return (this->working);
}

void		Thread::exit(void)
{
  pthread_exit(NULL);
}
