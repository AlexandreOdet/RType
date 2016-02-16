//
// Client.hh for Client in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Wed Nov 25 13:54:10 2015 Thibaut Lopez
// Last update Tue Dec 15 17:22:50 2015 Thibaut Lopez
//

#ifndef	CLIENT_HH
#define	CLIENT_HH

#include <iostream>
#include <string>
#include <list>
#include "ISocket.hh"
#include "Player.hh"
#ifdef	WIN32
#include "WMutex.hh"
#else
#include "LMutex.hh"
#endif

class	Client : public Player, public Mutex
{
private:
  ISocket	*_sock;
  bool		_isOpen;
  int		_roomId;
  Player	_player;
  bool		_isInGame;
  bool    _isReady;
  std::size_t	_sec;
  std::size_t	_usec;


public:
  explicit Client(ISocket *);
  virtual ~Client();

  bool		isIt(ISocket *) const;
  bool		isClosed() const;
  void		close();
  ISocket	*getSocket() const;
  bool		emptySocket();
  bool		enterRoom(const std::size_t &, const std::size_t &);
  bool		leaveRoom();
  const int	&getRoomId() const;
  bool		isInGame() const;
  void		isInGame(const bool &);
  void		updateTimer();
  bool		isRecentlyUpdated();
  void    setStatus(const bool &);
  const bool & getStatus() const;
};

#endif
