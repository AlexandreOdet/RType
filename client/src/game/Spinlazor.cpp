#include "Spinlazor.hh"


Spinlazor::Spinlazor(sf::Vector2f const v, int const id, int const health) : Object(v.x, v.y, id, health)
{
	_type = "spinlazor";
	_t_obj = imageManager["spininglazor"];
	_s_obj.setTexture(_t_obj);
	_xsize = 61;
	_ysize = 32;
	_nbanime = 4;
	_s = 0;

	_vecteur.x = 1;
	_vecteur.y = 0;
}


Spinlazor::~Spinlazor()
{
}


void		Spinlazor::update()
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
	_s_obj.setScale(1, 1);
}
