#include "Object.hh"

Object::Object(float const x, float const y ,int const id, int const health)
	: _sec(0), _usec(0)
{
	_pos.x = x;
	_pos.y = y;
	_id = id;
	_health = health;
	_state = STAND;
	_s = 0;
}

Object::~Object()
{
}


std::string			Object::getType() const
{
	return _type;
}

void				Object::setVecteur(sf::Vector2f v)
{
	_vecteur = v;
}

void				Object::display(sf::RenderWindow *w)
{
	std::size_t nSec;
	std::size_t nUsec;
	std::size_t tmpSec;
	std::size_t tmpUsec;

	if (this->_isTransparent)
		{
			(STTime::getInstance())->now(nSec, nUsec);
			(STTime::getInstance())->sub(nSec, nUsec, this->_sec, this->_usec, tmpSec, tmpUsec);
			if (tmpSec >= 1)
			 {
				 this->_isTransparent = false;
				 _s_obj.setColor(sf::Color(255, 255, 255, 255));
			 }
		}
	w->draw(_s_obj);
}

void				Object::update()
{
	_pos += _vecteur;
	_s_obj.setPosition(_pos);
}

void				Object::setState(eDirection s)
{
	_state = s;
}

eDirection			Object::getState() const
{
	return _state;
}

void				Object::setPos(sf::Vector2f p)
{
	_pos = p;
}

sf::Vector2f	Object::getPos() const
{
	return _pos;
}

void				Object::setHealth(int const p)
{
	_health = p;
	(void)p;
}

int 				Object::getHealth() const
{
	return _health;
}

int 				Object::getId() const
{
	return _id;
}

void        Object::hit()
{
	(STTime::getInstance())->now(this->_sec, this->_usec);
	_s_obj.setColor(sf::Color(255, 255, 255, 128));
	this->_isTransparent = true;
}
