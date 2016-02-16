//
// Enemy.cpp for Enemy in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 15 16:14:10 2015 Thibaut Lopez
// Last update Wed Dec 23 14:27:10 2015 Thibaut Lopez
//

#include "Enemy.hh"
#include "Game.hpp"

Enemy::Enemy(IEnemy *enemy, const std::size_t &x, const std::size_t &y)
  : _enemy(enemy)
{
  this->_maxHealth = this->_enemy->getMaxHealth();
  if (this->_maxHealth == 0)
    this->_maxHealth = 1;
  this->_health = this->_maxHealth;
  this->height(this->_enemy->getHeight());
  if (this->height() == 0)
    this->height(1);
  this->width(this->_enemy->getWidth());
  if (this->width() == 0)
    this->width(1);
  if (static_cast<int>(x - this->width()) <= 0)
    this->posX(this->width());
  else if (x + this->width() >= WIDTH)
    this->posX(WIDTH - this->width());
  else
    this->posX(x);
  if (static_cast<int>(y - this->height()) <= 0)
    this->posY(this->height());
  else if (y + this->height() >= HEIGHT)
    this->posY(HEIGHT - this->height());
  else
    this->posY(y);
}

Enemy::~Enemy()
{
  delete this->_enemy;
}

void		Enemy::behave(Game *game, eAction &action, uAction &arg)
{
  this->_enemy->behave(this, game, action, arg);
}

eCreature	Enemy::getType() const
{
  return (this->_enemy->getType());
}
