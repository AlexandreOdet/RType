#include "Eredship.hh"


Eredship::Eredship(sf::Vector2f const v, int const id, int const health) : Object(v.x, v.y, id, health)
{
	_type = "eredship";
	_t_obj = imageManager["Eredship"];
	_s_obj.setTexture(_t_obj);
	_xsize = 33;
	_ysize = 35;
	_nbanime = 8;
	_s = 0;
	_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize * (_s + 1), _ysize));
}


Eredship::~Eredship()
{
}

void	Eredship::update()
{
	Object::update();
	if (_s == _nbanime)
		_s = 0;
	if (_clock.getElapsedTime().asMilliseconds() >= 170)
	{
		_clock.restart();
		_s += 1;
	}
	_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize, _ysize));
	_s_obj.setScale(3, 3);
}
