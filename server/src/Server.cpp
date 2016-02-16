//
// Server.cpp for Server in /home/lopez_t/rtype/server/src
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Nov 24 15:03:55 2015 Thibaut Lopez
// Last update Sat Jan  2 19:11:15 2016 Thibaut Lopez
//

#include "Server.hh"

Server::Server()
{
#ifdef	WIN32
  this->_network = new WNetwork();
#else
  this->_network = new LNetwork();
#endif

  this->_commands[0] = &Server::_hello;
  this->_commands[1] = &Server::_disconnect;
  this->_commands[2] = &Server::_createRoom;
  this->_commands[3] = &Server::_joinRoom;
  this->_commands[4] = &Server::_leaveRoom;
  this->_commands[6] = &Server::_setReady;
}

Server::~Server()
{
}

Room			*Server::_createRoom()
{
  Room			*room;
  std::size_t		id;
  std::list<Room *>::iterator	it;

  id = 0;
  it = this->_rooms.begin();
  while (it != this->_rooms.end())
    {
      if ((*it)->getId() == id)
	{
	  id++;
	  it = this->_rooms.begin();
	}
      else
	++it;
    }
  room = new Room(id);
  this->_rooms.push_back(room);
  return (room);
}

Room			*Server::_findRoom(const std::size_t &idRoom)
{
  std::list<Room *>::iterator	it;

  it = this->_rooms.begin();
  while (it != this->_rooms.end())
    {
      if ((*it)->getId() == idRoom)
	return (*it);
      ++it;
    }
  return (NULL);
}

bool			Server::_hello(const t_pkt &packet, Client *client)
{
  (void)packet;
  _sendToNetwork(client, 0, "");
  this->_roomList();
  return (true);
}

bool      Server::_disconnect(const t_pkt &packet, Client *client)
{
  (void)packet;
  (void)client;
  return false;
}

bool			Server::_joinRoom(const t_pkt &packet, Client *client)
{
  for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); it ++)
  {
    if ((*it)->getId() == static_cast<std::size_t>(ctos(std::string(packet.args, packet.argLength))))
    {
      (*it)->addPlayer(client);
      this->_roomList();
      break;
    }
  }
  return true;
}

bool			Server::_leaveRoom(const t_pkt &packet, Client *client)
{
  for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); it ++)
  {
    if ((*it)->getId() == static_cast<std::size_t>(ctos(std::string(packet.args, packet.argLength))))
    {
      (*it)->deletePlayer(client);
      this->_roomList();
      break;
    }
  }
  return true;
  (void)client;
}

bool			Server::_createRoom(const t_pkt &packet, Client *client)
{
  Room			*room;

  for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); it ++)
  {
    if ((*it)->getPlayersNumber() == 0)
      {
        (*it)->addPlayer(client);
        this->_roomList();
        return true;
      }
  }

  room = this->_createRoom();
  room->addPlayer(client);
  this->_roomList();
  (void)packet;
  return true;
}

void      *launchThread(void *data)
{
  SafeData  *sfdata = static_cast<SafeData*>(data);
  Room      *room = static_cast<Room*>((*sfdata).data);

  room->loop();
  return NULL;
}

bool      Server::_setReady(const t_pkt &packet, Client *client)
{
  int status = ctos(std::string(packet.args, packet.argLength).substr(4, 4));
  client->setStatus(static_cast<bool>(status));
  std::size_t NbPlayerReady = 0;

  for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); it ++)
  {
    if ((*it)->getId() == static_cast<std::size_t>(ctos(std::string(packet.args, 4))))
    {
      std::list<Client *> tmp = (*it)->getPlayers();
      for (std::list<Client*>::iterator _it = tmp.begin(); _it != tmp.end(); ++_it)
      {
        if ((*_it)->getStatus() == true)
          NbPlayerReady++;
        if (NbPlayerReady == (*it)->getPlayersNumber())
        {
          this->_threadPool.addRoom(&launchThread, (*it));
          it = _rooms.erase(it);
        }
      }
      this->_roomList();
      break;
    }
  }
  return true;
}

