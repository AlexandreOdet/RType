#include "Player.hh"


Player::Player(int const x, int const y, int const id, int const health) : Object(x, y , id, health)
{
	_type = "player";
	_t_load = imageManager["loadshoot"];
	_s_load.setTexture(_t_load);
	_s_load.setOrigin(0, 13);
	_s2 = 0;

	_t_obj = imageManager["Player"];
	_s_obj.setTexture(_t_obj);
	_s_obj.setOrigin(16, 6);
	_xsize = 32;
	_ysize = 12;
	_nbanime = 5;
	_s = 2;
	_pos = sf::Vector2f(x, y);
	_active = false;
}


Player::~Player()
{
}


void	Player::activeShoot()
{
	_active = true;
}

void	Player::disableShoot()
{
	_active = false;
}

void	Player::update()
{
	Object::update();
	if (_state == STAND)
	{
		_clock.restart();
		_s = 2;
	}
	if (_state == UP)
	{
		_s = 4;
		if (_clock.getElapsedTime().asMilliseconds() <= 250)
			_s = 3;
	}
	if (_state == DOWN)
	{
		_s = 0;
		if (_clock.getElapsedTime().asMilliseconds() <= 250)
			_s = 1;
	}
	_s_obj.setTextureRect(sf::IntRect(_xsize * _s, _id * _ysize, _xsize, _ysize));
	_s_obj.setScale(3, 3);
	_s_obj.setPosition(_pos);
	if (_active == true)
	{
		if (_s2 == 5)
			_s2 = 0;
		if (_clock2.getElapsedTime().asMilliseconds() >= 100)
		{
			_clock2.restart();
			_s2 += 1;
		}
		_s_load.setTextureRect(sf::IntRect(29 * _s2, 0, 29, 25));
		_s_load.setScale(3, 3);
		_s_load.setPosition(_pos);
	}
}

void	Player::display(sf::RenderWindow *w)
{
	Object::display(w);
	if (_active == true)
		w->draw(_s_load);
}
