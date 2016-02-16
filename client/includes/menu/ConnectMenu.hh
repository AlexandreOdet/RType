#ifndef _ConnectRTYPE_
#define _ConnectRTYPE_

#include <SFML/Graphics.hpp>
#include <map>
#include <sstream>
#include "Cursor.hh"
#include "AManager.hh"

class client;

class ConnectMenu
{
public:
  ConnectMenu(client *cli);
  ~ConnectMenu();

  void HandleKeyBoard(sf::Event &event);
  void printWindow(sf::RenderWindow &);

void  printMessage(const bool & );

private:
  sf::Text            _text;
  sf::Text            _port;
  sf::Text            _ipText;
  sf::Text            _portText;
  sf::Text            _errorMsg;
  sf::Font            _font;
  sf::Texture         _img;
  sf::Sprite          _sprite;

  std::string         string;
  std::string         portString;

  bool                _printMsg;

  sf::RectangleShape  _rectangleIP;
  sf::RectangleShape  _rectanglePort;
  Cursor              *_cursor;
  client              *_cli;

  void initRectangles();
  void initRes();
  void connectTo();
  void closeApp();
};

#endif /*_ConnectRTYPE_*/
