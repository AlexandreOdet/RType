//
// LTime.cpp for LTime in /home/lopez_t/rtype/API/Time
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Nov 24 14:03:04 2015 Thibaut Lopez
// Last update Fri Dec 18 10:42:04 2015 Thibaut Lopez
//

#include "LTime.hh"

LTime::LTime()
{
}

LTime::~LTime()
{
}

void			LTime::now(std::size_t &sec, std::size_t &usec) const
{
  struct timeval	tv;

  gettimeofday(&tv, NULL);
  sec = tv.tv_sec;
  usec = tv.tv_usec;
}

void			LTime::sub(const std::size_t &aSec, const std::size_t &aUsec, const std::size_t &bSec, const std::size_t &bUsec, std::size_t &rSec, std::size_t &rUsec) const
{
  struct timeval	aTV;
  struct timeval	bTV;
  struct timeval	cTV;

  aTV.tv_sec = aSec;
  aTV.tv_usec = aUsec;
  bTV.tv_sec = bSec;
  bTV.tv_usec = bUsec;
  timersub(&aTV, &bTV, &cTV);
  rSec = cTV.tv_sec;
  rUsec = cTV.tv_usec;
}

void			LTime::Usleep(const std::size_t &usec) const
{
  usleep(usec);
}
