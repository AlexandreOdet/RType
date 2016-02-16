#include "InsertCoin.hh"

static int g_callBlink = 0;

InsertCoin::InsertCoin(sf::Font spaceFont, const int x, const int y)
{
  this->_posX = x;
  this->_posY = y;
  this->_font = spaceFont;
  this->_text.setString("INSERT COINS");
  this->_text.setFont(this->_font);
  this->_text.setCharacterSize(100);
  this->_isPrinted = true;
  this->_text.setColor(sf::Color::White);
  this->_text.setPosition(x, y);
}

InsertCoin::~InsertCoin()
{}

sf::Text const InsertCoin::getText() const
{
  return this->_text;
}

void InsertCoin::makeItBlink()
{
  if (g_callBlink % 60 == 0)
  {
    if (this->_isPrinted == true)
    {
      this->_text.setColor(sf::Color::Black);
      this->_isPrinted = false;
    }
    else
    {
      this->_text.setColor(sf::Color::White);
      this->_isPrinted = true;
    }
  }
  g_callBlink++;
}
