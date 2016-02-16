//
// Bydo.cpp for Bydo in /home/lopez_t/rtype/enemies
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 22 16:33:03 2015 Thibaut Lopez
// Last update Tue Dec 22 16:33:03 2015 Thibaut Lopez
//

#include "Bydo.hh"

Bydo::Bydo()
{
}

Bydo::~Bydo()
{
}

void		Bydo::behave(const Creature *me, const Game *game, eAction &action, uAction &arg)
{
  (void)me;
  (void)game;
  (void)action;
  (void)arg;
}

eCreature		Bydo::getType() const
{
  return (ZIPP);
}

std::size_t	Bydo::getMaxHealth() const
{
  return (1);
}

std::size_t	Bydo::getHeight() const
{
  return (1);
}

std::size_t	Bydo::getWidth() const
{
  return (1);
}

extern "C" IEnemy	*loadLib()
{
  return (new Bydo());
}
