//
// AShoot.hh for AShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:03:19 2015 Thibaut Lopez
// Last update Thu Dec 17 14:07:08 2015 Thibaut Lopez
//

#ifndef	ASHOOT_HH
#define	ASHOOT_HH

#include <iostream>
#include <string>
#include "Entity.hh"

class	AShoot : public Entity
{
protected:
  std::size_t		_power;
  std::size_t		_owner;
  int			_collision;

public:
  explicit AShoot(const std::size_t &, const std::size_t &, const std::size_t &);
  virtual ~AShoot();
  const std::size_t	&power() const;
  const std::size_t	&owner() const;
  bool			collide(const std::size_t &);
  virtual eShoot	getType() const = 0;
};

#endif
