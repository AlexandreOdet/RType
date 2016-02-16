#ifndef _WNetwork_
#define _WNetwork_


#include <winsock.h>

#include "INetwork.hh"
#include "INetwork.hh"
#include "WSocket.hh"

class WNetwork : public INetwork
{
public:
  explicit WNetwork();
  virtual ~WNetwork();

  bool			initServer(const uint16_t &, IHandler *);
  std::uint16_t		getPort() const;
  bool			eraseSocket(ISocket *);
  void			addTimer(const Timer &);
  bool			update();

  WSocket		*_find();
  void			_writeLoop();
  bool			_needToWrite();
  void			_updateClients();


private:
  IHandler		*_handler;
  int			_sock;
  std::uint16_t		_port;
  struct sockaddr_in	_sin;
  fd_set		_rbf;
  fd_set		_wbf;
  std::list<WSocket *>	_clients;
  t_pkt			_packet;
  std::list<Timer>	_timers;
};

#endif /*_WNetwork_*/
