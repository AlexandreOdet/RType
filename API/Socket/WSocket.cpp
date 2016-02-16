#include "WSocket.hh"

typedef	struct sockaddr_in s_sin;

WSocket::WSocket()
{
  this->_sin.sin_family = AF_INET;
  this->_sin.sin_addr.s_addr = 0;
  this->_sin.sin_port = 0;
  (STTime::getInstance())->now(this->_timeOutSec, this->_timeOutUsec);
  this->_deltaTime = 0.0f;
  this->_deltaSec = this->_timeOutSec;
  this->_deltaUsec = this->_timeOutUsec;
}

WSocket::WSocket(const s_sin &sin)
{
  this->_sin.sin_family = AF_INET;
  this->_sin.sin_addr.s_addr = sin.sin_addr.s_addr;
  this->_sin.sin_port = sin.sin_port;
  (STTime::getInstance())->now(this->_timeOutSec, this->_timeOutUsec);
  this->_deltaTime = 0.0f;
  this->_deltaSec = this->_timeOutSec;
  this->_deltaUsec = this->_timeOutUsec;
}

WSocket::~WSocket()
{
}

const s_sin		&WSocket::sin() const
{
  return (this->_sin);
}

void			WSocket::sin(const s_sin &sin)
{
  this->lock();
  this->_sin.sin_addr.s_addr = sin.sin_addr.s_addr;
  this->_sin.sin_port = sin.sin_port;
  this->unlock();
}

bool			WSocket::compare(const s_sin &sin) const
{
  return (this->_sin.sin_addr.s_addr == sin.sin_addr.s_addr &&
	  this->_sin.sin_port == sin.sin_port);
}

bool			WSocket::needToWrite() const
{
  return (this->_out.size() > 0);
}

bool			WSocket::Write(const int &sock)
{
  t_pkt			packet;
  float			sendRate;

  this->lock();
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
      if (sendto(sock, reinterpret_cast<char*>(&packet), PACKET_SIZE, 0, reinterpret_cast<const struct sockaddr *>(&this->_sin), sizeof(this->_sin)) == -1)
	return (false);
      this->_rSys.sent();
      this->_deltaTime -= 1.0f / sendRate;
    }
  this->unlock();
  return (true);
}

void			WSocket::put(const t_pkt &packet)
{
  if (packet.magicNbr != MAGIC_NBR)
    return ;
  this->lock();
  this->_rSys.received(packet.seq);
  this->_rSys.processAck(packet.ack, packet.ackBF);
  this->_in.push(packet);
  (STTime::getInstance())->now(this->_timeOutSec, this->_timeOutUsec);
  this->unlock();
}

bool			WSocket::receive(t_pkt &packet)
{
  if (this->_in.size() == 0)
    return (false);
  this->lock();
  packet = this->_in.front();
  this->_in.pop();
  this->unlock();
  return (true);
}

void			WSocket::Send(const t_pkt &packet)
{
  this->lock();
  this->_out.push(packet);
  this->unlock();
}

void			WSocket::printStats() const
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

int       WSocket::getTimeElapsed() const
{
  std::size_t		nSec;
  std::size_t		nUsec;
  std::size_t		tmpSec;
  std::size_t		tmpUsec;

  (STTime::getInstance())->now(nSec, nUsec);
  (STTime::getInstance())->sub(nSec, nUsec, this->_timeOutSec, this->_timeOutUsec, tmpSec, tmpUsec);
  return (tmpSec);
}

bool			WSocket::update()
{
  std::size_t		nSec;
  std::size_t		nUsec;
  std::size_t		tmpSec;
  std::size_t		tmpUsec;

  this->lock();
  (STTime::getInstance())->now(nSec, nUsec);
  (STTime::getInstance())->sub(nSec, nUsec, this->_timeOutSec, this->_timeOutUsec, tmpSec, tmpUsec);
  if (tmpSec >= 5)
    {
      this->unlock();
      return (false);
    }
  (STTime::getInstance())->sub(nSec, nUsec, this->_deltaSec, this->_deltaUsec, tmpSec, tmpUsec);
  this->_deltaTime += tmpSec;
  this->_deltaTime += static_cast<float>(tmpUsec) / 1000000.0f;
  this->_rSys.update();
  this->_fCon.update(this->_rSys.getRoundTripTime() * 1000.0f);
  this->unlock();
  return (true);
}
