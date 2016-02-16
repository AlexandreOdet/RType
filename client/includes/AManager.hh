#ifndef	AMANAGER_HH
#define	AMANAGER_HH

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "CException.hpp"

extern std::map<std::string, sf::Texture>     imageManager;
extern std::map<std::string, sf::Font>        fontManager;

class	AManager
{
public:
  virtual ~AManager();

  void            setGameRessource();
  void            setMenuRessource();
  void            addFont(std::string const &path, std::string const &name);
  void            addImage(std::string const &path, std::string const &name);
  sf::Font        getFont(std::string const &) const;
  sf::Texture     getImage(std::string const &) const;
};

#endif
