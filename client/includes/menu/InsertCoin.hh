#ifndef __INSERTCOIN__
#define __INSERTCOIN__

#include <SFML/Graphics.hpp>

#include <iostream>

class InsertCoin
{
public:
  InsertCoin(sf::Font, const int, const int);
  ~InsertCoin();
  void makeItBlink();
  sf::Text const getText() const;

private:
  int _posX;
  int _posY;
  sf::Text _text;
  sf::Font _font;
  bool _isPrinted;
};

#endif /*__INSERTCOIN__*/
