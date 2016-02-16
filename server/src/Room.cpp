#include "Room.hh"

Room::Room(const std::size_t &id)
  : _id(id)
{
}

Room::~Room()
{
}

const std::size_t	&Room::getId() const
{
  return _id;
}

bool			Room::addPlayer(Client *clt)
{
  if (!_game.addPlayer(clt))
    return (false);
  clt->leaveRoom();
  clt->enterRoom(_id, _game.getPlayers().size());
  return (true);
}

bool			Room::deletePlayer(Client *clt)
{
  if (!_game.deletePlayer(clt))
    return (false);
  clt->leaveRoom();
  return (true);
}

std::size_t		Room::getPlayersNumber() const
{
  return _game.getPlayers().size();
}

const std::list<Client *> & Room::getPlayers() const
{
  return this->_game.getPlayers();
}

bool			Room::needToBeFreed()
{
  return (this->_game.needToBeFreed());
}

void			Room::loop()
{
  _game.loop();
}
