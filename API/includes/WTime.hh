//
// WTime.hh for WTime in /home/lopez_t/rtype/API/includes
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Nov 24 14:07:37 2015 Thibaut Lopez
// Last update Fri Dec 18 10:41:33 2015 Thibaut Lopez
//

#ifndef	WTIME_HH
#define	WTIME_HH

#include <iostream>
#include <string>
#include <time.h>
#include <sys/timeb.h>
#include "ITime.hh"

class	WTime : public ITime
{
public:
  explicit WTime();
  virtual ~WTime();
  void	now(std::size_t &, std::size_t &) const;
  void	sub(const std::size_t &, const std::size_t &, const std::size_t &, const std::size_t &, std::size_t &, std::size_t &) const;
  void	Usleep(const std::size_t &) const;
};

#endif
