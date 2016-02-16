#include "ConnectMenu.hh"
#include "client.hh"
#include <iostream>

ConnectMenu::ConnectMenu(client *cli) : _cli(cli)
{
  this->string = "";
  this->portString = "";
  this->_printMsg = false;
  this->initRes();
  this->initRectangles();
}

ConnectMenu::~ConnectMenu()
{
}

void  ConnectMenu::printMessage(const bool & haveToPrint)
{
  this->_printMsg = haveToPrint;
}

void ConnectMenu::printWindow(sf::RenderWindow &_window)
{
  _window.draw(this->_sprite);
  _window.draw(this->_rectangleIP);
  _window.draw(this->_rectanglePort);
  _window.draw(this->_text);
  _window.draw(this->_ipText);
  _window.draw(this->_portText);
  this->_cursor->makeItBlink();
  _window.draw(this->_cursor->getRectangle());
  _window.draw(this->_port);
  if (this->_printMsg)
    _window.draw(this->_errorMsg);
}

void ConnectMenu::initRectangles()
{
  this->_rectangleIP.setSize(sf::Vector2f(500, 100));
  this->_rectangleIP.setFillColor(sf::Color(255, 255, 255));
  this->_rectangleIP.setPosition(50, 900);
  this->_rectangleIP.setOutlineThickness(10);
  this->_rectangleIP.setOutlineColor(sf::Color(0, 0, 0));

  this->_cursor = new Cursor(130, 925);

  this->_rectanglePort.setSize(sf::Vector2f(500, 100));
  this->_rectanglePort.setFillColor(sf::Color(255, 255, 255));
  this->_rectanglePort.setPosition(1250, 900);
  this->_rectanglePort.setOutlineThickness(10);
  this->_rectanglePort.setOutlineColor(sf::Color(0, 0, 0));
}

void ConnectMenu::initRes()
{
  this->_img = imageManager["bg"];
  this->_font = fontManager["default"];

  this->_sprite.setTexture(this->_img);

  this->_text.setString(" ");
  this->_text.setFont(this->_font);
  this->_text.setStyle(sf::Text::Regular);
  this->_text.setCharacterSize(50);
  this->_text.setColor(sf::Color::Black);
  this->_text.setPosition(135, 915);

  this->_port.setString(" ");
  this->_port.setFont(this->_font);
  this->_port.setStyle(sf::Text::Regular);
  this->_port.setCharacterSize(50);
  this->_port.setColor(sf::Color::Black);
  this->_port.setPosition(1420, 915);

  this->_ipText.setString("IP :");
  this->_ipText.setFont(this->_font);
  this->_ipText.setStyle(sf::Text::Regular);
  this->_ipText.setCharacterSize(50);
  this->_ipText.setColor(sf::Color::Black);
  this->_ipText.setPosition(60, 915);

  this->_portText.setString("Port :");
  this->_portText.setFont(this->_font);
  this->_portText.setStyle(sf::Text::Regular);
  this->_portText.setCharacterSize(50);
  this->_portText.setColor(sf::Color::Black);
  this->_portText.setPosition(1270, 915);

  this->_errorMsg.setString("Unable to reach the server");
  this->_errorMsg.setFont(this->_font);
  this->_errorMsg.setStyle(sf::Text::Regular);
  this->_errorMsg.setCharacterSize(50);
  this->_errorMsg.setColor(sf::Color::Red);
  this->_errorMsg.setPosition(630, 100);
}

void ConnectMenu::connectTo()
{
  this->_cli->setNetwork(this->string, this->portString);
}

void ConnectMenu::HandleKeyBoard(sf::Event &_event)
{
  if ((_event.key.code >= sf::Keyboard::Num0 && _event.key.code <= sf::Keyboard::Num9))
  {
     if (this->_cursor->isOnIp() == true)
     {
       if (this->string.length() < 15)
       {
         this->string += std::to_string (_event.key.code - 26);
         this->_text.setString(this->string);
         this->_cursor->moveCursor(this->_cursor->getPosX() + 25, this->_cursor->getPosY());
       }
    }
    else
    {
      if (this->portString.length() < 6)
      {
        this->portString += std::to_string(_event.key.code - 75);
        this->_port.setString(portString);
        this->_cursor->moveCursor(this->_cursor->getPosX() + 30, this->_cursor->getPosY());
      }
    }
  }
  else if ((_event.key.code >= sf::Keyboard::Numpad0 && _event.key.code <= sf::Keyboard::Numpad9))
  {
    if (this->_cursor->isOnIp() == true)
    {
      if (this->string.length() < 15)
      {
        this->string += std::to_string(_event.key.code - 75);
        this->_text.setString(this->string);
        this->_cursor->moveCursor(this->_cursor->getPosX() + 25, this->_cursor->getPosY());
      }
    }
    else
    {
      if (this->portString.length() < 6)
      {
        this->portString += std::to_string(_event.key.code - 75);
        this->_port.setString(portString);
        this->_cursor->moveCursor(this->_cursor->getPosX() + 30, this->_cursor->getPosY());
      }
    }
  }
  if (_event.key.code == sf::Keyboard::Period)
  {
    if (this->_cursor->isOnIp() == true)
    {
      this->string += ".";
      this->_text.setString(this->string);
      this->_cursor->moveCursor(this->_cursor->getPosX() + 15, this->_cursor->getPosY());
    }
  }
  if (_event.key.code == sf::Keyboard::BackSpace)
  {
    if (this->_cursor->isOnIp() == true)
    {
      if (string.length() > 0)
      {
        if (this->string[string.length() - 1] == '.')
          this->_cursor->moveCursor(this->_cursor->getPosX() - 15, this->_cursor->getPosY());
        else
          this->_cursor->moveCursor(this->_cursor->getPosX() - 27, this->_cursor->getPosY());
        this->string.erase(this->string.length() - 1, this->string.length());
        this->_text.setString(this->string);
        if (string.length() == 0)
        {
          this->_cursor->moveCursor(130, 925);
        }
      }
    }
    else
    {
      if (this->portString.length() > 0)
      {
        this->portString.erase(this->portString.length() - 1, this->portString.length());
        this->_port.setString(this->portString);
        this->_cursor->moveCursor(this->_cursor->getPosX() - 28, this->_cursor->getPosY());
      }
    }
  }
  if (_event.key.code == sf::Keyboard::Tab)
  {
    if (this->_cursor->isOnIp() == true)
    {
      this->_cursor->moveCursor(1400, 925);
      if (this->portString.length() > 0)
      this->_cursor->moveCursor(this->_cursor->getPosX() + (30 * this->portString.length()), this->_cursor->getPosY());
    }
    else
    {
      this->_cursor->moveCursor(130, 925);
      if (this->string.length() > 0)
      this->_cursor->moveCursor(this->_cursor->getPosX() + (21 * this->string.length()), this->_cursor->getPosY());
    }
  }
  if (_event.key.code == sf::Keyboard::Return)
  {
    this->connectTo();
  }
}
