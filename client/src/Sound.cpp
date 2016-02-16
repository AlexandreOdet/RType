#include "Sound.hh"

Sound *Sound::_instance = NULL;

Sound::Sound()
{
	try
	{
		if (!_music.openFromFile("../ressources/songs/stage_sound.ogg"))
			throw std::invalid_argument("stage_sound");
		if (!_s_shoot.openFromFile("../ressources/songs/beam_sound.ogg"))
			throw std::invalid_argument("beam_sound");
		if (!_s_explose.openFromFile("../ressources/songs/explose_sound.ogg"))
			throw std::invalid_argument("explose_sound");
	}
	catch (std::invalid_argument const &e)
	{
		std::cerr << "Impossible to load sound : " << e.what() << std::endl;
		exit (EXIT_FAILURE);
	}
	_s_shoot.setVolume(15);
	_s_explose.setVolume(70);
}


Sound::~Sound()
{
}

Sound     *Sound::instance()
{
	if (_instance == NULL)
		_instance = new Sound();
	return (_instance);
}

void		Sound::play(std::string type)
{
	if (type == "beam")
		_s_shoot.play();
	if (type == "explose")
		_s_explose.play();
	if (type == "stage")
		_music.play();
}
