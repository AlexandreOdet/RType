//
// Game.cpp for Game in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Thu Dec 10 23:50:16 2015 Thibaut Lopez
// Last update Sat Jan  2 20:30:28 2016 Thibaut Lopez
//

#include "Game.hpp"
#include "Server.hh"

Game::Game()
  : _needToBeFreed(false)
{
}

Game::~Game()
{
}

void				Game::_positionPlayers()
{
  int				pos;
  int				i;
  std::list<Client *>::iterator	it;

  it = _players.begin();
  i = 1;
  while (it != _players.end())
  {
    Server::_sendToNetwork((*it), 16, Server::itos(i));
    it++;
    i++;
  }

  pos = HEIGHT / this->_players.size() / 2;
  i = 0;
  it = this->_players.begin();
  while (it != this->_players.end())
    {
      (*it)->id(i + 1);
      (*it)->posX(200);
      (*it)->posY(pos * (1 + 2 * i));
      (*it)->speedX(0);
      (*it)->speedY(0);
      (*it)->reset();
      (*it)->isInGame(true);
      FCommand::sendToAll(this, FCommand::pop(*it, static_cast<eCreature>(i)), NULL);
      i++;
      ++it;
    }
}

void				Game::_handleClientCommands()
{
  std::list<Client *>::iterator	it;
  Client			*clt;
  ISocket			*sock;
  t_pkt				packet;

  it = this->_players.begin();
  while (it != this->_players.end())
  {
    clt = *it;
    clt->lock();
    sock = clt->getSocket();
    while (!clt->isClosed() && sock->receive(packet))
  	{
  	  if (!this->_fcommand.handlePacket(clt, packet, this))
  	    clt->close();
    }
    if (clt->isClosed())
    {
      if (clt->isInGame())
        clt->isInGame(false);
      FCommand::sendToAll(this, FCommand::destroy(clt), clt);
      it = this->_players.erase(it);
    }
      else
      	++it;
      clt->unlock();
  }
}

void				Game::_handleEnemyCommands()
{
  std::list<Enemy *>::iterator	it;
  eAction			action;
  uAction			arg;

  it = this->_enemies.begin();
  while (it != this->_enemies.end())
    {
      action = NOTHING;
      (*it)->behave(this, action, arg);
      if (this->_fcommand.handleEnemy(*it, this, action, arg))
	++it;
      else
	it = this->_enemies.erase(it);
    }
}

bool				Game::_updateMove(Entity *entity, const bool &stopWhenOutside)
{
  bool			isMoving;
  bool			mustSendMove;
  int				pos;

  mustSendMove = false;
  isMoving = entity->isMoving();
  pos = entity->posX() + entity->speedX();
  if (stopWhenOutside && entity->speedX() != 0)
    {
      if (static_cast<int>(pos - entity->width()) <= 0)
  	{
  	  entity->posX(entity->width());
  	  entity->speedX(0);
  	  mustSendMove = true;
  	}
      else if (pos + entity->width() >= WIDTH)
  	{
  	  entity->posX(WIDTH - entity->width());
  	  entity->speedX(0);
  	  mustSendMove = true;
  	}
      else
  	entity->posX(pos);
    }
  else
    entity->posX(pos);

  pos = entity->posY() + entity->speedY();
  if (stopWhenOutside && entity->speedY() != 0)
    {
      if (static_cast<int>(pos - entity->height()) <= 0)
  	{
  	  entity->posY(entity->height());
  	  entity->speedY(0);
  	  mustSendMove = true;
  	}
      else if (pos + entity->height() >= HEIGHT)
	{
	  entity->posY(HEIGHT - entity->height());
	  entity->speedY(0);
	  mustSendMove = true;
	}
      else
    	entity->posY(pos);
    }
  else
    entity->posY(pos);

  if (mustSendMove)
    FCommand::sendToAll(this, FCommand::move(entity), NULL);
  return (isMoving);
}

void				Game::_updateClientMoves()
{
  std::list<Client *>::iterator	it;

  it = this->_players.begin();
  while (it != this->_players.end())
    {
      if (this->_updateMove(*it, true))
	this->_collisionLoop(*it, this->_enemies, false, COLLISION_DAM);
      if ((*it)->health() == 0)
	{
	  FCommand::sendToAll(this, FCommand::destroy(*it), *it);
	  (*it)->isInGame(false);
	  it = this->_players.erase(it);
	}
      else
	++it;
    }
}

void				Game::_updateWallScrolling()
{
  std::list<Wall *>::iterator	it;

  it = this->_walls.begin();
  while (it != this->_walls.end())
    {
      this->_updateMove(*it, false);
      this->_collisionLoop(*it, this->_players, true, COLLISION_DAM);
      ++it;
    }
}

