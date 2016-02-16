//
// LTime.hh for LTime in /home/lopez_t/rtype/API/includes
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Nov 24 14:03:04 2015 Thibaut Lopez
// Last update Fri Dec 18 10:41:38 2015 Thibaut Lopez
//

#ifndef	LTIME_HH
#define	LTIME_HH

#include <iostream>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include "ITime.hh"

class	LTime : public ITime
{
public:
  explicit LTime();
  virtual ~LTime();
  void	now(std::size_t &, std::size_t &) const;
  void	sub(const std::size_t &, const std::size_t &, const std::size_t &, const std::size_t &, std::size_t &, std::size_t &) const;
  void	Usleep(const std::size_t &) const;
};

#endif
