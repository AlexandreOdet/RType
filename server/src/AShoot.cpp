//
// AShoot.cpp for AShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:03:19 2015 Thibaut Lopez
// Last update Thu Dec 17 13:45:36 2015 Thibaut Lopez
//

#include "AShoot.hh"

AShoot::AShoot(const std::size_t &power, const std::size_t &owner, const std::size_t &collision)
  : Entity(), _power(power), _owner(owner), _collision(collision)
{
}

AShoot::~AShoot()
{
}

const std::size_t	&AShoot::power() const
{
  return (this->_power);
}

const std::size_t	&AShoot::owner() const
{
  return (this->_owner);
}

bool			AShoot::collide(const std::size_t &collisionNb)
{
  this->_collision -= collisionNb;
  if (this->_collision <= 0)
    return (true);
  return (false);
}
