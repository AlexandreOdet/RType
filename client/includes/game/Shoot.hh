#ifndef __SHOOT_H__
#define __SHOOT_H__

#include "Object.hh"
class Shoot :
	public Object
{
public:
	Shoot(sf::Vector2f const, int const);
	~Shoot();

	virtual void update();
};

#endif
