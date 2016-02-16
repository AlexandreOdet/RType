//
// LongShoot.hh for LongShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:37:44 2015 Thibaut Lopez
// Last update Thu Dec 17 13:49:14 2015 Thibaut Lopez
//

#ifndef	LONGSHOOT_HH
#define	LONGSHOOT_HH

#include "AShoot.hh"

class	LongShoot : public AShoot
{
public:
  explicit LongShoot(const std::size_t &, const std::size_t &, const std::size_t &, const std::size_t &);
  virtual ~LongShoot();
  eShoot	getType() const;
};

#endif
