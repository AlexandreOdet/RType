//
// WTime.cpp for WTime in /home/lopez_t/rtype/API/Time
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Nov 24 14:07:37 2015 Thibaut Lopez
// Last update Fri Dec 18 10:41:59 2015 Thibaut Lopez
//

#include <Windows.h>
#include "WTime.hh"

WTime::WTime()
{
}

WTime::~WTime()
{
}

void		WTime::now(std::size_t &sec, std::size_t &usec) const
{
  struct _timeb	timebuffer;

  _ftime (&timebuffer);
  sec = timebuffer.time;
  usec = timebuffer.millitm * 1000;
}

void		WTime::sub(const std::size_t &aSec, const std::size_t &aUsec, const std::size_t &bSec, const std::size_t &bUsec, std::size_t &rSec, std::size_t &rUsec) const
{
  int		usec;

  rSec = aSec - bSec;
  usec = aUsec - bUsec;
  if (usec < 0)
    {
      --rSec;
      usec += 1000000;
    }
  rUsec = usec;
}

void		WTime::Usleep(const std::size_t &usec) const
{
  Sleep(usec / 1000);
}
