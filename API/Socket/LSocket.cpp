//
// LSocket.cpp for LSocket in /home/lopez_t/rtype/API
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Mon Nov 23 13:21:20 2015 Thibaut Lopez
// Last update Thu Dec 10 15:11:07 2015 Thibaut Lopez
//

#include "LSocket.hh"

LSocket::LSocket()
{
  memset(&this->_sin, 0, sizeof(this->_sin));
  this->_sin.sin_family = AF_INET;
  this->_sin.sin_addr.s_addr = 0;
  this->_sin.sin_port = 0;
  (STTime::getInstance())->now(this->_timeOutSec, this->_timeOutUsec);
  this->_deltaTime = 0.0f;
  this->_deltaSec = this->_timeOutSec;
  this->_deltaUsec = this->_timeOutUsec;
}

LSocket::LSocket(const s_sin &sin)
{
  memset(&this->_sin, 0, sizeof(this->_sin));
  this->_sin.sin_family = AF_INET;
  this->_sin.sin_addr.s_addr = sin.sin_addr.s_addr;
  this->_sin.sin_port = sin.sin_port;
  (STTime::getInstance())->now(this->_timeOutSec, this->_timeOutUsec);
  this->_deltaTime = 0.0f;
  this->_deltaSec = this->_timeOutSec;
  this->_deltaUsec = this->_timeOutUsec;
}

LSocket::~LSocket()
{
}

const s_sin		&LSocket::sin() const
{
  return (this->_sin);
}

void			LSocket::sin(const s_sin &sin)
{
  this->_sin.sin_addr.s_addr = sin.sin_addr.s_addr;
  this->_sin.sin_port = sin.sin_port;
}

bool			LSocket::compare(const s_sin &sin) const
{
  return (this->_sin.sin_addr.s_addr == sin.sin_addr.s_addr &&
	  this->_sin.sin_port == sin.sin_port);
}

bool			LSocket::needToWrite() const
{
  return (this->_out.size() > 0);
}

bool			LSocket::Write(const int &sock)
{
  t_pkt			packet;
  float			sendRate;

  sendRate = this->_fCon.getSendRate();
  while (this->_deltaTime > 1.0f / sendRate)
    {
      if (this->_out.size() == 0)
	     return (true);
      packet = this->_out.front();
      this->_out.pop();
      packet.magicNbr = MAGIC_NBR;
      packet.seq = this->_rSys.getLocalSeq();
      packet.ack = this->_rSys.getRemoteSeq();
      packet.ackBF = this->_rSys.generateAckBF();
      #ifdef __APPLE__
      if (sendto(sock, &packet, PACKET_SIZE, 0, reinterpret_cast<const struct sockaddr *>(&this->_sin), sizeof(this->_sin)) == -1)
      #else
      if (sendto(sock, &packet, PACKET_SIZE, MSG_NOSIGNAL, reinterpret_cast<const struct sockaddr *>(&this->_sin), sizeof(this->_sin)) == -1)
      #endif
        return (false);
      this->_rSys.sent();
      this->_deltaTime -= 1.0f / sendRate;
    }
  return (true);
}

void			LSocket::put(const t_pkt &packet)
{
  if (packet.magicNbr != MAGIC_NBR)
    return ;
  this->_rSys.received(packet.seq);
  this->_rSys.processAck(packet.ack, packet.ackBF);
  this->_in.push(packet);
  (STTime::getInstance())->now(this->_timeOutSec, this->_timeOutUsec);
}

bool			LSocket::receive(t_pkt &packet)
{
  if (this->_in.size() == 0)
    return (false);
  packet = this->_in.front();
  this->_in.pop();
  return (true);
}

void			LSocket::Send(const t_pkt &packet)
{
  this->_out.push(packet);
}

void			LSocket::printStats() const
{
  std::size_t		sentPkts;
  std::size_t		lostPkts;
  float			lostPercent;

  sentPkts = this->_rSys.getSentPkts();
  lostPkts = this->_rSys.getLostPkts();
  lostPercent = sentPkts > 0 ? static_cast<float>(lostPkts) / static_cast<float>(sentPkts) * 100.0f : 0.0f;
  std::cout << "rtt " << this->_rSys.getRoundTripTime() * 1000.0f << "ms";
  std::cout << ", sent " << sentPkts;
  std::cout << ", acked " << this->_rSys.getAckedPkts();
  std::cout << ", lost " << lostPkts << " (" << lostPercent << "%)";
  std::cout << ", sent bandwidth = " << this->_rSys.getSentBandwidth() << "kbps";
  std::cout << ", acked bandwidth = "<< this->_rSys.getAckedBandwidth() << "kbps" << std::endl;
}

bool			LSocket::update()
{
  std::size_t		nSec;
  std::size_t		nUsec;
  std::size_t		tmpSec;
  std::size_t		tmpUsec;

  (STTime::getInstance())->now(nSec, nUsec);
  (STTime::getInstance())->sub(nSec, nUsec, this->_timeOutSec, this->_timeOutUsec, tmpSec, tmpUsec);
  if (tmpSec >= 5)
    return (false);
  (STTime::getInstance())->sub(nSec, nUsec, this->_deltaSec, this->_deltaUsec, tmpSec, tmpUsec);
  this->_deltaTime += tmpSec;
  this->_deltaTime += static_cast<float>(tmpUsec) / 1000000.0f;
  this->_rSys.update();
  this->_fCon.update(this->_rSys.getRoundTripTime() * 1000.0f);
  return (true);
}
