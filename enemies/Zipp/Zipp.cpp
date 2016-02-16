//
// Zipp.cpp for Zipp in /home/lopez_t/rtype/enemies
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 22 16:30:39 2015 Thibaut Lopez
// Last update Tue Dec 22 16:30:39 2015 Thibaut Lopez
//

#include "Zipp.hh"

Zipp::Zipp()
{
}

Zipp::~Zipp()
{
}

void		Zipp::behave(const Creature *me, const Game *game, eAction &action, uAction &arg)
{
  (void)me;
  (void)game;
  (void)action;
  (void)arg;
}

eCreature		Zipp::getType() const
{
  return (ZIPP);
}

std::size_t	Zipp::getMaxHealth() const
{
  return (1);
}

std::size_t	Zipp::getHeight() const
{
  return (1);
}

std::size_t	Zipp::getWidth() const
{
  return (1);
}

extern "C" IEnemy	*loadLib()
{
  return (new Zipp());
}
