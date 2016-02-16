#include "readyLighter.hh"

readyLighter::readyLighter(const int posX, const int posY, const std::size_t nbReady)
{
  this->_saveX = posX;
  this->_posX = posX;
  this->_posY = posY;
  for (int i = 0; i < 4; i++)
  {
    this->_fires.push_back(new Light(this->_posX, posY, (i < (int)nbReady) ? true : false));
    this->_posX += 40;
  }
}

readyLighter::~readyLighter(){}

void readyLighter::updateLights(const int newNbReady)
{
  this->_posX = this->_saveX;
  this->_fires.resize(1);
  for (int i = 0; i < 4; i++)
  {
    this->_fires.push_back(new Light(this->_posX, this->_posY, (i < newNbReady) ? true : false));
    this->_posX += 40;
  }
}
void readyLighter::printLights(sf::RenderWindow &window) const
{
  for (std::list<Light*>::const_iterator it = this->_fires.begin(); it != this->_fires.end(); ++it)
    window.draw((*it)->getCircle());
}
