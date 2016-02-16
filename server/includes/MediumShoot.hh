//
// MediumShoot.hh for MediumShoot in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 15:35:06 2015 Thibaut Lopez
// Last update Thu Dec 17 13:48:07 2015 Thibaut Lopez
//

#ifndef	MEDIUMSHOOT_HH
#define	MEDIUMSHOOT_HH

#include "AShoot.hh"

class	MediumShoot : public AShoot
{
public:
  explicit MediumShoot(const std::size_t &, const std::size_t &, const std::size_t &, const std::size_t &);
  virtual ~MediumShoot();
  eShoot	getType() const;
};

#endif
