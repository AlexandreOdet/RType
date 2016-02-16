//
// Bagut.hh for Bagut in /home/lopez_t/rtype/enemies
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 22 16:32:45 2015 Thibaut Lopez
// Last update Tue Dec 22 16:32:45 2015 Thibaut Lopez
//

#ifndef	BAGUT_HH
#define	BAGUT_HH

#include "ILoader.hh"
#include "NormalShoot.hh"
#include "MediumShoot.hh"
#include "LongShoot.hh"
#include "EnemyShoot.hh"
#include "STTime.hh"
#include "Client.hh"
#include "Game.hpp"

class	Bagut : public IEnemy
{
public:
  Bagut();
  virtual ~Bagut();
  void		behave(const Creature *, const Game *, eAction &, uAction &);
  eCreature	getType() const;
  std::size_t	getMaxHealth() const;
  std::size_t	getHeight() const;
  std::size_t	getWidth() const;
};

extern "C" IEnemy	*loadLib();

#endif
