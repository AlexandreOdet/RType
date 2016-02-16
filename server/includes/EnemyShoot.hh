//
// EnemyShoot.hh for EnemyShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:37:44 2015 Thibaut Lopez
// Last update Thu Dec 17 13:50:28 2015 Thibaut Lopez
//

#ifndef	ENEMYSHOOT_HH
#define	ENEMYSHOOT_HH

#include "AShoot.hh"

class	EnemyShoot : public AShoot
{
public:
  explicit EnemyShoot(const std::size_t &, const std::size_t &, const std::size_t &, const std::size_t &);
  virtual ~EnemyShoot();
  eShoot	getType() const;
};

#endif
