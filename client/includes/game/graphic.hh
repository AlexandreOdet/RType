#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <SFML/Graphics.hpp>

#include "AManager.hh"
#include "Space.hh"
#include "Eball.hh"
#include "Player.hh"
#include "HUD.hh"
#include "Shoot.hh"
#include "Eshoot.hh"
#include "Explode.hh"
#include "Eredship.hh"
#include "Beam.hh"
#include "Spinlazor.hh"
#include "Shootgun.hh"
#include "IGraphic.hh"
#include "GameHeader.hh"

class client;

class graphic : public IGraphic
{
public:
	graphic(client *);
	~graphic();

	bool handleEvent();
	void printWindow();
	void initWindow();
	void cleaner();

	void setIdPlayer(int const idPlayer);
	int 	getIdPlayer() const;
	void addEntity(int const, int const, int const, int const, int const);
	void deleteEntity(int const);
	void addShoot(std::vector<float> const);
	Object *getEntity(int const);

private:

	eDirection 				_stateX;
	eDirection 				_stateY;

	sf::RenderWindow	*_window;
	sf::Event					_event;

	int							_score;
	int							_life;
	bool						_first;
	bool 						_loading;
	float 					_charge;

	client          *_cli;
	HUD							*_hud;
	Space						*_background;

	int 						_idPlayer;

	std::map<int, Object*> 	_entity;
	std::vector<Object *>		_shoots;
	std::vector<Explode *>	_explode;

	AManager 				_res;
};

#endif
