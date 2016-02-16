#ifndef __CURSOR__
#define __CURSOR__

#include <SFML/Graphics.hpp>

class Cursor
{
public:
  explicit Cursor(const int, const int);
  ~Cursor();
  void moveCursor(const int, const int);
  sf::RectangleShape const getRectangle() const;
  void makeItBlink();
  bool isOnIp() const;
  int getPosX() const;
  int getPosY() const;

private:
  sf::RectangleShape _cursor;
  int sizeX;
  int sizeY;
  int posX;
  int posY;
  bool _isBlack;
  bool _isOnIp;
};

#endif /*__CURSOR__*/
