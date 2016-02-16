#include "Explode.hh"

Explode::Explode(sf::Vector2f const pos)
{
	Sound::instance()->play("explose");
	_end = false;
	_t = imageManager["explode"];
	_s.setTexture(_t);
	_s.setScale(3, 3);
	_s.setPosition(pos);
}


Explode::~Explode()
{
}

void		Explode::update()
{
	if (_clock.getElapsedTime().asMilliseconds() < 100)
		_s.setTextureRect(sf::IntRect(0, 0, 31, 29));
	if (_clock.getElapsedTime().asMilliseconds() > 100 && _clock.getElapsedTime().asMilliseconds() < 200)
		_s.setTextureRect(sf::IntRect(31 * 1, 0, 31, 29));
	if (_clock.getElapsedTime().asMilliseconds() > 200 && _clock.getElapsedTime().asMilliseconds() < 300)
		_s.setTextureRect(sf::IntRect(31 * 2, 0, 31, 29));
	if (_clock.getElapsedTime().asMilliseconds() > 300 && _clock.getElapsedTime().asMilliseconds() < 400)
		_s.setTextureRect(sf::IntRect(31 * 3, 0, 31, 29));
	if (_clock.getElapsedTime().asMilliseconds() > 400)
		_end = true;
}


bool		Explode::getEnd() const
{
	return _end;
}

void		Explode::display(sf::RenderWindow *w) const
{
	w->draw(_s);
}
