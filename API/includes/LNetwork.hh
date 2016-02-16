//
// LNetwork.hh for LNetwork in /home/lopez_t/rtype/API/interface
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Thu Nov 19 15:38:19 2015 Thibaut Lopez
// Last update Tue Dec 15 14:34:19 2015 Thibaut Lopez
//

#ifndef	LNETWORK_HH
#define	LNETWORK_HH

#include "INetwork.hh"
#include "LSocket.hh"

class	LNetwork : public INetwork
{
private:
  IHandler		*_handler;
  int			_sock;
  std::uint16_t		_port;
  struct sockaddr_in	_sin;
  fd_set		_rbf;
  fd_set		_wbf;
  std::list<LSocket *>	_clients;
  t_pkt			_packet;
  std::list<Timer>	_timers;

  LSocket		*_find();
  void			_writeLoop();
  bool			_needToWrite();
  void			_updateClients();

public:
  explicit LNetwork();
  virtual ~LNetwork();

  bool			initServer(const uint16_t &, IHandler *);
  std::uint16_t		getPort() const;
  bool			eraseSocket(ISocket *);
  void			addTimer(const Timer &);
  bool			update();
};

#endif
