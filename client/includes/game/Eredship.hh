#ifndef __EREDSHIP__H_
#define __EREDSHIP__H_

#include "Object.hh"
class Eredship :
	public Object
{
public:
	Eredship(sf::Vector2f const, int const, int const);
	~Eredship();

	void	virtual update();
};

#endif
