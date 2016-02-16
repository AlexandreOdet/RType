#ifndef client_HH
#define client_HH

#include <iostream>
#include <ostream>
#include "Menu.hh"
#include "graphic.hh"
#ifndef _WIN32
#include "LClient.hh"
#else
#include "WClient.hh"
#endif
#include "GameHeader.hh"

#define WIN_WIDTH (1920)
#define WIN_HEIGHT (1080)

#define WidthToWin(x) (((x) / WIDTH) * WIN_WIDTH)
#define HeightToWin(x) (((x) / HEIGHT) * WIN_HEIGHT)

typedef void        (client::*_fct)(int const size, std::string const &);

class client
{
private:
  IClient               *_net;
  Menu                  *_menu;
  graphic               *_game;

  bool                  _loop;
  bool                  _connected;
  bool                  _onMenu;
  std::map<int, _fct>   fctMap;
  std::size_t           _sec;
  std::size_t           _usec;

public:
  client ();
  client (const std::string &ip, std::string const &port); // to remove
  virtual ~client ();

  void  loop();
  void  sendToNetwork(int cmd, std::string const &args);
  void  setNetwork(std::string const &ip, std::string const &port);
  void  quitGame();
  void  parseCmd(t_pkt const &);
  std::string   itos(int const) const;
  int           ctos(std::string const &) const;

private:
  bool  validateIpAddress(const std::string&);

  void  _connect(int const size, std::string const &);
  void  _move(int const size, std::string const &);
  void  _loadShoot(int const size, std::string const &);
  void  _shoot(int const size, std::string const &);
  void  _destroy(int const size, std::string const &);
  void  _Leav(int const size, std::string const &);
  void  _life(int const size, std::string const &);
  void  _pop(int const size, std::string const &);
  void  _updateRooms(int const size, std::string const &);
  void  _updateMap(int const size, std::string const &);
  void  _startGame(int const size, std::string const &);
  void  _stopGame(int const size, std::string const &);
};

#endif
