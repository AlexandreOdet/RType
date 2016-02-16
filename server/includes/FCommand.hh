//
// FCommand.hh for FCommand in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 08 14:55:01 2015 Thibaut Lopez
// Last update Sat Jan  2 18:37:20 2016 Thibaut Lopez
//

#ifndef	FCOMMAND_HH
#define	FCOMMAND_HH

#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include "ISocket.hh"
#include "Client.hh"
#include "EnemyShoot.hh"

class	Game;

class	Enemy;

union	uAction;

class	FCommand
{
private:
  typedef bool			(FCommand::*s_func)(Client *, const t_pkt &, Game *);
  std::map<int, s_func>		_commands;
  typedef bool			(FCommand::*s_move)(Client *);
  std::map<eDirection, s_move>	_moves;
  typedef bool			(FCommand::*s_act)(Enemy *, Game *, const uAction &);
  std::map<eAction, s_act>	_actions;
  bool				_disconnect(Client *, const t_pkt &, Game *);
  bool				_leaveRoom(Client *, const t_pkt &, Game *);
  bool				_moveUp(Client *);
  bool				_moveDown(Client *);
  bool				_moveLeft(Client *);
  bool				_moveRight(Client *);
  bool				_moveStopX(Client *);
  bool				_moveStopY(Client *);
  bool				_move(Client *, const t_pkt &, Game *);
  bool				_loadShoot(Client *, const t_pkt &, Game *);
  bool				_shoot(Client *, const t_pkt &, Game *);
  bool				_ping(Client *, const t_pkt &, Game *);
  bool				_up(Enemy *, Game *, const uAction &);
  bool				_down(Enemy *, Game *, const uAction &);
  bool				_left(Enemy *, Game *, const uAction &);
  bool				_right(Enemy *, Game *, const uAction &);
  bool				_stopX(Enemy *, Game *, const uAction &);
  bool				_stopY(Enemy *, Game *, const uAction &);
  bool				_shoot(Enemy *, Game *, const uAction &);
  bool				_suicide(Enemy *, Game *, const uAction &);
  bool				_nothing(Enemy *, Game *, const uAction &);

public:
  FCommand();
  virtual ~FCommand();
  bool				handlePacket(Client *, const t_pkt &, Game *);
  bool				handleEnemy(Enemy *, Game *, const eAction &, const uAction &);
  static bool			sendToAll(Game *, const t_pkt &, const Client *);
  static t_pkt			leave(const Entity *);
  static t_pkt			move(const Entity *);
  static t_pkt			shoot(const AShoot *);
  static t_pkt			health(const Creature *);
  static t_pkt			destroy(const Entity *);
  static t_pkt			pop(const Creature *, const eCreature &);
  static t_pkt			endGame();
};

#include "Enemy.hh"

#endif
