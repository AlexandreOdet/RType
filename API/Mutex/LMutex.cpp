//
// Mutex.cpp for  in /home/coudra_c/rendu/TP/thread_pool
// 
// Made by Coudray Colin
// Login   <coudra_c@epitech.net>
// 
// Started on  Sat Apr 18 16:22:59 2015 Coudray Colin
// Last update Tue Dec  1 12:16:49 2015 Coudray Colin
//

#include "LMutex.hh"

Mutex::Mutex(void)
{
  this->mutex = PTHREAD_MUTEX_INITIALIZER;
}

Mutex::~Mutex(void)
{
  pthread_mutex_destroy(&this->mutex);
}

void    Mutex::lock(void)
{
  pthread_mutex_lock(&this->mutex);
}

void    Mutex::unlock(void)
{
  pthread_mutex_unlock(&this->mutex);
}

bool    Mutex::trylock(void)
{
  return (pthread_mutex_trylock(&this->mutex));
}

pthread_mutex_t	*Mutex::handle()
{
  return (&this->mutex);
}
