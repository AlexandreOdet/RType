#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Sound.hh"
#include "AManager.hh"
#include "GameHeader.hh"
#include "STTime.hh"

class Object
{
public:
	Object(float const, float const, int const, int const);
	virtual ~Object();

	virtual std::string		getType() const;

	virtual void					update();
	virtual void					setVecteur(sf::Vector2f);
	virtual void					setState(eDirection s);
	virtual eDirection		getState() const;
	virtual void					setPos(sf::Vector2f p);
	virtual sf::Vector2f	getPos() const;
	virtual void					display(sf::RenderWindow *w);

	virtual int 					getId() const;
	virtual int 					getHealth() const;
	virtual void 					setHealth(int const);
	void 									hit();

protected:
	sf::Texture		_t_obj;
	sf::Sprite		_s_obj;
	int				_id;
	int				_s;
	int				_xsize;
	int				_ysize;
	int 			_health;
	int				_nbanime;
	std::size_t _sec;
	std::size_t _usec;
	bool      _isTransparent;

	std::string		_type;
	eDirection			_state;
	sf::Clock		_clock;
	sf::Vector2f	_pos;
	sf::Vector2f	_vecteur;
};

#endif