bool			Server::_cnf(const t_pkt &packet, Client *client)
{
  (void)packet;
  (void)client;
  return (true);
}

void      Server::_roomList()
{
  for (std::list<Client *>::iterator clients = _clients.begin(); clients != this->_clients.end(); ++clients)
  {
    std::size_t NbPlayerReady = 0;
    for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); it ++)
    {
      std::string toSend = itos((*it)->getId());
      toSend += itos((*it)->getPlayersNumber());
      std::list<Client *> tmp = (*it)->getPlayers();
      for (std::list<Client*>::iterator _it = tmp.begin(); _it != tmp.end(); ++_it)
        {
          if ((*_it)->getStatus() == true)
            NbPlayerReady++;
        }
      toSend += itos(NbPlayerReady);
      _sendToNetwork(*clients, 14, toSend);
    }
  }
}

void	Server::_eraseUselessRooms()
{
  for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end();)
    {
      if ((*it)->needToBeFreed())
	it = _rooms.erase(it);
      else
	++it;
    }
}

void      Server::_sendToNetwork(Client *client, std::size_t cmd, std::string const &args)
{
  t_pkt pkt;

  if (client->getSocket() == NULL)
    return ;
  pkt.key = cmd;
  pkt.argLength = args.size();
  memcpy(pkt.args, args.c_str(), args.size());
  client->updateTimer();
  client->getSocket()->Send(pkt);
}

std::string  Server::itos(int const args)
{
  return std::string((char *)&args, sizeof(int));
}

int   Server::ctos(std::string const &arg)
{
  int *lol = reinterpret_cast<int*>((unsigned char*)arg.c_str());
  return (lol[0]);
}

void			Server::handleConnection(ISocket *sock)
{
  std::list<Client *>::iterator	it;
  Client		*clt;

  it = this->_clients.begin();
  while (it != this->_clients.end())
    {
      if ((*it)->isIt(sock))
	return ;
      ++it;
    }
  clt = new Client(sock);
  this->_clients.push_back(clt);
}

void			Server::handleDisconnection(ISocket *sock)
{
  std::list<Client *>::iterator	it;
  Client		*clt;
  Room			*room;

  it = this->_clients.begin();
  while (it != this->_clients.end())
    {
      clt = *it;
      if (clt->isIt(sock))
	{
	  if (!clt->isInGame())
	    {
	      room = this->_findRoom(clt->getRoomId());
	      if (room != NULL)
		room->deletePlayer(clt);
	      delete clt;
	      it = this->_clients.erase(it);
	    }
	  else
	    {
	      clt->lock();
	      clt->close();
	      clt->emptySocket();
	      clt->unlock();
	      ++it;
	    }
	}
      else
	++it;
    }
}

void			Server::ring()
{
  std::cout << "DRIIIIIINNGGG" << std::endl;
}

bool			Server::initServer(const std::uint16_t &port)
{
  return (this->_network->initServer(port, this));
}

std::uint16_t		Server::getPort() const
{
  return (this->_network->getPort());
}

void			Server::run()
{
  t_pkt			packet;
  std::list<Client *>::iterator	it;
  bool			exist;

  while (this->_network->update())
    {
      it = this->_clients.begin();
      while (it != this->_clients.end())
	{
	  exist = true;
	  if (!(*it)->isInGame() &&
        (*it)->getSocket() != NULL &&
        (*it)->getSocket()->receive(packet))
	    {
	      if (packet.key != 128)
		{
		  try
		    {
		      exist = (this->*_commands.at(packet.key))(packet, *it);
		    }
		  catch (std::out_of_range &err)
		    {
		      (void)err;
		      exist = this->_cnf(packet, *it);
		    }
		}
	    }
	  if (!exist || ((*it)->isClosed() && !(*it)->isInGame()))
	    {
	      this->_network->eraseSocket((*it)->getSocket());
	      delete (*it);
	      it = this->_clients.erase(it);
	    }
	  else
	    {
	      if ((*it)->isRecentlyUpdated() == false)
		this->_sendToNetwork(*it, 128, "");
	      ++it;
	    }
	}
      this->_eraseUselessRooms();
    }
}
