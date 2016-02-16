//
// LongShoot.cpp for LongShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:37:44 2015 Thibaut Lopez
// Last update Tue Dec 22 15:37:15 2015 Thibaut Lopez
//

#include "LongShoot.hh"

LongShoot::LongShoot(const std::size_t &x, const std::size_t &y, const std::size_t &id, const std::size_t &owner)
  : AShoot(50, owner, 1)
{
  this->id(id + 0x80000000);
  this->posX(x);
  this->posY(y);
  this->width(85);
  this->height(20);
  this->speedX(SHOOT_SPEEDX);
  this->speedY(SHOOT_SPEEDY);
}

LongShoot::~LongShoot()
{
}

eShoot	LongShoot::getType() const
{
  return (LONGS);
}
