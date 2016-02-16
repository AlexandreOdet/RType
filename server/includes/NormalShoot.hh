//
// NormalShoot.hh for NormalShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:23:56 2015 Thibaut Lopez
// Last update Thu Dec 17 13:47:38 2015 Thibaut Lopez
//

#ifndef	NORMALSHOOT_HH
#define	NORMALSHOOT_HH

#include "AShoot.hh"

class	NormalShoot : public AShoot
{
public:
  explicit NormalShoot(const std::size_t &, const std::size_t &, const std::size_t &, const std::size_t &);
  virtual ~NormalShoot();
  eShoot	getType() const;
};

#endif
