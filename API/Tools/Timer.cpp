//
// Timer.cpp for Timer in /home/lopez_t/rtype/server
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Mon Nov 23 17:31:10 2015 Thibaut Lopez
// Last update Tue Dec  1 19:07:06 2015 Thibaut Lopez
//

#include "Timer.hh"

Timer::Timer()
  : _sec(0), _usec(0), _clock(NULL)
{
}

Timer::Timer(const std::size_t &sec, const std::size_t &usec)
  : _sec(sec), _usec(usec), _clock(NULL)
{
}

Timer::Timer(Timer const &cpy)
  : _sec(cpy.sec()), _usec(cpy.usec()), _clock(cpy.clock())
{
}

Timer::~Timer()
{
}

Timer const		&Timer::operator=(Timer const &cpy)
{
  if (&cpy != this)
    {
      this->sec(cpy.sec());
      this->usec(cpy.usec());
      this->clock(cpy.clock());
    }
  return (*this);
}

void			Timer::clock(IClock *clock)
{
  this->_clock = clock;
}

IClock			*Timer::clock() const
{
  return (this->_clock);
}

void			Timer::setDeadline(const std::size_t &sec, const std::size_t &usec)
{
  (STTime::getInstance())->now(this->_sec, this->_usec);
  this->_sec += sec;
  this->_usec += usec;
  this->_sec += this->_usec / 1000000;
  this->_usec = this->_usec % 1000000;
}

void			Timer::sec(const std::size_t &sec)
{
  this->_sec = sec;
}

const std::size_t	&Timer::sec() const
{
  return (this->_sec);
}

void			Timer::usec(const std::size_t &usec)
{
  this->_usec = usec;
}

const std::size_t	&Timer::usec() const
{
  return (this->_usec);
}

bool			Timer::ring()
{
  std::size_t		sec;
  std::size_t		usec;

  (STTime::getInstance())->now(sec, usec);
  if (sec > this->_sec || (sec == this->_sec && usec > this->_usec))
    {
      this->_clock->ring();
      return (true);
    }
  return (false);
}
