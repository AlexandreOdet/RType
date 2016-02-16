//
// Client.cpp for Client in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Wed Nov 25 13:54:10 2015 Thibaut Lopez
// Last update Sun Dec 13 14:36:19 2015 Thibaut Lopez
//

#include "Client.hh"

Client::Client(ISocket *sock)
  : _sock(sock), _isOpen(true), _roomId(-1), _isInGame(false), _isReady(false)
{
}

Client::~Client()
{
}

void		Client::updateTimer()
{
  (STTime::getInstance())->now(_sec, _usec);
}

bool		Client::isRecentlyUpdated()
{
  std::size_t	tmpSec = 0;
  std::size_t	tmpUsec = 0;

  (STTime::getInstance())->now(tmpSec, tmpUsec);
  if (_sec + 2 >= tmpSec)
    return true;
  else
    return false;
}

bool		Client::isIt(ISocket *sock) const
{
  return (this->_isOpen && sock == this->_sock);
}

bool		Client::isClosed() const
{
  return (!this->_isOpen);
}

void		Client::close()
{
  this->_isOpen = false;
}

ISocket		*Client::getSocket() const
{
  return (this->_sock);
}

bool		Client::emptySocket()
{
  if (this->_sock == NULL)
    return (false);
  this->_sock = NULL;
  return (true);
}

bool		Client::enterRoom(const std::size_t &roomId, const std::size_t &id)
{
  if (this->_roomId != -1)
    return (false);
  this->_roomId = roomId;
  this->_player.id(id);
  return (true);
}

bool		Client::leaveRoom()
{
  if (this->_roomId == -1)
    return (false);
  this->_roomId = -1;
  this->_player.id(-1);
  return (true);
}

const int	&Client::getRoomId() const
{
  return (this->_roomId);
}

bool		Client::isInGame() const
{
  return (this->_isInGame);
}

void		Client::isInGame(const bool &isInGame)
{
  this->_isInGame = isInGame;
}

void    Client::setStatus(const bool & isReady)
{
  this->_isReady = isReady;
}

const bool & Client::getStatus() const
{
  return this->_isReady;
}
