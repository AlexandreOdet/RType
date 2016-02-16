#ifndef	WSOCKET_HH
#define	WSOCKET_HH

typedef	struct sockaddr_in s_sin;

#include <winsock.h>
#include <stdio.h>
#include <stdlib.h> 
#include <queue>
#include "ISocket.hh"
#include "STTime.hh"

class	WSocket : public ISocket
{
private:
	struct sockaddr_in	_sin;
  std::queue<t_pkt>	_in;
  std::queue<t_pkt>	_out;
  ReliabilitySystem	_rSys;
  FlowControl		_fCon;
  std::size_t		_timeOutSec;
  std::size_t		_timeOutUsec;
  float			_deltaTime;
  std::size_t		_deltaSec;
  std::size_t		_deltaUsec;

public:
  WSocket();
  WSocket(const s_sin &);
  virtual ~WSocket();
  const s_sin		&sin() const;
  void			sin(const s_sin &);
  bool			compare(const s_sin &) const;
  bool			needToWrite() const;
  bool			Write(const int &);
  void			put(const t_pkt &);
  bool			receive(t_pkt &);
  void			Send(const t_pkt &);
  void			printStats() const;
  bool			update();
  int			getTimeElapsed() const;
};

#endif
