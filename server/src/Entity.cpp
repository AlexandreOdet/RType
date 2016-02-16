//
// Entity.cpp for Entity in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 11 11:43:38 2015 Thibaut Lopez
// Last update Tue Dec 22 11:57:27 2015 Thibaut Lopez
//

#include "Entity.hh"

Entity::Entity()
  : _id(-1), _posX(0), _posY(0), _speedX(0), _speedY(0), _height(0), _width(0)
{
}

Entity::Entity(Entity const &cpy)
  : _id(cpy.id()), _posX(cpy.posX()), _posY(cpy.posY()), _speedX(cpy.speedX()), _speedY(cpy.speedY()), _height(cpy.height()), _width(cpy.width())
{
}

Entity::~Entity()
{
}

Entity const		&Entity::operator=(Entity const &cpy)
{
  if (&cpy != this)
    {
      this->id(cpy.id());
      this->posX(cpy.posX());
      this->posY(cpy.posY());
      this->speedX(cpy.speedX());
      this->speedY(cpy.speedY());
      this->height(cpy.height());
      this->width(cpy.width());
    }
  return (*this);
}

const int		&Entity::id() const
{
  return (this->_id);
}

void			Entity::id(const int &id)
{
  this->_id = id;
}

const int		&Entity::posX() const
{
  return (this->_posX);
}

void			Entity::posX(const int &posX)
{
  this->_posX = posX;
}

const int		&Entity::posY() const
{
  return (this->_posY);
}

void			Entity::posY(const int &posY)
{
  this->_posY = posY;
}

const int		&Entity::speedX() const
{
  return (this->_speedX);
}

void			Entity::speedX(const int &speedX)
{
  this->_speedX = speedX;
}

const int		&Entity::speedY() const
{
  return (this->_speedY);
}

void			Entity::speedY(const int &speedY)
{
  this->_speedY = speedY;
}

const std::size_t	&Entity::height() const
{
  return (this->_height);
}

void			Entity::height(const std::size_t &height)
{
  this->_height = height;
}

const std::size_t	&Entity::width() const
{
  return (this->_width);
}

void			Entity::width(const std::size_t &width)
{
  this->_width = width;
}

bool			Entity::isMoving() const
{
  return (this->_speedX != 0 || this->_speedY != 0);
}
