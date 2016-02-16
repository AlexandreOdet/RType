//
// Timer.hh for Timer in /home/lopez_t/rtype/server
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Mon Nov 23 17:31:13 2015 Thibaut Lopez
// Last update Tue Dec  1 19:13:33 2015 Thibaut Lopez
//

#ifndef	TIMER_HH
#define	TIMER_HH

#include <string>
#include <iostream>
#include "STTime.hh"

class	IClock
{
public:
  virtual void		ring() = 0;
};

class	Timer
{
private:
  std::size_t		_sec;
  std::size_t		_usec;
  IClock		*_clock;

public:
  Timer();
  Timer(const std::size_t &, const std::size_t &);
  Timer(Timer const &);
  virtual ~Timer();
  virtual Timer const	&operator=(Timer const &);
  void			clock(IClock *);
  IClock		*clock() const;
  void			setDeadline(const std::size_t &, const std::size_t &);
  void			sec(const std::size_t &);
  const std::size_t	&sec() const;
  void			usec(const std::size_t &);
  const std::size_t	&usec() const;
  bool			ring();
};

#endif
