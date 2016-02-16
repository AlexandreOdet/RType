//
// Satellite.hh for Satellite in /home/lopez_t/rtype/enemies
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 22 16:32:10 2015 Thibaut Lopez
// Last update Tue Dec 22 16:32:10 2015 Thibaut Lopez
//

#ifndef	SATELLITE_HH
#define	SATELLITE_HH

#include "ILoader.hh"
#include "NormalShoot.hh"
#include "MediumShoot.hh"
#include "LongShoot.hh"
#include "EnemyShoot.hh"
#include "STTime.hh"
#include "Client.hh"
#include "Game.hpp"

class	Satellite : public IEnemy
{
public:
  Satellite();
  virtual ~Satellite();
  void		behave(const Creature *, const Game *, eAction &, uAction &);
  eCreature	getType() const;
  std::size_t	getMaxHealth() const;
  std::size_t	getHeight() const;
  std::size_t	getWidth() const;
};

extern "C" IEnemy	*loadLib();

#endif
