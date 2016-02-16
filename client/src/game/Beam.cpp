#include "Beam.hh"

Beam::Beam(sf::Vector2f const p, int const pow, int const id, float const speed) : Object(p.x, p.y, id, 1)
{
	Sound::instance()->play("beam");
	_pow = pow;
	_type = "shoot";
	_t_obj = imageManager["shoot1"];
	_s_obj.setTexture(_t_obj);

	_xsize = 16;
	_ysize = 12;

	_t_medium = imageManager["shoot2"];
	_s_medium.setTexture(_t_medium);
	_s_medium.setPosition(p);

	_t_strong = imageManager["shoot3"];
	_s_strong.setTexture(_t_strong);
	_s_strong.setPosition(p);

	_nbanime = 2;
	_s = 0;
	_vecteur.x = speed;
	_vecteur.y = 0;
}


Beam::~Beam()
{
}


void		Beam::rotate(float const r)
{
	_s_medium.setRotation(r);
	_s_obj.setRotation(r);
	_s_strong.setRotation(r);
}

void		Beam::update()
{
	Object::update();
	if (_s == _nbanime)
		_s = 0;
	if (_clock.getElapsedTime().asMilliseconds() >= 100)
	{
		_clock.restart();
		_s += 1;
	}
	if (_pow < 5)
	{
		_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize, _ysize));
		_s_obj.setScale(2, 2);
	}
	if (_pow > 5 && _pow < 15)
	{
		_s_medium.setPosition(_pos);
		_s_medium.setTextureRect(sf::IntRect(34 * _s, 0, 34, 12));
		_s_medium.setScale(2, 2);
	}
	if (_pow >= 15)
	{
		_s_strong.setPosition(_pos);
		_s_strong.setTextureRect(sf::IntRect(64 * _s, 0, 64, 14));
		_s_strong.setScale(2, 2);
	}
}

void		Beam::display(sf::RenderWindow *w)
{
	if (_pow < 5)
		w->draw(_s_obj);
	if (_pow > 5 && _pow < 15)
		w->draw(_s_medium);
	if (_pow > 15)
		w->draw(_s_strong);
}
