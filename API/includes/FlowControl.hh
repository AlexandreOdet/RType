//
// FlowControl.hh for FlowControl in /home/lopez_t/rtype/API
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec  1 14:36:21 2015 Thibaut Lopez
// Last update Tue Dec  1 19:11:38 2015 Thibaut Lopez
//

#ifndef FLOWCONTROL_HH
#define FLOWCONTROL_HH

#include <iostream>
#include <string>
#include "STTime.hh"

class FlowControl
{
private:
  enum eMode
    {
      GOOD,
      BAD
    };
  eMode		_mode;
  float		_penalty;
  float		_goodTime;
  float		_penaltyAcc;
  float		_sendRate;
  float		_rttThreshold;
  std::size_t	_sec;
  std::size_t	_usec;
  void		_goodUpdate(const float &, const float &);
  void		_badUpdate(const float &, const float &);

public:
  FlowControl();
  ~FlowControl();
  void		reset();
  void		update(const float &);
  const float	&getSendRate() const;
};

#endif
