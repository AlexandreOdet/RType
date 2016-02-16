#include "Eeye.hh"


#include "Eredship.hh"


Eeye::Eeye(sf::Vector2f const v, int const id, int const health) : Object(v.x, v.y, id, health)
{
	_type = "eeye";
	_t_obj = imageManager["Eeye"];
	_s_obj.setTexture(_t_obj);
	_xsize = 17;
	_ysize = 14;
	_nbanime = 4;
	_s = 0;
	_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize * (_s + 1), _ysize));
}


Eeye::~Eeye()
{
}

void	Eeye::update()
{
	Object::update();
	if (_s == _nbanime)
		_s = 0;
	if (_clock.getElapsedTime().asMilliseconds() >= 200)
	{
		_clock.restart();
		_s += 1;
	}
	_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize, _ysize));
	_s_obj.setScale(3, 3);
}