void				Game::_updateEnemiesMoves()
{
  std::list<Enemy *>::iterator	it;

  it = this->_enemies.begin();
  while (it != this->_enemies.end())
    {
      if (this->_updateMove(*it, true))
	this->_collisionLoop(*it, this->_players, true, COLLISION_DAM);
      ++it;
    }
}

void				Game::_updateShootMoves()
{
  std::list<AShoot *>::iterator	it;
  int				pos;

  it = this->_shoots.begin();
  while (it != this->_shoots.end())
    {
      pos = (*it)->posX() + (*it)->speedX();
      if (pos < 0 || pos > WIDTH)
	{
	  FCommand::sendToAll(this, FCommand::destroy(*it), NULL);
	  it = this->_shoots.erase(it);
	}
      else
	{
	  (*it)->posX(pos);
	  pos = (*it)->posY() + (*it)->speedY();
	  if (pos < 0 || pos > HEIGHT)
	    {
	      FCommand::sendToAll(this, FCommand::destroy(*it), NULL);
	      it = this->_shoots.erase(it);
	    }
	  else
	    {
	      (*it)->posY(pos);
	      if ((*it)->owner() <= 4)
		pos = this->_collisionLoop(*it, this->_enemies, true, (*it)->power());
	      else
		pos = this->_collisionLoop(*it, this->_players, true, (*it)->power());
	      if ((*it)->collide(pos))
		{
		  FCommand::sendToAll(this, FCommand::destroy(*it), NULL);
		  it = this->_shoots.erase(it);
		}
	      else
		++it;
	    }
	}
    }
}

const std::list<Client *>	&Game::getPlayers() const
{
  return _players;
}

bool				Game::addPlayer(Client *clt)
{
  if (this->_players.size() < 4 && std::find(this->_players.begin(), this->_players.end(), clt) == this->_players.end())
    {
      this->_players.push_back(clt);
      return (true);
    }
  return (false);
}

bool				Game::deletePlayer(Client *clt)
{
  for (std::list<Client *>::iterator it = _players.begin(); it != _players.end(); ++it)
    {
      if (clt == (*it))
	{
	  _players.erase(it);
	  return true;
	}
    }
  return false;
}

void				Game::addShoot(AShoot *shoot)
{
  this->_shoots.push_back(shoot);
}

std::size_t			Game::newIdShoot() const
{
  int				id;
  std::list<AShoot *>::const_iterator	it;

  id = 0;
  it = this->_shoots.begin();
  while (it != this->_shoots.end())
    {
      if ((*it)->id() == id)
	{
	  id++;
	  it = this->_shoots.begin();
	}
      else
	++it;
    }
  return (id);
}

void				Game::addEnemy(Enemy *enemy)
{
  int				id = 5;
  std::list<Enemy *>::iterator	it;

  it = this->_enemies.begin();
  while (it != this->_enemies.end())
    {
      if ((*it)->id() == id)
	{
	  id++;
	  it = this->_enemies.begin();
	}
      else
	++it;
    }
  enemy->id(id);
  this->_enemies.push_back(enemy);
  FCommand::sendToAll(this, FCommand::pop(enemy, enemy->getType()), NULL);
}

void				Game::addWall(Wall *wall)
{
  this->_walls.push_back(wall);
}

bool				Game::needToBeFreed() const
{
  return (this->_needToBeFreed);
}

void				Game::loop(const std::string &stage)
{
  bool				loop;
  std::size_t			nSec;
  std::size_t			nUsec;
  std::size_t			tmpSec;
  std::size_t			tmpUsec;
  std::size_t			rSec;
  std::size_t			rUsec;

  this->_stage.loadStage(stage);
  this->_positionPlayers();
  loop = true;
  while (loop)
    {
      (STTime::getInstance())->now(nSec, nUsec);
      this->_handleClientCommands();
      this->_handleEnemyCommands();
      this->_updateClientMoves();
      this->_updateWallScrolling();
      this->_updateEnemiesMoves();
      this->_updateShootMoves();
      if (this->_players.size() == 0 || (!this->_stage.update(this) && this->_enemies.size() == 0))
	loop = false;
      else
	{
	  (STTime::getInstance())->now(tmpSec, tmpUsec);
	  (STTime::getInstance())->sub(tmpSec, tmpUsec, nSec, nUsec, rSec, rUsec);
	  if (rSec == 0 && rUsec < 16666)
	    (STTime::getInstance())->Usleep(16666 - rUsec);
	}
    }
  FCommand::sendToAll(this, FCommand::endGame(), NULL);
  std::list<Client *>::iterator	it;

  it = this->_players.begin();
  while (it != this->_players.end())
    {
      (*it)->isInGame(false);
      it = this->_players.erase(it);
    }
  this->_needToBeFreed = true;
}
