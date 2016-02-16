//
// ThreadPool.hh for  in /home/coudra_c/rendu/TP/thread_pool
//
// Made by Coudray Colin
// Login   <coudra_c@epitech.net>
//
// Started on  Sun Apr 19 13:45:16 2015 Coudray Colin
// Last update Mon Dec 21 15:55:45 2015 colin
//

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include "TSafeQueue.hpp"
#ifdef _WIN32
#include "WThread.hpp"
#else
#include "LThread.hpp"
#endif

#include <vector>
#include <utility>


class SafeData : public Mutex
{
public:
  SafeData(void *data)
  {
    this->data = data;
  }
  virtual ~SafeData(){}

  void	*data;
};

class ThreadPool
{
public:

  typedef std::pair<thr_func, SafeData> Task;

  ThreadPool();
  static void			*entry(void *data);

  void				addRoom(thr_func, void*);
  size_t			remainingTasks();
  ~ThreadPool();

protected:
  std::vector<Thread *>	thread;
};

#endif
