#ifndef __ILOADER__
#define __ILOADER__

#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include "AShoot.hh"
#include "Creature.hh"

class	Game;

union	uAction
{
  int		speed;
};

class	IEnemy
{
public:
  virtual ~IEnemy() {}
  virtual void		behave(const Creature *, const Game *, eAction &, uAction &) = 0;
  virtual eCreature	getType() const = 0;
  virtual std::size_t	getMaxHealth() const = 0;
  virtual std::size_t	getHeight() const = 0;
  virtual std::size_t	getWidth() const = 0;
};

class	ILoader
{
public:
  virtual ~ILoader() {};
  virtual bool openLibrary(const std::string &) = 0;
  virtual void closeLibrary()const  = 0;
  virtual IEnemy *getInstance() const = 0;
};

#endif /*__ILOADER__*/
