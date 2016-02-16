#include "graphic.hh"
#include "client.hh"

graphic::graphic(client *cli) : _cli(cli)
{
	_res.setGameRessource();
	_charge = 0;
	_score = 0;
	_idPlayer = -1;
	_first = true;
	_life = 2;
	_loading = false;
	_stateX = STOPX;
	_stateY = STOPY;
}

graphic::~graphic()
{
	if (_window != NULL)
		_window->close();
}

void 		graphic::initWindow()
{
	_window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "R-Type", sf::Style::Fullscreen);
	_window->setFramerateLimit(60);
	_hud = new HUD();
	Sound::instance()->play("stage");
	_background = new Space();
	_first = false;
}

void 		graphic::setIdPlayer(int const idPlayer)
{
	this->_idPlayer = idPlayer;
}

int 		graphic::getIdPlayer() const
{
	return _idPlayer;
}

void 		graphic::addEntity(int const id, int const type, int const health, int const x, int const y)
{
	if (type < 4)
		_entity[id] = new Player(x, y, id, health);
	else if (type == 6)
		_entity[id] = new Eredship(sf::Vector2f(x, y), id, health);
	else
		_entity[id] = new Eball(sf::Vector2f(x, y), id, health);
}

Object *graphic::getEntity(int const id)
{
	return _entity[id];
}

void 		graphic::deleteEntity(int const id)
{
	bool isShoot;

	isShoot = ((id / 0x80000000) == 1);

	if (id == _idPlayer)
	{
		_idPlayer = -1;
		_cli->quitGame();
	}
	else if (!isShoot)
	{
		std::map<int, Object*>::iterator it = _entity.find(id);

		if (it != _entity.end())
		{
			_explode.push_back(new Explode((*it).second->getPos()));
			it = _entity.erase(it);
		}
	}
	else
	{
		std::vector<Object*>::iterator it;

		for (it = _shoots.begin(); it !=_shoots.end(); ++it)
		{
			if ((*it)->getId() == id)
			{
				delete *it;
				it = _shoots.erase(it);
				return;
			}
		}
	}
}

void 		graphic::addShoot(std::vector<float> const args)
{
	if (args[2] < 3)
	{
		dynamic_cast<Player*>(_entity[static_cast<int>(args[1])])->disableShoot();
		_shoots.push_back(new Beam(sf::Vector2f(WidthToWin(args[3]), HeightToWin(args[4])), (args[2] * 10) + 1, static_cast<int>(args[0]), WidthToWin(args[5])));
	}
	else
		_shoots.push_back(new Eshoot(sf::Vector2f(WidthToWin(args[3]), HeightToWin(args[4])), args[2] ,sf::Vector2f(WidthToWin(args[5]), HeightToWin(args[6]))));
}

bool		graphic::handleEvent()
{
	if (_first == true)
		initWindow();
	cleaner();
	if (!_window->isOpen())
		return false;

	std::map<int, Object*>::iterator it = _entity.find(_idPlayer);
	while (_window->pollEvent(_event))
	{
		eDirection 				_oldX = _stateX;
		eDirection 				_oldY = _stateY;

		if ((_event.type == sf::Event::Closed) || ((_event.type == sf::Event::KeyPressed) &&
				(_event.key.code == sf::Keyboard::Escape)))
			_window->close();

		if (_idPlayer != -1 && it != _entity.end())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (!_loading)
				{
					_cli->sendToNetwork(8, "");
					_loading = true;
				}
				_charge += 1;
			}
			if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Space)
			{
				_cli->sendToNetwork(9, "");
				_loading = false;
				_charge = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				_stateY = UP;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				_stateY = DOWN;
			else
				_stateY = STOPY;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				_stateX = LEFT;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				_stateX = RIGHT;
			else
				_stateX = STOPX;

			if (_stateX != _oldX)
				_cli->sendToNetwork(7, _cli->itos(_stateX));
			if (_stateY != _oldY)
				_cli->sendToNetwork(7, _cli->itos(_stateY));
		}
	}
	if (_idPlayer != -1 && it != _entity.end())
	{
		if (_charge > 0)
			dynamic_cast<Player*>(_entity[_idPlayer])->activeShoot();
		if (_charge == 0)
			dynamic_cast<Player*>(_entity[_idPlayer])->disableShoot();
	}
	for (std::map<int, Object *>::iterator i = _entity.begin(); i != _entity.end(); i++)
		(*i).second->update();
	for (std::vector<Object *>::iterator i = _shoots.begin(); i != _shoots.end(); i++)
		(*i)->update();
	for (std::vector<Explode *>::iterator y = _explode.begin(); y != _explode.end(); y++)
		(*y)->update();
	_background->update();
	_hud->update(_score, _life, _charge);
	return true;
}

void		graphic::printWindow()
{
	if (_first != true)
	{
		_window->clear();
		_background->display(_window);
		for (std::map<int, Object *>::iterator i = _entity.begin(); i != _entity.end(); i++)
			(*i).second->display(_window);
		for (std::vector<Object *>::iterator i = _shoots.begin(); i != _shoots.end(); i++)
			(*i)->display(_window);
		for (std::vector<Explode *>::iterator i = _explode.begin(); i != _explode.end(); i++)
			(*i)->display(_window);
		_hud->display(_window);
		_window->display();
	}
}

void		graphic::cleaner()
{
	for (std::map<int, Object *>::iterator i = _entity.begin(); i != _entity.end();)
	{
		if ((*i).second->getPos().x > 1920 || (*i).second->getPos().x  < 0)
			i = _entity.erase(i);
		else
			i++;
	}
	for (std::vector<Explode *>::iterator y = _explode.begin(); y != _explode.end();)
	{
		if ((*y)->getEnd() == true)
			y = _explode.erase(y);
		else
			y++;
	}
}
