#ifndef	ROOM_HH
#define	ROOM_HH

#include "Game.hpp"

class	Room
{
  std::size_t		_id;
  Game			_game;

public:
  explicit Room(const std::size_t &);
  virtual ~Room();

  const std::size_t	&getId() const;
  bool			addPlayer(Client *);
  bool			deletePlayer(Client *);
  std::size_t		getPlayersNumber() const;
  const std::list<Client *> & getPlayers() const;
  bool			needToBeFreed();
  void			loop();
};

#endif
