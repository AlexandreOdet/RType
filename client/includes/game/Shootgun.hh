#ifndef _SHOOTGUN_H__
#define _SHOOTGUN_H__

#include "Object.hh"
#include "Beam.hh"

class Shootgun :
	public Object
{
public:
	Shootgun(sf::Vector2f const, int const, int const, float const);
	~Shootgun();

	virtual	void		update();
	virtual	void		display(sf::RenderWindow *);

private:
	Beam			*_up;
	Beam			*_middle;
	Beam			*_down;
};

#endif
