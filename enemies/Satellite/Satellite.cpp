//
// Satellite.cpp for Satellite in /home/lopez_t/rtype/enemies
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 22 16:32:10 2015 Thibaut Lopez
// Last update Sat Jan  2 20:28:06 2016 Thibaut Lopez
//

#include "Satellite.hh"

Satellite::Satellite()
{
}

Satellite::~Satellite()
{
}

void		Satellite::behave(const Creature *me, const Game *game, eAction &action, uAction &arg)
{
  (void)me;
  (void)game;
  (void)action;
  (void)arg;
}

eCreature		Satellite::getType() const
{
  return (ZIPP);
}

std::size_t	Satellite::getMaxHealth() const
{
  return (100);
}

std::size_t	Satellite::getHeight() const
{
  return (6);
}

std::size_t	Satellite::getWidth() const
{
  return (6);
}

extern "C" IEnemy	*loadLib()
{
  return (new Satellite());
}
