//
// GameHeader.hh for GameHeader in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Mon Dec  7 03:25:21 2015 Thibaut Lopez
// Last update Wed Dec 30 14:38:16 2015 Thibaut Lopez
//

#ifndef	GAMEHEADER_HH
#define	GAMEHEADER_HH

#define	WIDTH		(1280)
#define	HEIGHT		(800)
#define	PLAYER_SPEEDX	(10)
#define	PLAYER_SPEEDY	(10)
#define	SHOOT_HEIGHT	(0)
#define SHOOT_WIDTH	(0)
#define	SHOOT_SPEEDX	(15)
#define	SHOOT_SPEEDY	(0)
#define	COLLISION_DAM	(34)
#define	SCROLLER	(-2)

enum			eAction
  {
    GOUP,
    GODOWN,
    GOLEFT,
    GORIGHT,
    GOSTOPX,
    GOSTOPY,
    SHOOT,
    SUICIDE,
    NOTHING,
    BLINK
  };

enum			eDirection
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOPX,
    STOPY,
    STAND
  };

enum			eShoot
  {
    NORMAL,
    MEDIUM,
    LONGS,
    ENEMY
  };

enum			eCreature
  {
    PLAYER1 = 0,
    PLAYER2 = 1,
    PLAYER3 = 2,
    PLAYER4 = 3,
    ZIPP,
    SATELLITE,
    MANX,
    BAGUT,
    BYDO
  };

#endif
