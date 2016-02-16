//
// Enemy.hh for Enemy in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 15 16:14:10 2015 Thibaut Lopez
// Last update Wed Dec 23 11:42:41 2015 Thibaut Lopez
//

#ifndef	ENEMY_HH
#define	ENEMY_HH

#include "Creature.hh"
#include "ILoader.hh"

class	Enemy : public Creature
{
private:
  IEnemy	*_enemy;

public:
  explicit Enemy(IEnemy *, const std::size_t &, const std::size_t &);
  virtual ~Enemy();
  void		behave(Game *, eAction &, uAction &);
  eCreature	getType() const;
};

#include "ILoader.hh"

#endif
