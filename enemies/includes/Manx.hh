//
// Manx.hh for Manx in /home/lopez_t/rtype/enemies
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Thu Dec 17 11:56:37 2015 Thibaut Lopez
// Last update Tue Dec 22 16:28:38 2015 Thibaut Lopez
//

#ifndef	MANX_HH
#define	MANX_HH

#include "ILoader.hh"
#include "NormalShoot.hh"
#include "MediumShoot.hh"
#include "LongShoot.hh"
#include "EnemyShoot.hh"
#include "STTime.hh"
#include "Client.hh"
#include "Game.hpp"

class	Manx : public IEnemy
{
private:
  std::size_t	_sec;
  std::size_t	_usec;
  std::size_t	_shootSec;
  std::size_t	_shootUsec;
  bool		_goingUp;

public:
  Manx();
  virtual ~Manx();
  void		behave(const Creature *, const Game *, eAction &, uAction &);
  eCreature	getType() const;
  std::size_t	getMaxHealth() const;
  std::size_t	getHeight() const;
  std::size_t	getWidth() const;
};

extern "C" IEnemy	*loadLib();

#endif
