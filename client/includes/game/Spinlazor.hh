#ifndef __SPINLAZOR_H_
#define __SPINLAZOR_H_


#include "Object.hh"

class Spinlazor :
	public Object
{
public:
	Spinlazor(sf::Vector2f const, int const, int const);
	~Spinlazor();

	void	virtual update();
};

#endif
