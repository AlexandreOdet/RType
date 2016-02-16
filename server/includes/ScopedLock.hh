//
// ScopedLock.hh for  in /home/coudra_c/rendu/TP/thread_pool
// 
// Made by Coudray Colin
// Login   <coudra_c@epitech.net>
// 
// Started on  Sat Apr 18 16:55:25 2015 Coudray Colin
// Last update Sat Apr 18 17:03:12 2015 Coudray Colin
//

#ifndef SCOPEDLOCK_HH_
#define SCOPEDLOCK_HH_

#include "IMutex.hpp"

class ScopedLock
{
public:
  ScopedLock(IMutex *mutex);
  ~ScopedLock();

private:
  ScopedLock(ScopedLock const &);
  ScopedLock&	operator=(ScopedLock const &);

  IMutex	*mutex;
};

#endif
