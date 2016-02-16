//
// LSocket.hh for LSocket in /home/lopez_t/rtype/API
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Mon Nov 23 13:21:16 2015 Thibaut Lopez
// Last update Thu Dec 10 15:12:35 2015 Thibaut Lopez
//

#ifndef	LSOCKET_HH
#define	LSOCKET_HH

typedef	struct sockaddr_in s_sin;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <queue>
#include "ISocket.hh"
#include "STTime.hh"

class	LSocket : public ISocket
{
private:
  s_sin			_sin;
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
  LSocket();
  LSocket(const s_sin &);
  virtual ~LSocket();
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
};

#endif
