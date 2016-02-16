#ifndef __SPACE_H__
#define __SPACE_H__

#include <SFML/Graphics.hpp>
#include "AManager.hh"

class Space
{
public:
	Space();
	~Space();

	void display(sf::RenderWindow *w);
	void update();


protected:
	sf::Texture _t_background;
	sf::Sprite  _s_background;
	float		_x;
};


#endif
