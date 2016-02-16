//
// NormalShoot.cpp for NormalShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:23:56 2015 Thibaut Lopez
// Last update Tue Dec 22 15:36:34 2015 Thibaut Lopez
//

#include "NormalShoot.hh"

NormalShoot::NormalShoot(const std::size_t &x, const std::size_t &y, const std::size_t &id, const std::size_t &owner)
  : AShoot(10, owner, 1)
{
  this->id(id + 0x80000000);
  this->posX(x);
  this->posY(y);
  this->width(21);
  this->height(17);
  this->speedX(SHOOT_SPEEDX);
  this->speedY(SHOOT_SPEEDY);
}

NormalShoot::~NormalShoot()
{
}

eShoot	NormalShoot::getType() const
{
  return (NORMAL);
}
