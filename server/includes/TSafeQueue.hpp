//
// TSafeQueue.hpp for  in /home/coudra_c/rendu/TP/thread_pool
// 
// Made by Coudray Colin
// Login   <coudra_c@epitech.net>
// 
// Started on  Sun Apr 19 11:08:16 2015 Coudray Colin
// Last update Tue Dec 15 16:47:28 2015 Thibaut Lopez
//

#ifndef TSAFEQUEUE_HPP_
#define TSAFEQUEUE_HPP_

#include <list>
#ifdef _WIN32
#include "WMutex.hh"
#else
#include "LMutex.hh"
#endif

#include "ScopedLock.hh"

template<typename T>class TSafeQueue
{
public:
  TSafeQueue()
  {
    this->finish = false;
    this->shared_mutex = false;
    this->mutex = new Mutex;
  }

  TSafeQueue(Mutex *mutex)
  {
    this->finish = false;
    this->mutex = mutex;
    this->shared_mutex = true;
  }

  ~TSafeQueue(void)
  {
    if (this->shared_mutex == false)
      delete this->mutex;
  }
  
  void		push(T value)
  {
    ScopedLock	s_lock(this->mutex);

    this->finish = false;
    this->queue.push_back(value);
  }

  unsigned int	size(void)
  {
    ScopedLock	s_lock(this->mutex);

    return (this->queue.size());
  }

  bool		tryPop(T* value)
  {
    ScopedLock	s_lock(this->mutex);

    *value = 0;
    if (this->queue.size() == 0)
      return (false);
    *value = this->queue.front();
    this->queue.pop_front();
    return (true);
  }

  bool		isFinished(void)
  {
    ScopedLock	s_lock(this->mutex);

    return (this->finish);
  }

  void		setFinished(void)
  {
    ScopedLock	s_lock(this->mutex);

    if (this->queue.size() == 0)
      this->finish = true;
  }

private:
  std::list<T>	queue;
  bool		finish;
  Mutex		*mutex;
  bool		shared_mutex;
};

#endif
