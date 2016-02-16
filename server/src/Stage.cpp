//
// Stage.cpp for Stage in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 18 16:28:27 2015 Thibaut Lopez
// Last update Sat Jan  2 19:11:58 2016 Thibaut Lopez
//

#include "Stage.hh"

Stage::Stage()
  : MapParser(), _frameCount(0), _isLoaded(false)
{
  std::size_t	tmp;

  (STTime::getInstance())->now(tmp, tmp);
  srand(tmp);
}

Stage::~Stage()
{
}

void		Stage::_loadBasicMap()
{
  EnemyType	*enemyType;

  try
    {
      enemyType = new EnemyType("../enemies/Zipp.so", 0);
      this->_enemyTypes['z'] = enemyType;
    }
  catch (std::runtime_error &err)
    {
      std::cerr << err.what() << std::endl;
    }
  try
    {
      enemyType = new EnemyType("../enemies/Satellite.so", 0);
      this->_enemyTypes['s'] = enemyType;
    }
  catch (std::runtime_error &err)
    {
      std::cerr << err.what() << std::endl;
    }
  try
    {
      enemyType = new EnemyType("../enemies/Manx.so", 10);
      this->_enemyTypes['m'] = enemyType;
    }
  catch (std::runtime_error &err)
    {
      std::cerr << err.what() << std::endl;
    }
  try
    {
      enemyType = new EnemyType("../enemies/Bagut.so", 0);
      this->_enemyTypes['b'] = enemyType;
    }
  catch (std::runtime_error &err)
    {
      std::cerr << err.what() << std::endl;
    }
  this->map.push_back({'#', '#', '#', 'm', 's', '#', '#', '#'});
  for (int i = 0; i < 20; i++)
    this->map.push_back({'#', '#', '#', '#', '#', '#', '#', '#'});  
}

void		Stage::_harmoniseRandomEncounter()
{
  std::map<char, EnemyType *>::iterator	it;
  float		total;

  total = 0.0f;
  it = this->_enemyTypes.begin();
  while (!this->_enemyTypes.empty() && it != this->_enemyTypes.end())
    {
      total += (*it).second->encounterChance();
      ++it;
    }

  if (total == 100.0 || total == 0.0)
    return ;
  it = this->_enemyTypes.begin();
  while (!this->_enemyTypes.empty() && it != this->_enemyTypes.end())
    {
      (*it).second->encounterChance(100.0f * (*it).second->encounterChance() / total);
      ++it;
    }
}

void		Stage::loadStage(const std::string &stage)
{
  if (!this->parse(stage) && !this->_isLoaded)
    this->_loadBasicMap();
  this->_harmoniseRandomEncounter();
  this->_pos = this->map.begin();
  this->_isLoaded = true;
}

bool		Stage::update(Game *game)
{
  int		randNum;
  float		total = 0.0;
  std::map<char, EnemyType *>::iterator	it;
  int		posY;

  if (this->_pos == this->map.end())
    return (false);
  if (this->_frameCount == 0)
    {
      for (int i = 0; i < 8; i++)
	{
	  posY = HEIGHT / 16 * (1 + 2 * i);
	  if ((*this->_pos)[i] == WALL_CHAR)
	    game->addWall(new Wall(posY));
	  else if ((*this->_pos)[i] != '#')
	    {
	      try
		{
		  game->addEnemy(this->_enemyTypes.at((*this->_pos)[i])->newEnemy(WIDTH - 100, posY));
		}
	      catch (std::out_of_range &err)
		{
		  (void)err;
		}
	    }
	}
      ++this->_pos;
      if (this->_pos == this->map.end())
	return (false);
    }
  if (this->_frameCount % 10 == 0 && (randNum = rand() % 100) <= 5)
    {
      randNum = rand() % 100;
      it = this->_enemyTypes.begin();
      while (it != this->_enemyTypes.end())
	{
	  total += (*it).second->encounterChance();
	  if (total > randNum)
	    {
	      game->addEnemy((*it).second->newEnemy(WIDTH - 100, rand() % HEIGHT));
	      it = this->_enemyTypes.end();
	    }
	  else
	    ++it;
	}
    }
  this->_frameCount++;
  this->_frameCount %= 80;
  return (true);
}
