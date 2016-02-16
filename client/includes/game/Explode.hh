#include <SFML/Graphics.hpp>
#include "AManager.hh"
#include "Sound.hh"

class Explode
{
public:
	Explode(sf::Vector2f const);
	~Explode();

	void		update();
	void		display(sf::RenderWindow *) const;
	bool		getEnd() const;

private:
	bool			_end;
	sf::Texture		_t;
	sf::Sprite		_s;
	sf::Clock		_clock;
};
