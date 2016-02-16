//
// Stage.hh for Stage in /home/lopez_t/rtype/server
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Fri Dec 18 16:28:27 2015 Thibaut Lopez
// Last update Tue Dec 29 16:54:59 2015 Thibaut Lopez
//

#ifndef	STAGE_HH
#define	STAGE_HH

#include "MapParser.hh"
#include "Wall.hh"
#include <list>
#include <stdlib.h>

class	Enemy;

class	Game;

class	Stage : public MapParser
{
private:
  int		_frameCount;
  bool		_isLoaded;
  Map::iterator	_pos;
  void		_loadBasicMap();
  void		_harmoniseRandomEncounter();

public:
  explicit Stage();
  virtual ~Stage();
  void		loadStage(const std::string & = "");
  bool		update(Game *);
};

#include "Game.hpp"

#endif
