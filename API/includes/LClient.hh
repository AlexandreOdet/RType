//
// LClient.hh for LClient in /home/lopez_t/rtype/API/interface
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Thu Nov 19 15:38:19 2015 Thibaut Lopez
// Last update Thu Dec  3 13:10:17 2015 Thibaut Lopez
//

#ifndef	LCLIENT_HH
#define	LCLIENT_HH

#include "IClient.hh"
#include "LSocket.hh"

class	LClient : public IClient
{
private:
  int			_sock;
  std::string		_ip;
  std::uint16_t		_port;
  struct sockaddr_in	_sin;
  fd_set		_rbf;
  fd_set		_wbf;
  LSocket		*_server;
  t_pkt			_packet;
  std::list<Timer>	_timers;

public:
  explicit LClient();
  virtual ~LClient();

  bool			initClient(const std::string &, const uint16_t &);
  const std::string	&getIP() const;
  std::uint16_t		getPort() const;
  ISocket		*getSocket() const;
  void			addTimer(const Timer &);
  bool			update();
};

#endif
