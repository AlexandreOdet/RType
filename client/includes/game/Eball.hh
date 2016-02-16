#ifndef __EBALL_H__
#define __EBALL_H__


#include "Object.hh"

class Eball :
	public Object
{
public:
	Eball(sf::Vector2f const, int const, int const);
	~Eball();

	void	virtual update();
};

#endif
