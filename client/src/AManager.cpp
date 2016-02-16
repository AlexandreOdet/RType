#include "AManager.hh"

std::map<std::string, sf::Texture>     imageManager;
std::map<std::string, sf::Font>        fontManager;

AManager::~AManager()
{
}

void AManager::setGameRessource()
{
  addImage("../ressources/images/shoot1.png", "shoot1");
  addImage("../ressources/images/shoot2.png", "shoot2");
  addImage("../ressources/images/shoot3.png", "shoot3");
  addImage("../ressources/images/EBall.png", "EBall");
  addImage("../ressources/images/Eeye.png", "Eeye");
  addImage("../ressources/images/Eredship.png", "Eredship");
  addImage("../ressources/images/eshoot.png", "eshoot");
  addImage("../ressources/images/background.png", "background");
  addImage("../ressources/images/explode.png", "explode");
  addImage("../ressources/images/nabibi.png", "nabibi");
  addImage("../ressources/images/loadshoot.png", "loadshoot");
  addImage("../ressources/images/Player.png", "Player");
  addImage("../ressources/images/spininglazor.png", "spininglazor");
  addFont("../ressources/fonts/tec.ttf", "tec");
}

void AManager::setMenuRessource()
{
  addImage("../ressources/images/MainBG.jpg", "MainBG");
  addImage("../ressources/images/bg.jpg", "bg");
  addImage("../ressources/images/r_type-logo.png", "rtype_logo");
  addImage("../ressources/images/highlight.png", "highlight");
  addImage("../ressources/images/earth.png", "earth");
  addFont("../ressources/fonts/font.ttf", "default");
  addFont("../ressources/fonts/spaceage.ttf", "spaceage");
  addFont("../ressources/fonts/Android.ttf", "Android");
}

void AManager::addFont(std::string const &path, std::string const &name)
{
  sf::Font font;
  if (!font.loadFromFile(path))
  throw FileError("font", path);
  fontManager.insert(std::pair<std::string, sf::Font>(name, font));
}

void AManager::addImage(std::string const &path, std::string const &name)
{
  sf::Texture texture;
  if (!texture.loadFromFile(path))
    throw FileError("image", path);
  imageManager.insert(std::pair<std::string, sf::Texture>(name, texture));
}

sf::Font        AManager::getFont(std::string const &name) const
{
  sf::Font ret;

  std::map<std::string, sf::Font>::iterator it = fontManager.find(name);
  if (it != fontManager.end())
    ret = (fontManager[name]);
  else
    throw FileError("font", name);
  return (ret);
}

sf::Texture     AManager::getImage(std::string const &name) const
{
  sf::Texture ret;

  std::map<std::string, sf::Texture>::iterator it = imageManager.find(name);
  if (it != imageManager.end())
    ret = (imageManager[name]);
  else
    throw FileError("image", name);
  return ret;
}
