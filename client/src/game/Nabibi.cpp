#include "Nabibi.hh"

Nabibi::Nabibi(sf::Vector2f const v, int const id, int const health) : Object(v.x, v.y, id, health)
{
	_type = "nabibi";
	_def = true;
	_t_obj = imageManager["nabibi"];
	_s_obj.setTexture(_t_obj);
	_xsize = 63;
	_ysize = 67;
	_nbanime = 5;
	_s = 0;
	_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize, _ysize));
}

Nabibi::~Nabibi()
{
}

void						Nabibi::changeStand()
{
	if	(_clock.getElapsedTime().asMilliseconds() >= 50)
		_def = !_def;
	_clock.restart();
}

std::vector<Object *>		Nabibi::Waveshoot() const
{
	std::vector<Object *>	tmp;
	int i = 0;
	double x[] = { -0.64, 0.81, -0.93, -0.22, -0.02, -0.98 };
	double y[] = { 0.76, -0.57, 0.35, -0.9, 0.99, -0.15 };
	while (i < 6)
	{
		tmp.push_back(new Eshoot(_pos, 0, sf::Vector2f(float(x[i]), float(y[i]))));
		i += 1;
	}
	return tmp;
}

void						Nabibi::update()
{
	Object::update();
	if (_def == false)
	{
		if (_clock.getElapsedTime().asMilliseconds() >= 800)
		{
			_clock.restart();
			if (_s == 0)
				_s += 1;
			else
			_s -= 1;
			_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize, _ysize));
		}
	}
	if (_def == true && _s < 4)
	{
		if (_clock.getElapsedTime().asMilliseconds() >= 800)
		{
			_clock.restart();
			_s += 1;
			_s_obj.setTextureRect(sf::IntRect(_xsize * _s, 0, _xsize, _ysize));
		}
	}
	_s_obj.setScale(5, 5);
}
