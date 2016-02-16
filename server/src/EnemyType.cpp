//
// EnemyType.cpp for EnemyType in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 18 16:37:02 2015 Thibaut Lopez
// Last update Wed Dec 23 11:43:26 2015 Thibaut Lopez
//

#include "ILoader.hh"
#ifdef WIN32
#include "WLoader.hh"
#endif
#include "EnemyType.hh"

EnemyType::EnemyType(const std::string &lib, const float &encounterChance)
  : _encounterChance(encounterChance)
{
  IEnemy	*tmp;

  if (this->_encounterChance < 0.0)
    this->_encounterChance = 0.0;
  if (this->_encounterChance > 50.0)
    this->_encounterChance = 50.0;
#ifdef	WIN32
  this->_loader = new WLoader();
#else
  this->_loader = new ULoader();
#endif
  if (!this->_loader->openLibrary(lib))
    throw std::runtime_error("Couldn't load.");
  tmp = this->_loader->getInstance();
  if (tmp != NULL)
    delete tmp;
}

EnemyType::~EnemyType()
{
  this->_loader->closeLibrary();
  delete this->_loader;
}

Enemy		*EnemyType::newEnemy(const std::size_t &x, const std::size_t &y)
{
  return (new Enemy(this->_loader->getInstance(), x, y));
}

const float	&EnemyType::encounterChance() const
{
  return (this->_encounterChance);
}

void		EnemyType::encounterChance(const float &encounterChance)
{
  this->_encounterChance = encounterChance;
}
