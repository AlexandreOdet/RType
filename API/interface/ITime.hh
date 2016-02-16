//
// ITime.hh for ITime in /home/lopez_t/rtype/API/interface
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Nov 24 14:01:32 2015 Thibaut Lopez
// Last update Fri Dec 18 10:41:06 2015 Thibaut Lopez
//

#ifndef	ITIME_HH
#define	ITIME_HH

#include <iostream>
#include <string>

class	ITime
{
public:
  virtual ~ITime() {};
  virtual void	now(std::size_t &, std::size_t &) const = 0;
  virtual void	sub(const std::size_t &, const std::size_t &, const std::size_t &, const std::size_t &, std::size_t &, std::size_t &) const = 0;
  virtual void	Usleep(const std::size_t &) const = 0;
};

#endif
