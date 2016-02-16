//
// Player.hh for Player in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 12:00:38 2015 Thibaut Lopez
// Last update Mon Dec 14 16:56:27 2015 Thibaut Lopez
//

#ifndef	PLAYER_HH
#define	PLAYER_HH

#include "NormalShoot.hh"
#include "MediumShoot.hh"
#include "LongShoot.hh"
#include "Creature.hh"

class	Player : public Creature
{
private:
  bool			_isCharging;
  std::size_t		_chargeSec;
  std::size_t		_chargeUsec;

public:
  Player();
  Player(const std::size_t &);
  virtual ~Player();

  bool			isCharging() const;
  void			isCharging(const bool &);
  AShoot		*shoot(const std::size_t &);
};

#endif
