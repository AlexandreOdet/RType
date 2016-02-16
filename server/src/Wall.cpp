//
// Wall.cpp for Wall in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Mon Dec 21 18:07:10 2015 Thibaut Lopez
// Last update Wed Dec 23 11:45:38 2015 Thibaut Lopez
//

#include "Wall.hh"

Wall::Wall(const std::size_t &y)
{
  this->posX(WIDTH);
  this->posY(y);
  this->speedX(SCROLLER);
  this->speedY(0);
  this->height(HEIGHT / 16);
  this->width(WIDTH / 16);
}

Wall::~Wall()
{
}
