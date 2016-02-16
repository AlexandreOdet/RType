#include "Cursor.hh"

static int blink = 0;

Cursor::Cursor(const int x, const int y)
{
  if (x == 130 && y == 925)
    this->_isOnIp = true;
  else
    this->_isOnIp = false;
  this->posX = x;
  this->posY = y;
  this->sizeX = 5;
  this->sizeY = 40;
  this->_cursor.setSize(sf::Vector2f(sizeX, sizeY));
  this->_cursor.setFillColor(sf::Color(0, 0, 0));
  this->_cursor.setPosition(x, y);
  this->_isBlack = true;
}

Cursor::~Cursor()
{

}

void Cursor::moveCursor(const int x, const int y)
{
  if (x >= 130 && x <= (130 + 500) && y == 925)
    this->_isOnIp = true;
  else
    this->_isOnIp = false;
  this->posX = x;
  this->posY = y;
  this->_cursor.setPosition(x, y);
}

void Cursor::makeItBlink()
{
  if (blink % 30 == 0)
  {
    if (this->_isBlack == true)
    {
      this->_isBlack = false;
      this->_cursor.setFillColor(sf::Color(255, 255, 255));
    }
    else
    {
      this->_isBlack = true;
      this->_cursor.setFillColor(sf::Color(0, 0, 0));
    }
  }
  blink++;
}

sf::RectangleShape const Cursor::getRectangle() const
{
  return this->_cursor;
}

bool Cursor::isOnIp() const
{
  return this->_isOnIp;
}

int Cursor::getPosX() const
{
  return this->posX;
}

int Cursor::getPosY() const
{
  return this->posY;
}
