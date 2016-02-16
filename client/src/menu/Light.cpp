#include "Light.hh"

Light::Light(const int posX, const int posY, bool isReady)
{
  this->_light.setRadius(15);
  this->_light.setPosition(posX, posY);
  this->_light.setFillColor((isReady) ? sf::Color::Green : sf::Color::Red);
}

Light::~Light(){}

const sf::CircleShape Light::getCircle() const
{
  return this->_light;
}
