#ifndef _Light_
#define _Light_

#include <SFML/Graphics.hpp>

class Light
{
public:
  explicit Light(const int, const int, bool);
  ~Light();
  const sf::CircleShape getCircle() const;
private:
  sf::CircleShape _light;
};

#endif
