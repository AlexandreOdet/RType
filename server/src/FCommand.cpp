//
// FCommand.cpp for FCommand in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 08 14:55:01 2015 Thibaut Lopez
// Last update Sat Jan  2 20:06:53 2016 Thibaut Lopez
//

#include "FCommand.hh"
#include "Game.hpp"

FCommand::FCommand()
{
  this->_commands[1] = &FCommand::_disconnect;
  this->_commands[4] = &FCommand::_leaveRoom;
  this->_commands[7] = &FCommand::_move;
  this->_commands[8] = &FCommand::_loadShoot;
  this->_commands[9] = &FCommand::_shoot;
  this->_commands[128] = &FCommand::_ping;
  this->_moves[UP] = &FCommand::_moveUp;
  this->_moves[DOWN] = &FCommand::_moveDown;
  this->_moves[LEFT] = &FCommand::_moveLeft;
  this->_moves[RIGHT] = &FCommand::_moveRight;
  this->_moves[STOPX] = &FCommand::_moveStopX;
  this->_moves[STOPY] = &FCommand::_moveStopY;
  this->_actions[GOUP] = &FCommand::_up;
  this->_actions[GODOWN] = &FCommand::_down;
  this->_actions[GOLEFT] = &FCommand::_left;
  this->_actions[GORIGHT] = &FCommand::_right;
  this->_actions[GOSTOPX] = &FCommand::_stopX;
  this->_actions[GOSTOPY] = &FCommand::_stopY;
  this->_actions[SHOOT] = &FCommand::_shoot;
  this->_actions[SUICIDE] = &FCommand::_suicide;
  this->_actions[NOTHING] = &FCommand::_nothing;
}

FCommand::~FCommand()
{
}

bool			FCommand::_disconnect(Client *clt, const t_pkt &packet, Game *game)
{
  (void)clt;
  (void)packet;
  (void)game;
  return (false);
}

bool			FCommand::_leaveRoom(Client *clt, const t_pkt &packet, Game *game)
{
  (void)clt;
  (void)packet;
  (void)game;
  return (false);
}

bool			FCommand::_moveUp(Client *clt)
{
  if (clt->speedY() == -PLAYER_SPEEDY ||
      clt->posY() - clt->height() <= 0)
    return (false);
  clt->speedY(-PLAYER_SPEEDY);
  return (true);
}

bool			FCommand::_moveDown(Client *clt)
{
  if (clt->speedY() == PLAYER_SPEEDY ||
      clt->posY() + clt->height() >= HEIGHT)
    return (false);
  clt->speedY(PLAYER_SPEEDY);
  return (true);
}

bool			FCommand::_moveLeft(Client *clt)
{
  if (clt->speedX() == -PLAYER_SPEEDX ||
      clt->posX() - clt->width() <= 0)
    return (false);
  clt->speedX(-PLAYER_SPEEDX);
  return (true);
}

bool			FCommand::_moveRight(Client *clt)
{
 if (clt->speedX() == PLAYER_SPEEDX ||
      clt->posX() + clt->width() >= WIDTH)
    return (false);
  clt->speedX(PLAYER_SPEEDX);
  return (true);
}

bool			FCommand::_moveStopX(Client *clt)
{
  if (clt->speedX() == 0)
    return (false);
  clt->speedX(0);
  return (true);
}

bool			FCommand::_moveStopY(Client *clt)
{
  if (clt->speedY() == 0)
    return (false);
  clt->speedY(0);
  return (true);
}

bool			FCommand::_move(Client *clt, const t_pkt &packet, Game *game)
{
  Player		attr;
  eDirection		direction;
  bool			shouldSendMove;

  shouldSendMove = false;
  direction = (eDirection)packet.args[0];
  try
    {
      shouldSendMove = (this->*_moves.at(direction))(clt);
    }
  catch (std::out_of_range &err)
    {
      (void)err;
      return (true);
    }
  if (shouldSendMove)
    FCommand::sendToAll(game, FCommand::move(clt), clt);
  return (true);
}

