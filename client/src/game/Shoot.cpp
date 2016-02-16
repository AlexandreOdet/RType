#include "Shoot.hh"


Shoot::Shoot(sf::Vector2f const v, int const id) : Object(v.x, v.y, id, 1)
{
	_xsize = 29;
	_ysize = 25;
	_nbanime = 5;
	_s = 0;
	_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize * (_s + 1), _ysize));
}


Shoot::~Shoot()
{
}

void	Shoot::update()
{
	_s_obj.setPosition(_pos);
}
