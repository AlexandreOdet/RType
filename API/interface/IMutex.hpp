//
// IMutex.hh for  in /home/coudra_c/rendu/TP/thread_pool
// 
// Made by Coudray Colin
// Login   <coudra_c@epitech.net>
// 
// Started on  Sat Apr 18 16:18:23 2015 Coudray Colin
// Last update Sat Apr 18 16:32:35 2015 Coudray Colin
//

#ifndef IMUTEX_HH_
#define IMUTEX_HH_

class IMutex
{
public:
  virtual       ~IMutex(void) {}
  virtual void  lock(void) = 0;
  virtual void  unlock(void) = 0;
  virtual bool  trylock(void) = 0;
};

#endif
