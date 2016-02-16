//
// Game.hh for Game in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Thu Dec 10 23:50:16 2015 Thibaut Lopez
// Last update Sat Jan  2 16:36:09 2016 Thibaut Lopez
//

#ifndef	GAME_HH
#define	GAME_HH

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "Client.hh"
#include "FCommand.hh"
#include "Stage.hh"
#include "ILoader.hh"

class Wall;
class Stage;
class Server;

class	Game
{
private:
  std::list<Client *>		_players;
  std::list<Enemy *>		_enemies;
  std::list<AShoot *>		_shoots;
  std::list<Wall *>		_walls;
  bool				_needToBeFreed;
  FCommand			_fcommand;
  Stage				_stage;
  void				_positionPlayers();
  void				_handleClientCommands();
  void				_handleEnemyCommands();
  template <class Iterator>
  Iterator			_collision(Iterator begin, Iterator end, const Entity *attrs)
  {
    while (begin != end)
      {
	if (attrs->posX() - attrs->width() < (*begin)->posX() + (*begin)->width() &&
	    attrs->posX() + attrs->width() > (*begin)->posX() - (*begin)->width() &&
	    attrs->posY() - attrs->height() < (*begin)->posY() + (*begin)->height() &&
	    attrs->posY() + attrs->height() > (*begin)->posY() - (*begin)->height())
	  return (begin);
	++begin;
      }
    return (end);
  }

  template <class List>
  std::size_t			_collisionLoop(Entity *collider, List &colliding, bool whoIsColliding, int power)
  {
    typename List::iterator	it;
    eHealthState		healthState;
    Creature			*target;
    std::size_t			ret;
    Client			*clt;

    it = colliding.begin();
    ret = 0;
    while ((it = this->_collision(it, colliding.end(), collider)) != colliding.end())
      {
	if (whoIsColliding == true)
	  target = static_cast<Creature *>(*it);
	else
	  target = static_cast<Creature *>(collider);
	healthState = target->changeHealth(power);
	if (healthState == CHANGED)
	  {
	    ret++;
	    FCommand::sendToAll(this, FCommand::health(target), NULL);
	  }
	else if (healthState == EMPTY)
	  {
	    ret++;
	    FCommand::sendToAll(this, FCommand::destroy(target), NULL);
	    if (whoIsColliding == true)
	      {
		if ((clt = dynamic_cast<Client *>(*it)) != NULL)
		  clt->isInGame(false);
		it = colliding.erase(it);
	      }
	    else
	      ++it;
	  }
	else
	  ++it;
      }
    return (ret);
  }

  bool				_updateMove(Entity *, const bool &);
  void				_updateWallScrolling();
  void				_updateClientMoves();
  void				_updateEnemiesMoves();
  void				_updateShootMoves();

public:
  Game();
  virtual ~Game();
  const std::list<Client *>	&getPlayers() const;
  bool				addPlayer(Client *);
  bool				deletePlayer(Client *);
  void				addShoot(AShoot *);
  std::size_t			newIdShoot() const;
  void				addEnemy(Enemy *);
  void				addWall(Wall *);
  bool				needToBeFreed() const;
  void				needToBeFreed(const bool &);
  void				loop(const std::string & = "");
};

#endif