bool			FCommand::_loadShoot(Client *clt, const t_pkt &packet, Game *game)
{
  t_pkt		toSend;

  (void)packet;
  clt->isCharging(true);
  toSend.key = 8;
  memcpy(toSend.args, &(clt->id()), sizeof(int));
  toSend.argLength = sizeof(int);
  FCommand::sendToAll(game, toSend, clt);
  return (true);
}

bool			FCommand::_shoot(Client *clt, const t_pkt &packet, Game *game)
{
  AShoot		*shoot;

  (void)packet;
  shoot = clt->shoot(game->newIdShoot());
  game->addShoot(shoot);
  FCommand::sendToAll(game, FCommand::shoot(shoot), clt);
  return (true);
}

bool			FCommand::_ping(Client *clt, const t_pkt &packet, Game *game)
{
  (void)clt;
  (void)packet;
  (void)game;
  return (true);
}

bool			FCommand::_up(Enemy *enemy, Game *game, const uAction &action)
{
  if (action.speed >= 0 ||
      enemy->speedY() == action.speed ||
      enemy->posY() - enemy->height() <= 0)
    return (true);
  enemy->speedY(action.speed);
  FCommand::sendToAll(game, FCommand::move(enemy), NULL);
  return (true);
}

bool			FCommand::_down(Enemy *enemy, Game *game, const uAction &action)
{
  if (action.speed <= 0 ||
      enemy->speedY() == action.speed ||
      enemy->posY() + enemy->height() >= HEIGHT)
    return (true);
  enemy->speedY(action.speed);
  FCommand::sendToAll(game, FCommand::move(enemy), NULL);
  return (true);
}

bool			FCommand::_left(Enemy *enemy, Game *game, const uAction &action)
{
  if (action.speed >= 0 ||
      enemy->speedX() == action.speed ||
      enemy->posX() - enemy->width() <= 0)
    return (true);
  enemy->speedX(action.speed);
  FCommand::sendToAll(game, FCommand::move(enemy), NULL);
  return (true);
}

bool			FCommand::_right(Enemy *enemy, Game *game, const uAction &action)
{
  if (action.speed <= 0 ||
      enemy->speedX() == action.speed ||
      enemy->posX() + enemy->width() >= WIDTH)
    return (true);
  enemy->speedX(action.speed);
 FCommand::sendToAll(game, FCommand::move(enemy), NULL);
  return (true);
}

bool			FCommand::_stopX(Enemy *enemy, Game *game, const uAction &action)
{
  if (action.speed != 0 ||
      enemy->speedX() == 0)
    return (true);
  enemy->speedX(0);
  FCommand::sendToAll(game, FCommand::move(enemy), NULL);
  return (true);
}

bool			FCommand::_stopY(Enemy *enemy, Game *game, const uAction &action)
{
  if (action.speed != 0 ||
      enemy->speedY() == 0)
    return (true);
  enemy->speedY(0);
  FCommand::sendToAll(game, FCommand::move(enemy), NULL);
  return (true);
}

bool			FCommand::_shoot(Enemy *enemy, Game *game, const uAction &action)
{
  AShoot		*shoot;

  (void)action;
  shoot = new EnemyShoot(enemy->posX(), enemy->posY(), game->newIdShoot(), enemy->id());
  game->addShoot(shoot);
  FCommand::sendToAll(game, FCommand::shoot(shoot), NULL);
  return (true);
}

bool			FCommand::_suicide(Enemy *enemy, Game *game, const uAction &action)
{
  (void)action;
  FCommand::sendToAll(game, FCommand::destroy(enemy), NULL);
  return (false);
}

bool			FCommand::_nothing(Enemy *enemy, Game *game, const uAction &action)
{
  (void)action;
  (void)enemy;
  (void)game;
  return (true);
}

bool			FCommand::handlePacket(Client *clt, const t_pkt &packet, Game *game)
{
  bool			ret;

  ret = true;
  try
    {
      ret = (this->*_commands.at(packet.key))(clt, packet, game);
    }
  catch (std::out_of_range &err)
    {
      (void)err;
    }
  if (ret == false)
    FCommand::sendToAll(game, FCommand::leave(clt), clt);
  return (ret);
}

