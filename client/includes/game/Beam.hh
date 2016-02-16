#ifndef __BEAM_H__
#define __BEAM_H__


#include "Object.hh"

class Beam :
	public Object
{
public:
	Beam(sf::Vector2f const, int const, int const, float const);
	~Beam();

	virtual	void	rotate(float const);
	virtual	void	update();
	virtual	void	display(sf::RenderWindow *);

private:

	int				_pow;
	sf::Texture		_t_medium;
	sf::Sprite		_s_medium;
	sf::Texture		_t_strong;
	sf::Sprite		_s_strong;
};

#endif
