#ifndef __SOUND_H__
#define __SOUND_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CException.hpp"

class Sound
{
public:
	~Sound();

	void			play(std::string);
	static Sound	*instance();

private:
	Sound();
	sf::Music					_music;
	sf::Music					_s_shoot;
	sf::Music					_s_explose;
	static Sound				*_instance;
};

#endif
