#include "Room.hh"

Room::Room(const int id, const int nbPlayer)
{
  this->_id = id;
  this->_nbPlayer = nbPlayer;
  this->_nbPlayerReady = 0;
}

Room::~Room()
{

}

int Room::getIdRoom() const
{
  return this->_id;
}

int Room::getNbPlayerRoom() const
{
  return this->_nbPlayer;
}

void Room::setPlayer(int const nb)
{
  this->_nbPlayer = nb;
}

int Room::getReadys() const
{
  return this->_nbPlayerReady;
}

void Room::addReadys(int const nb)
{
    this->_nbPlayerReady = nb;
}
