//
// LNetwork.cpp for LNetwork in /home/lopez_t/rtype/API/interface
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Thu Nov 19 15:39:16 2015 Thibaut Lopez
// Last update Tue Dec 15 14:53:50 2015 Thibaut Lopez
//

#include "LNetwork.hh"

LNetwork::LNetwork()
{
}

LNetwork::~LNetwork()
{
  std::list<LSocket *>::iterator	it;
  LSocket		*client;

  it = this->_clients.begin();
  while (it != this->_clients.end())
    {
      client = *it;
      it = this->_clients.erase(it);
      delete client;
    }
}

LSocket			*LNetwork::_find()
{
  std::list<LSocket *>::iterator	it;
  LSocket		*client;

  it = this->_clients.begin();
  while (it != this->_clients.end())
    {
      if ((*it)->compare(this->_sin))
	return (*it);
      ++it;
    }
  client = new LSocket(this->_sin);
  this->_handler->handleConnection(client);
  this->_clients.push_back(client);
  return (client);
}

void			LNetwork::_writeLoop()
{
  std::list<LSocket *>::iterator	it;
  LSocket		*client;

  it = this->_clients.begin();
  while (it != this->_clients.end())
    {
      client = *it;
      if (!client->Write(this->_sock))
	{
	  this->_handler->handleDisconnection(client);
	  it = this->_clients.erase(it);
	  delete client;
	}
      else
	++it;
    }
}

void			LNetwork::_updateClients()
{
  std::list<LSocket *>::iterator	it;
  LSocket		*client;

  it = this->_clients.begin();
  while (it != this->_clients.end())
    {
      client = *it;
      if (!client->update())
	{
	  this->_handler->handleDisconnection(client);
	  it = this->_clients.erase(it);
	  delete client;
	}
      else
	++it;
    }
}

bool			LNetwork::_needToWrite()
{
  std::list<LSocket *>::iterator	it;

  it = this->_clients.begin();
  while (it != this->_clients.end())
    {
      if ((*it)->needToWrite())
	return (true);
      ++it;
    }
  return (false);
}

bool			LNetwork::initServer(const uint16_t &port, IHandler *handler)
{
  socklen_t		len;

  this->_port = port;
  this->_handler = handler;
  this->_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (this->_sock == -1)
    throw std::runtime_error("Couldn't create a socket.");
  this->_sin.sin_addr.s_addr = htonl(INADDR_ANY);
  this->_sin.sin_port = htons(port);
  this->_sin.sin_family = AF_INET;
  if (bind(this->_sock, reinterpret_cast<const struct sockaddr *>(&this->_sin), sizeof(this->_sin)) == -1)
    {
      close(this->_sock);
      throw std::runtime_error("Couldn't bind");
    }
  len = sizeof(this->_sin);
  if (this->_port == 0)
    {
      if (getsockname(this->_sock, reinterpret_cast<struct sockaddr *>(&this->_sin), &len) == -1)
	{
	  close(this->_sock);
	  throw std::runtime_error("Couldn't get socket by its name.");
	}
      this->_port = ntohs(this->_sin.sin_port);
    }
  return (true);
}

std::uint16_t		LNetwork::getPort() const
{
  return (this->_port);
}

bool			LNetwork::eraseSocket(ISocket *sock)
{
  std::size_t		size;

  size = this->_clients.size();
  this->_clients.remove(static_cast<LSocket *>(sock));
  return (size != this->_clients.size());
}

void			LNetwork::addTimer(const Timer &timer)
{
  this->_timers.push_back(timer);
}

bool			LNetwork::update()
{
  socklen_t		sinsize;
  long int		size;
  LSocket		*client;
  std::list<Timer>::iterator	it;
  struct timeval	tv;

  sinsize = sizeof(this->_sin);
  FD_ZERO(&this->_rbf);
  FD_ZERO(&this->_wbf);
  FD_SET(this->_sock, &this->_rbf);
  if (this->_needToWrite())
    FD_SET(this->_sock, &this->_wbf);
  tv.tv_sec = 0;
  tv.tv_usec = 10000;
  if (select(this->_sock + 1, &this->_rbf, &this->_wbf, NULL, &tv) != -1)
    {
      if (FD_ISSET(this->_sock, &this->_rbf))
	{
	  size = recvfrom(this->_sock, &this->_packet, PACKET_SIZE, 0, reinterpret_cast<struct sockaddr *>(&this->_sin), &sinsize);
	  if (size == -1)
	    throw std::runtime_error("RecvFrom failed.");
	  if (size == PACKET_SIZE)
	    {
	      client = this->_find();
	      client->put(this->_packet);
	    }
	}
      if (FD_ISSET(this->_sock, &this->_wbf))
	this->_writeLoop();
    }
  else
    throw std::runtime_error("Select failed.");
  this->_updateClients();
  it = this->_timers.begin();
  while (it != this->_timers.end())
    {
      if ((*it).ring())
	it = this->_timers.erase(it);
      else
	++it;
    }
  return (true);
}
