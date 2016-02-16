//
// Server.hh for Server in /home/lopez_t/rtype/server/includes
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Nov 24 15:03:55 2015 Thibaut Lopez
// Last update Sat Jan  2 15:07:53 2016 Thibaut Lopez
//

#ifndef	SERVER_HH
#define	SERVER_HH

#include <iostream>
#include <string>
#include <map>
#include "ThreadPool.hpp"
#include "Room.hh"
#ifdef	WIN32
#include "WNetwork.hh"
#else
#include "LNetwork.hh"
#endif

class	Server : public IHandler, public IClock
{
private:
  INetwork		*_network;
  std::list<Client *>	_clients;
  std::list<Room *>	_rooms;
  typedef bool		(Server::*s_func)(const t_pkt &, Client *);
  std::map<int, s_func>	_commands;
  ThreadPool  _threadPool;

  Room			*_createRoom();
  Room			*_findRoom(const std::size_t &);

  bool			_hello(const t_pkt &, Client *);
  bool			_disconnect(const t_pkt &, Client *);

  bool			_joinRoom(const t_pkt &, Client *);
  bool			_leaveRoom(const t_pkt &, Client *);
  bool			_createRoom(const t_pkt &, Client *);
  bool			_setReady(const t_pkt &, Client *);

  bool			_cnf(const t_pkt &, Client *);

  void			_roomList();
  void			_eraseUselessRooms();

public:
  Server();
  virtual ~Server();

  void			handleConnection(ISocket *);
  void			handleDisconnection(ISocket *);
  void			ring();
  bool			initServer(const std::uint16_t &);
  std::uint16_t		getPort() const;
  void			run();

  static void			    _sendToNetwork(Client *, std::size_t, std::string const &);
  static std::string   itos(int const);
  static int			      ctos(std::string const &);
};

#endif
