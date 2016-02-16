#include "Eball.hh"


Eball::Eball(sf::Vector2f const v, int const id, int const health) : Object(v.x, v.y , id, health)
{
	_type = "eball";
	_t_obj = imageManager["EBall"];
	_s_obj.setTexture(_t_obj);
	_xsize = 17;
	_ysize = 18;
	_nbanime = 12;
	_s = 0;
	_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize * (_s + 1), _ysize));
}


Eball::~Eball()
{
}

void	Eball::update()
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
