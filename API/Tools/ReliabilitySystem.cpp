//
// ReliabilitySystem.cpp for ReliabilitySystem in /home/lopez_t/rtype/API
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Mon Nov 30 15:33:36 2015 Thibaut Lopez
// Last update Thu Dec  3 11:32:59 2015 Thibaut Lopez
//

#include "ReliabilitySystem.hh"

ReliabilitySystem::ReliabilitySystem()
{
  this->reset();
}

float			ReliabilitySystem::_getTime(const std::size_t &sec, const std::size_t &usec) const
{
  std::size_t		nSec;
  std::size_t		nUsec;
  std::size_t		tmpSec;
  std::size_t		tmpUsec;
  float			time;

  (STTime::getInstance())->now(nSec, nUsec);
  (STTime::getInstance())->sub(nSec, nUsec, sec, usec, tmpSec, tmpUsec);
  time = tmpSec;
  time += static_cast<float>(tmpUsec) / 1000000.0f;
  return (time);
}

int			ReliabilitySystem::_indexForSeq(const std::size_t &seq, const std::size_t &ack) const
{
  if (seq > ack)
    return (ack + (0xFFFFFFFF - seq));
  else
    return (ack - 1 - seq);
}

void			ReliabilitySystem::_updateQueues()
{
  std::size_t		latestSeq;
  std::size_t		minSeq;

  while (this->_sent.size() && this->_getTime(this->_sent.front().sec, this->_sent.front().usec) > this->_rttMax + EPSILON)
    this->_sent.pop_front();
  if (this->_recved.size())
    {
      latestSeq = this->_recved.back().seq;
      minSeq = (latestSeq > 34) ? latestSeq - 34 : 0;
      while (this->_recved.size() && this->_recved.front().seq < minSeq)
	this->_recved.pop_front();
    }
  while (this->_acked.size() && this->_getTime(this->_acked.front().sec, this->_acked.front().usec) > this->_rttMax * 2 - EPSILON)
    this->_acked.pop_front();
  while (this->_pAck.size() && this->_getTime(this->_pAck.front().sec, this->_pAck.front().usec) > this->_rttMax + EPSILON)
    {
      this->_pAck.pop_front();
      this->_lostPkts++;
    }
}

void			ReliabilitySystem::_updateStats()
{
  int			sentBPS;
  int			ackedBPS;
  PacketQueue::iterator it;

  sentBPS = 0;
  ackedBPS = 0;
  it = this->_sent.begin();
  while (it != this->_sent.end())
    {
      sentBPS += 256;
      ++it;
    }
  it = this->_acked.begin();
  while (it != this->_acked.end())
    {
      if (this->_getTime(it->sec, it->usec) >= this->_rttMax)
	ackedBPS += 256;
      ++it;
    }
  sentBPS /= this->_rttMax;
  ackedBPS /= this->_rttMax;
  this->_sentBandwidth = sentBPS * (8 / 1000.0f);
  this->_ackedBandwidth = ackedBPS * (8 / 1000.0f);
}

void			ReliabilitySystem::reset()
{
  this->_localSeq = 0;
  this->_remoteSeq = 0;
  this->_sent.clear();
  this->_recved.clear();
  this->_pAck.clear();
  this->_acked.clear();
  this->_sentPkts = 0;
  this->_recvPkts = 0;
  this->_lostPkts = 0;
  this->_ackedPkts = 0;
  this->_sentBandwidth = 0.0f;
  this->_ackedBandwidth = 0.0f;
  this->_rtt = 0.0f;
  this->_rttMax = 1.0f;
}

void			ReliabilitySystem::sent()
{
  PacketQueue::iterator	it;
  t_pkt_data		data;

  if (this->_sent.exists(this->_localSeq))
    {
      std::cout << "local sequence " << this->_localSeq << " exists" << std::endl;
      for (it = this->_sent.begin(); it != this->_sent.end(); ++it)
	std::cout << " + " << (*it).seq << std::endl;
    }
  data.seq = this->_localSeq;
  (STTime::getInstance())->now(data.sec, data.usec);
  this->_sent.push_back(data);
  this->_pAck.push_back(data);
  this->_sentPkts++;
  this->_localSeq++;
}

void			ReliabilitySystem::received(const std::size_t &seq)
{
  t_pkt_data		data;

  this->_recvPkts++;
  if (this->_recved.exists(seq))
    return;
  data.seq = seq;
  (STTime::getInstance())->now(data.sec, data.usec);
  this->_recved.push_back(data);
  if (seq > this->_remoteSeq)
    this->_remoteSeq = seq;
}

std::size_t		ReliabilitySystem::generateAckBF() const
{
  std::size_t		ackBF;
  PacketQueue::const_iterator	it;
  int			bitIndex;

  ackBF = 0;
  it = this->_recved.begin();
  while (it != this->_recved.end())
    {
      if (it->seq >= this->_remoteSeq)
	return (ackBF);
      bitIndex = this->_indexForSeq(it->seq, this->_remoteSeq);
      if (bitIndex <= 31)
	ackBF |= 1 << bitIndex;
      ++it;
    }
  return (ackBF);
}

void			ReliabilitySystem::processAck(const std::size_t &ack, const std::size_t &ackBF)
{
  PacketQueue::iterator it;
  bool		isAcked;
  int		bitIndex;

  if (this->_pAck.empty())
    return;
  it = this->_pAck.begin();
  while (it != this->_pAck.end())
    {
      isAcked = false;
      if (it->seq == ack)
	isAcked = true;
      else if (it->seq < ack)
	{
	  bitIndex = this->_indexForSeq( it->seq, ack);
	  if (bitIndex <= 31)
	    isAcked = (ackBF >> bitIndex) & 1;
	}
      if (isAcked)
	{
	  this->_rtt += (this->_getTime(it->sec, it->usec) - this->_rtt) * 0.1f;
	  this->_acked.insertSorted(*it);
	  this->_acks.push_back(it->seq);
	  this->_ackedPkts++;
	  it = this->_pAck.erase(it);
	}
      else
	++it;
    }
}

void		ReliabilitySystem::update()
{
  this->_acks.clear();
  this->_updateQueues();
  this->_updateStats();
}

std::size_t	ReliabilitySystem::getLocalSeq() const
{
  return (this->_localSeq);
}

std::size_t	ReliabilitySystem::getRemoteSeq() const
{
  return (this->_remoteSeq);
}

std::size_t	ReliabilitySystem::getSentPkts() const
{
  return (this->_sentPkts);
}

std::size_t	ReliabilitySystem::getReceivedPkts() const
{
  return (this->_recvPkts);
}

std::size_t	ReliabilitySystem::getLostPkts() const
{
  return (this->_lostPkts);
}

std::size_t	ReliabilitySystem::getAckedPkts() const
{
  return (this->_ackedPkts);
}

float		ReliabilitySystem::getSentBandwidth() const
{
  return (this->_sentBandwidth);
}

float		ReliabilitySystem::getAckedBandwidth() const
{
  return (this->_ackedBandwidth);
}

float		ReliabilitySystem::getRoundTripTime() const
{
  return (this->_rtt);
}
