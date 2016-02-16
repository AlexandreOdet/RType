//
// Mutex.hh for  in /home/coudra_c/rendu/TP/thread_pool
// 
// Made by Coudray Colin
// Login   <coudra_c@epitech.net>
// 
// Started on  Sat Apr 18 16:18:57 2015 Coudray Colin
// Last update Tue Dec 15 10:50:53 2015 Coudray Colin
//

#ifndef LMUTEX_HH_
#define LMUTEX_HH_

#include <pthread.h>
#include "IMutex.hpp"

class Mutex : public IMutex
{
public:
  Mutex(void);
  virtual			~Mutex(void);
  virtual void			lock(void);
  virtual void			unlock(void);
  virtual bool			trylock(void);
  virtual pthread_mutex_t	*handle();

protected:
  pthread_mutex_t		mutex;
};

#endif
