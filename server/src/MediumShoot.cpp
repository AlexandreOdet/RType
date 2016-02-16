//
// MediumShoot.cpp for MediumShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:35:06 2015 Thibaut Lopez
// Last update Tue Dec 22 15:36:36 2015 Thibaut Lopez
//

#include "MediumShoot.hh"

MediumShoot::MediumShoot(const std::size_t &x, const std::size_t &y, const std::size_t &id, const std::size_t &owner)
  : AShoot(30, owner, 1)
{
  this->id(id + 0x80000000);
  this->posX(x);
  this->posY(y);
  this->width(45);
  this->height(17);
  this->speedX(SHOOT_SPEEDX);
  this->speedY(SHOOT_SPEEDY);
}

MediumShoot::~MediumShoot()
{
}

eShoot	MediumShoot::getType() const
{
  return (MEDIUM);
}
