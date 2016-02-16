//
// Creature.hh for Creature in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 17:41:18 2015 Thibaut Lopez
// Last update Sat Jan  2 17:04:02 2016 Thibaut Lopez
//

#ifndef	CREATURE_HH
#define	CREATURE_HH

#include "Entity.hh"
#include "STTime.hh"

enum	eHealthState
  {
    NOT_CHANGED,
    CHANGED,
    EMPTY
  };

class	Creature : public Entity
{
protected:
  std::size_t		_health;
  std::size_t		_maxHealth;
  std::size_t		_invicibleSec;
  std::size_t		_invicibleUsec;

public:
  Creature();
  explicit Creature(const std::size_t &);
  virtual ~Creature();
  void			reset();
  const std::size_t	&health() const;
  void			invicible();
  bool			isInvicible();
  eHealthState		changeHealth(const int &);
};

#endif
