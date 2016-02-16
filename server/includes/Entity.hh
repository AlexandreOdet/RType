//
// Entity.hh for Entity in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 11:43:38 2015 Thibaut Lopez
// Last update Tue Dec 22 11:56:28 2015 Thibaut Lopez
//

#ifndef	ENTITY_HH
#define	ENTITY_HH

#include <iostream>
#include <string>
#include "GameHeader.hh"

class	Entity
{
protected:
  int			_id;
  int			_posX;
  int			_posY;
  int			_speedX;
  int			_speedY;
  std::size_t		_height;
  std::size_t		_width;

public:
  Entity();
  Entity(Entity const &);
  virtual ~Entity();
  virtual Entity const	&operator=(Entity const &);
  const int		&id() const;
  void			id(const int &);
  const int		&posX() const;
  void			posX(const int &);
  const int		&posY() const;
  void			posY(const int &);
  const int		&speedX() const;
  void			speedX(const int &);
  const int		&speedY() const;
  void			speedY(const int &);
  const std::size_t	&height() const;
  void			height(const std::size_t &);
  const std::size_t	&width() const;
  void			width(const std::size_t &);
  bool			isMoving() const;
};

#endif
