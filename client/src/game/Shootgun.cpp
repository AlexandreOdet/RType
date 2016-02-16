#include "Shootgun.hh"


Shootgun::Shootgun(sf::Vector2f const p, int const pow, int const id, float const speed) : Object(p.x, p.y, id, 1)
{
	Sound::instance()->play("beam");
	_up = new Beam(p, pow, id, speed);
	_up->setVecteur(sf::Vector2f(speed, float(-0.1)));
	_up->rotate(-10);

	_middle = new Beam(p, pow, id, speed);

	_down = new Beam(p, pow, id, speed);
	_down->setVecteur(sf::Vector2f(speed, float(0.1)));
	_down->rotate(10);
}


Shootgun::~Shootgun()
{
	delete _up;
	delete _middle;
	delete _down;
}

void		Shootgun::update()
{
	_pos = _middle->getPos();
	_up->update();
	_middle->update();
	_down->update();
}

void		Shootgun::display(sf::RenderWindow *w)
{
	_up->display(w);
	_middle->display(w);
	_down->display(w);
 }
