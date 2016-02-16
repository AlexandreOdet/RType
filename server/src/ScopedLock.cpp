//
// ScopedLock.cpp for  in /home/coudra_c/rendu/TP/thread_pool
// 
// Made by Coudray Colin
// Login   <coudra_c@epitech.net>
// 
// Started on  Sat Apr 18 16:58:26 2015 Coudray Colin
// Last update Sat Apr 18 17:07:36 2015 Coudray Colin
//

#include "ScopedLock.hh"

ScopedLock::ScopedLock(IMutex *mutex)
{
  this->mutex = mutex;
  this->mutex->lock();
}

ScopedLock::~ScopedLock()
{
  this->mutex->unlock();
}
