#ifndef _readyLighter_
#define _readyLighter_

#include <list>
#include <SFML/Graphics.hpp>
#include "Light.hh"

class readyLighter
{
  public:
    explicit readyLighter(const int, const int, const std::size_t);
    ~readyLighter();
    void updateLights(const int);
    void printLights(sf::RenderWindow &) const;
  private:
  std::list<Light*> _fires;
  int _posX;
  int _posY;
  int _saveX;
};

#endif
