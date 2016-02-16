//
// Manx.cpp for Manx in /home/lopez_t/rtype/enemies
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Thu Dec 17 11:56:37 2015 Thibaut Lopez
// Last update Sat Jan  2 20:28:23 2016 Thibaut Lopez
//

#include "Manx.hh"

Manx::Manx()
  : _shootSec(0), _shootUsec(0), _goingUp(true)
{
}

Manx::~Manx()
{
}

void			Manx::behave(const Creature *my, const Game *game, eAction &action, uAction &arg)
{
  std::size_t		nSec;
  std::size_t		nUsec;
  std::size_t		tmpSec;
  std::size_t		tmpUsec;
  std::list<Client *>	clients;
  std::list<Client *>::iterator	it;

  if (my->speedX() >= 0)
    {
      if (static_cast<int>(my->posX() - my->width()) <= 0)
	action = SUICIDE;
      else
	{
	  action = GOLEFT;
	  arg.speed = SCROLLER;
	  this->_sec = 0;
	  this->_usec = 0;
	}
      return ;
    }
  (STTime::getInstance())->now(nSec, nUsec);
  (STTime::getInstance())->sub(nSec, nUsec, this->_sec, this->_usec, tmpSec, tmpUsec);
  if (tmpSec >= 1)
    {
      action = (this->_goingUp) ? GOUP : GODOWN;
      arg.speed = (this->_goingUp) ? -1 : 1;
      (STTime::getInstance())->now(this->_sec, this->_usec);
      this->_goingUp = !this->_goingUp;
      return ;
    }
  (STTime::getInstance())->sub(nSec, nUsec, this->_shootSec, this->_shootUsec, tmpSec, tmpUsec);
  if (tmpSec > 0 || tmpUsec > 500000)
    {
      clients = game->getPlayers();
      it = clients.begin();
      while (it != clients.end())
	{
	  if ((*it)->posY() >= my->posY() - 20 && (*it)->posY() <= my->posY() + 20)
	    {
	      action = SHOOT;
	      (STTime::getInstance())->now(this->_shootSec, this->_shootUsec);
	      return ;
	    }
	  ++it;
	}
    }
  action = NOTHING;
}

eCreature		Manx::getType() const
{
  return (MANX);
}

std::size_t		Manx::getMaxHealth() const
{
  return (25);
}

std::size_t		Manx::getHeight() const
{
  return (11);
}

std::size_t		Manx::getWidth() const
{
  return (11);
}

extern "C" IEnemy	*loadLib()
{
  return (new Manx());
}