bool			FCommand::handleEnemy(Enemy *enemy, Game *game, const eAction &action, const uAction &arg)
{
  try
    {
      return ((this->*_actions.at(action))(enemy, game, arg));
    }
  catch (std::out_of_range &err)
    {
      (void)err;
    }
  return (true);
}

bool			FCommand::sendToAll(Game *game, const t_pkt &packet, const Client *clt)
{
  std::list<Client *>	clients;
  std::list<Client *>::iterator	it;

  clients = game->getPlayers();
  it = clients.begin();
  while (it != clients.end())
    {
      if (*it != clt)
	(*it)->lock();
      if (!(*it)->isClosed() && (*it)->getSocket() != NULL)
	(*it)->getSocket()->Send(packet);
      if (*it != clt)
	(*it)->unlock();
      ++it;
    }
  return (true);
}

t_pkt			FCommand::leave(const Entity *entity)
{
  t_pkt			packet;

  packet.key = 11;
  memcpy(packet.args, &(entity->id()), sizeof(int));
  packet.argLength = sizeof(int);
  return (packet);
}

t_pkt			FCommand::move(const Entity *entity)
{
  t_pkt			packet;

  packet.key = 7;
  memcpy(packet.args, &(entity->id()), sizeof(int));
  memcpy(packet.args + sizeof(int), &(entity->posX()), sizeof(int));
  memcpy(packet.args + 2 * sizeof(int), &(entity->posY()), sizeof(int));
  memcpy(packet.args + 3 * sizeof(int), &(entity->speedX()), sizeof(int));
  memcpy(packet.args + 4 * sizeof(int), &(entity->speedY()), sizeof(int));
  packet.argLength = 5 * sizeof(int);
  return (packet);
}

t_pkt			FCommand::shoot(const AShoot *shoot)
{
  t_pkt			packet;
  eShoot		shootType;

  shootType = shoot->getType();
  packet.key = 9;
  memcpy(packet.args, &(shoot->id()), sizeof(int));
  memcpy(packet.args + 1 * sizeof(int), &shoot->owner(), sizeof(int));
  memcpy(packet.args + 2 * sizeof(int), &shootType, sizeof(int));
  memcpy(packet.args + 3 * sizeof(int), &(shoot->posX()), sizeof(int));
  memcpy(packet.args + 4 * sizeof(int), &(shoot->posY()), sizeof(int));
  memcpy(packet.args + 5 * sizeof(int), &(shoot->speedX()), sizeof(int));
  memcpy(packet.args + 6 * sizeof(int), &(shoot->speedY()), sizeof(int));
  packet.argLength = 7 * sizeof(int);
  return (packet);
}

t_pkt			FCommand::destroy(const Entity *entity)
{
  t_pkt			packet;

  packet.key = 10;
  memcpy(packet.args, &(entity->id()), sizeof(int));
  packet.argLength = sizeof(int);
  return (packet);
}

t_pkt			FCommand::health(const Creature *creature)
{
  t_pkt			packet;

  packet.key = 12;
  memcpy(packet.args, &(creature->id()), sizeof(int));
  memcpy(packet.args + sizeof(int), &(creature->health()), sizeof(int));
  packet.argLength = 2 * sizeof(int);
  return (packet);
}

t_pkt			FCommand::pop(const Creature *creature, const eCreature &type)
{
  t_pkt			packet;

  packet.key = 13;
  memcpy(packet.args, &(creature->id()), sizeof(int));
  memcpy(packet.args + sizeof(int), &type, sizeof(int));
  memcpy(packet.args + 2 * sizeof(int), &(creature->health()), sizeof(int));
  memcpy(packet.args + 3 * sizeof(int), &(creature->posX()), sizeof(int));
  memcpy(packet.args + 4 * sizeof(int), &(creature->posY()), sizeof(int));
  packet.argLength = 5 * sizeof(int);
  return (packet);
}

t_pkt			FCommand::endGame()
{
  t_pkt			packet;

  packet.key = 17;
  packet.argLength = 0;
  return (packet);
}
