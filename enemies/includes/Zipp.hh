//
// Zipp.hh for Zipp in /home/lopez_t/rtype/enemies
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 22 16:30:39 2015 Thibaut Lopez
// Last update Tue Dec 22 16:31:41 2015 Thibaut Lopez
//

#ifndef	ZIPP_HH
#define	ZIPP_HH

#include "ILoader.hh"
#include "NormalShoot.hh"
#include "MediumShoot.hh"
#include "LongShoot.hh"
#include "EnemyShoot.hh"
#include "STTime.hh"
#include "Client.hh"
#include "Game.hpp"

class	Zipp : public IEnemy
{
public:
  Zipp();
  virtual ~Zipp();
  void		behave(const Creature *, const Game *, eAction &, uAction &);
  eCreature	getType() const;
  std::size_t	getMaxHealth() const;
  std::size_t	getHeight() const;
  std::size_t	getWidth() const;
};

extern "C" IEnemy	*loadLib();

#endif
