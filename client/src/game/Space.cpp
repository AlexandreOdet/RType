#include "Space.hh"
#include <iostream>

Space::Space()
{
	_x = 0;
	_t_background = imageManager["background"];

	_s_background.setTexture(_t_background);
	_s_background.setPosition(0, 0);
}


Space::~Space()
{
}

void	Space::update()
{
	if (_x < 1920)
		_x += float(0.8);
	_s_background.setTextureRect(sf::IntRect((int)_x, 0, 1920 + (int)_x, 1080));
}

void	Space::display(sf::RenderWindow *w)
{
	w->draw(_s_background);
}
