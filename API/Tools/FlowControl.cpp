//
// FlowControl.cpp for FlowControl in /home/lopez_t/rtype/API
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Tue Dec  1 14:36:15 2015 Thibaut Lopez
// Last update Tue Dec  1 19:10:50 2015 Thibaut Lopez
//

#include "FlowControl.hh"

FlowControl::FlowControl()
  : _rttThreshold(250.0f)
{
  this->reset();
}

FlowControl::~FlowControl()
{
}

void		FlowControl::_goodUpdate(const float &time, const float &rtt)
{
  if (rtt > this->_rttThreshold)
    {
      std::cout << "*** dropping to bad mode ***" << std::endl;
      this->_mode = BAD;
      this->_sendRate = 10.0f;
      if (this->_goodTime < 10.0f && this->_penalty < 60.0f)
	{
	  this->_penalty *= 2.0f;
	  if (this->_penalty > 60.0f)
	    this->_penalty = 60.0f;
	  std::cout << "penalty time increased to " << this->_penalty << std::endl;
	}
      this->_goodTime = 0.0f;
      this->_penaltyAcc = 0.0f;
      return;
    }
  this->_goodTime += time;
  this->_penaltyAcc += time;
  if (this->_penaltyAcc > 10.0f && this->_penalty > 1.0f)
    {
      this->_penalty /= 2.0f;
      if (this->_penalty < 1.0f)
	this->_penalty = 1.0f;
      std::cout <<  "penalty time reduced to " << this->_penalty << std::endl;
      this->_penaltyAcc = 0.0f;
    }
}

void		FlowControl::_badUpdate(const float &time, const float &rtt)
{
  if (rtt <= this->_rttThreshold)
    this->_goodTime += time;
  else
    this->_goodTime = 0.0f;
  if (this->_goodTime > this->_penalty)
    {
      std::cout << "*** upgrading to good mode ***" << std::endl;
      this->_goodTime = 0.0f;
      this->_penaltyAcc = 0.0f;
      this->_mode = GOOD;
      this->_sendRate = 30.0f;
      return;
    }
}

void		FlowControl::reset()
{
  this->_mode = BAD;
  this->_penalty = 4.0f;
  this->_goodTime = 0.0f;
  this->_penaltyAcc = 0.0f;
  this->_sendRate = 10.0f;
  (STTime::getInstance())->now(this->_sec, this->_usec);
}

void		FlowControl::update(const float &rtt)
{
  std::size_t	nSec;
  std::size_t	nUsec;
  std::size_t	tmpSec;
  std::size_t	tmpUsec;
  float		time;

  (STTime::getInstance())->now(nSec, nUsec);
  (STTime::getInstance())->sub(nSec, nUsec, this->_sec, this->_usec, tmpSec, tmpUsec);
  time = tmpSec;
  time += static_cast<float>(tmpUsec) / 1000000.0f;
  if (this->_mode == GOOD)
    this->_goodUpdate(time, rtt);
  else
    this->_badUpdate(time, rtt);
  this->_sec = nSec;
  this->_usec = nUsec;
}

const float	&FlowControl::getSendRate() const
{
  return (this->_sendRate);
}
