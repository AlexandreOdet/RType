#pragma once
#include "Object.hh"
class Eeye :
	public Object
{
public:
	Eeye(sf::Vector2f const, int const, int const);
	~Eeye();

	virtual void update();
};
