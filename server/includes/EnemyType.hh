//
// EnemyType.hh for EnemyType in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 18 16:37:02 2015 Thibaut Lopez
// Last update Wed Dec 23 11:44:03 2015 Thibaut Lopez
//

#ifndef	ENEMYTYPE_HH
#define	ENEMYTYPE_HH

#include "Enemy.hh"
#ifdef	WIN32
#include "WLoader.hh"
#else
#include "ULoader.hh"
#endif

class	EnemyType
{
private:

  ILoader	*_loader;
  float		_encounterChance;

public:
  explicit EnemyType(const std::string &, const float & = 10.0);
  virtual ~EnemyType();
  Enemy		*newEnemy(const std::size_t &, const std::size_t &);
  const float	&encounterChance() const;
  void		encounterChance(const float &);
};

#endif
