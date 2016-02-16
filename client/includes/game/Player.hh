#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Object.hh"

class Player :
	public Object
{
public:
	Player(int const, int const, int const, int const);
	~Player();

	void	virtual update();
	void	virtual display(sf::RenderWindow *);
	void	activeShoot();
	void	disableShoot();

private:
	bool			_active;
	sf::Texture		_t_load;
	sf::Sprite		_s_load;
	sf::Clock		_clock2;
	int				_s2;

};

#endif
