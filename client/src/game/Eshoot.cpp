#include "Eshoot.hh"


Eshoot::Eshoot(sf::Vector2f const p, int const id, sf::Vector2f const v) : Object(p.x, p.y, id, 1)
{
	_type = "eshoot";
	_t_obj = imageManager["eshoot"];
	_s_obj.setTexture(_t_obj);
	_xsize = 17;
	_ysize = 16;
	_nbanime = 4;
	_s = 0;
	_vecteur = v;
}


Eshoot::~Eshoot()
{
}

void		Eshoot::update()
{
	Object::update();
	if (_s == _nbanime)
		_s = 0;
	if (_clock.getElapsedTime().asMilliseconds() >= 100)
	{
		_clock.restart();
		_s += 1;
	}
	_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize, _ysize));
	_s_obj.setScale(3, 3);
}
