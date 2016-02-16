#ifndef __HUD_H__
#define __HUD_H__

#include <SFML/Graphics.hpp>
#include "AManager.hh"

class HUD
{
public:
	HUD();
	~HUD();

	void	update(int const score, int const life, int const charge);
	void	display(sf::RenderWindow *w);

private:
	sf::Font	_font;
	sf::Color	_blue;


	std::string _s;
	std::string _l;
	std::string	_b;
	sf::Text	_beam;
	sf::Text	_life;
	sf::Text	_score;
};

#endif
