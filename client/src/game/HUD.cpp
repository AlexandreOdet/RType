#include "HUD.hh"

HUD::HUD()
{
	_font = fontManager["tec"];

	_blue.b = 250;
	_blue.r = 133;
	_blue.g = 198;

	_l = "LIFE: ";
	_life.setFont(_font);
	_life.setColor(sf::Color::White);
	_life.setCharacterSize(40);
	_life.setPosition(75, 75);

	_s = "SCORE: ";
	_score.setFont(_font);
	_score.setColor(sf::Color::White);
	_score.setCharacterSize(40);
	_score.setPosition(1600, 75);

	_b = "Beam : [";
	_beam.setFont(_font);
	_beam.setColor(_blue);
	_beam.setCharacterSize(35);
	_beam.setPosition(550, 1000);
}

HUD::~HUD()
{
}

void	HUD::update(int const score, int const life, int const charge)
{
	_life.setString(_l + std::to_string(life));
	_score.setString(_s + std::to_string(score));
	std::string c = "";
	int i = 0;
	while (++i < 20)
	{
		if (i < charge)
			c += "|";
		else
			c += "-";
	}
	c += "]";
	_beam.setString(_b + c);
}

void	HUD::display(sf::RenderWindow *w)
{
	w->draw(_life);
	w->draw(_score);
	w->draw(_beam);
}
