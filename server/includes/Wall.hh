//
// Wall.hh for Wall in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Mon Dec 21 18:07:10 2015 Thibaut Lopez
// Last update Wed Dec 23 11:41:15 2015 Thibaut Lopez
//

#ifndef	WALL_HH
#define	WALL_HH

#include "Entity.hh"

class	Wall : public Entity
{
public:
  explicit Wall(const std::size_t &);
  virtual ~Wall();
};

#endif
