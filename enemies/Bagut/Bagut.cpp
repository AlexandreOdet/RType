//
// Bagut.cpp for Bagut in /home/lopez_t/rtype/enemies
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 22 16:32:45 2015 Thibaut Lopez
// Last update Tue Dec 22 16:32:45 2015 Thibaut Lopez
//

#include "Bagut.hh"
#ifdef _WIN32
#include "pch.h"
#endif
Bagut::Bagut()
{
}

Bagut::~Bagut()
{
}

void		Bagut::behave(const Creature *me, const Game *game, eAction &action, uAction &arg)
{
  (void)me;
  (void)game;
  (void)action;
  (void)arg;
}

eCreature		Bagut::getType() const
{
  return (ZIPP);
}

std::size_t	Bagut::getMaxHealth() const
{
  return (1);
}

std::size_t	Bagut::getHeight() const
{
  return (1);
}

std::size_t	Bagut::getWidth() const
{
  return (1);
}

extern "C" IEnemy	*loadLib()
{
  return (new Bagut());
}
