//
// EnemyShoot.cpp for EnemyShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:37:44 2015 Thibaut Lopez
// Last update Sat Jan  2 20:22:29 2016 Thibaut Lopez
//

#include "EnemyShoot.hh"

EnemyShoot::EnemyShoot(const std::size_t &x, const std::size_t &y, const std::size_t &id, const std::size_t &owner)
  : AShoot(15, owner, 1)
{
  this->id(id + 0x80000000);
  this->posX(x);
  this->posY(y);
  this->width(5);
  this->height(5);
  this->speedX((-SHOOT_SPEEDX) / 2);
  this->speedY(SHOOT_SPEEDY);
}

EnemyShoot::~EnemyShoot()
{
}

eShoot	EnemyShoot::getType() const
{
  return (ENEMY);
}
