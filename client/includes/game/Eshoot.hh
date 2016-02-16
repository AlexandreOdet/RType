#ifndef __ESHOOT_H__
#define __ESHOOT_H__

#include "Object.hh"

class Eshoot :
	public Object
{
public:
	Eshoot(sf::Vector2f const, int const, sf::Vector2f const);
	~Eshoot();

	void virtual	update();
};

#endif
