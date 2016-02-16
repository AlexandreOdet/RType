#include "ThreadPool.hpp"

#ifndef _WIN32
#include <unistd.h>
#endif

#ifdef _WIN32
typedef void			*(*thr_func)(void*);
#endif

ThreadPool::ThreadPool()
{
}

void ThreadPool::addRoom(thr_func begin, void *map)
{
  Task *task = new Task(begin, SafeData(map));
  Thread *thr = new Thread(&ThreadPool::entry);

  this->thread.push_back(thr);
  thr->start(task);
}

void			      *ThreadPool::entry(void *data)
{
  Task			      *task = (Task *)data;

  task->first(&task->second);
  delete(task);
  Thread::exit();
  return (NULL);
}

size_t                        ThreadPool::remainingTasks()
{
  return (this->thread.size());
}

ThreadPool::~ThreadPool()
{
  for (Thread *t : thread)
    {
      delete(t);
    }
}
