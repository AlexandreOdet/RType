//
// Creature.cpp for Creature in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 17:41:18 2015 Thibaut Lopez
// Last update Sat Jan  2 19:10:51 2016 Thibaut Lopez
//

#include "Creature.hh"

Creature::Creature()
{
}

Creature::Creature(const std::size_t &maxHealth)
  : Entity(), _health(maxHealth), _maxHealth(maxHealth)
{
}

Creature::~Creature()
{
}

void			Creature::reset()
{
  this->_health = this->_maxHealth;
}

const std::size_t	&Creature::health() const
{
  return (this->_health);
}

void			Creature::invicible()
{
  (STTime::getInstance())->now(this->_invicibleSec, this->_invicibleUsec);
}

bool			Creature::isInvicible()
{
  std::size_t		sec;
  std::size_t		usec;
  std::size_t		rSec;
  std::size_t		rUsec;

  (STTime::getInstance())->now(sec, usec);
  (STTime::getInstance())->sub(sec, usec, this->_invicibleSec, this->_invicibleUsec, rSec, rUsec);
  if (rSec >= 1)
    return (false);
  return (true);
}

eHealthState		Creature::changeHealth(const int &value)
{
  int			health;

  if (!this->isInvicible())
    {
      this->invicible();
      health = this->_health;
      health -= value;
      if (health <= 0)
	this->_health = 0;
      else if (static_cast<std::size_t>(health) > this->_maxHealth)
	this->_health = this->_maxHealth;
      else
	this->_health = health;
      return ((this->_health == 0) ? EMPTY : CHANGED);
    }
  return (NOT_CHANGED);
}
