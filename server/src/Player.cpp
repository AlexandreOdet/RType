//
// Player.cpp for Player in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 12:00:38 2015 Thibaut Lopez
// Last update Sat Jan  2 20:26:46 2016 Thibaut Lopez
//

#include "Player.hh"

Player::Player()
  : Creature(100), _isCharging(false), _chargeSec(0), _chargeUsec(0)
{
  this->height(13);
  this->width(32);
}

Player::Player(const std::size_t &id)
  : Creature(100)
{
  this->id(id);
  this->height(6);
  this->width(16);
}

Player::~Player()
{
}

bool			Player::isCharging() const
{
  return (this->_isCharging);
}

void			Player::isCharging(const bool &isCharging)
{
  if (isCharging == this->_isCharging)
    return ;
  this->_isCharging = isCharging;
  if (isCharging == true)
    (STTime::getInstance())->now(this->_chargeSec, this->_chargeUsec);
}

AShoot			*Player::shoot(const std::size_t &id)
{
  std::size_t		time[4];

  if (!this->_isCharging)
    return (new NormalShoot(this->posX(), this->posY(), id, this->id()));
  this->_isCharging = false;
  (STTime::getInstance())->now(time[0], time[1]);
  (STTime::getInstance())->sub(time[0], time[1], this->_chargeSec, this->_chargeUsec, time[2], time[3]);
  if (time[2] > 0  || (time[2] == 0 && time[3] >= 700000))
    return (new LongShoot(this->posX(), this->posY(), id, this->id()));
  else if (time[2] > 0 || (time[2] == 0 && time[3] >= 400000))
    return (new MediumShoot(this->posX(), this->posY(), id, this->id()));
  else
    return (new NormalShoot(this->posX(), this->posY(), id, this->id()));
}
