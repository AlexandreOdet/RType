#ifndef _MenuRTYPE_
#define _MenuRTYPE_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ConnectMenu.hh"
#include "IGraphic.hh"
#include "AManager.hh"
#include "MainWindow.hh"

#define FPS (60)

class client;

class Menu : public IGraphic
{
public:
  Menu(client *cli);
  ~Menu();

  bool handleEvent();
  void setConnected(bool const);
  void printWindow();

  ConnectMenu   *getConnectMenu();
  MainWindow    *getRoomMenu();

private:
  bool              isConnected;
  AManager          _res;
  ConnectMenu       *_connect;
  MainWindow        *_rooms;
  client            *_cli;

  sf::RenderWindow  _window;
  sf::Event         _event;

  std::map<int, void (Menu::*)()> mapEvent;
  void	(Menu::*ptr)();

  void closeApp();
  void HandleKeyBoard();
};

#endif /*_MenuRTYPE_*/
