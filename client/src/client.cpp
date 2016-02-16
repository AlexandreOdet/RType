#include "client.hh"

#ifdef _WIN32
#include "WClient.hh"
#endif

#ifdef _WIN32
int isIp_v4(const char* ip)
{
	char *cp = strdup(ip);
	int num;
	int flag = 1;
	int counter = 0;
	char* p = strtok(cp, ".");

	while (p && flag) {
		num = atoi(p);

		if (num >= 0 && num <= 255 && (counter++<4)) {
			flag = 1;
			p = strtok(NULL, ".");

		}
		else {
			flag = 0;
			break;
		}
	}

	return flag && (counter == 3);

}
#endif

client::client()
{
  _menu = new Menu(this);
#ifndef _WIN32
  _net = new LClient();
#else
  _net = new WClient();
#endif
  _game = NULL;
  _loop = true;

  this->_connected = false;
  this->_onMenu = true;

  this->fctMap[0] = &client::_connect;
  this->fctMap[7] = &client::_move;
  this->fctMap[8] = &client::_loadShoot;
  this->fctMap[9] = &client::_shoot;
  this->fctMap[10] = &client::_destroy;
  this->fctMap[11] = &client::_Leav;
  this->fctMap[12] = &client::_life;
  this->fctMap[13] = &client::_pop;
  this->fctMap[14] = &client::_updateRooms;
  this->fctMap[15] = &client::_updateMap;
  this->fctMap[16] = &client::_startGame;
  this->fctMap[17] = &client::_stopGame;
}

client::~client()
{
}

void  client::loop()
{
  std::size_t tmpSec = 0;
  std::size_t tmpUsec = 0;

  while (_loop)
  {
    if (this->_connected == false)
    {
      if (_menu->handleEvent() == false)
        return;
    }
    else if (_net->update())
    {
      (STTime::getInstance())->now(tmpSec, tmpUsec);
      if (_sec + 2 <= tmpSec)
        sendToNetwork(128, "");
      t_pkt packet;
      if (_net->getSocket()->receive(packet) == true)
        parseCmd(packet);

      if (this->_onMenu)
      {
        if (_menu->handleEvent() == false)
          return;
      }
      else if (_game->handleEvent() == false)
        return;
      else
        _game->printWindow();
    }
    else
      return;
  }
  (void)tmpSec;
  (void)tmpUsec;
}

int   client::ctos(std::string const &arg) const
{
  int *lol = reinterpret_cast<int*>((unsigned char*)arg.c_str());
  return (lol[0]);
}

std::string  client::itos(int const args) const
{
  return std::string((char *)&args, sizeof(int));
}

void  client::sendToNetwork(int cmd, std::string const &args)
{
  t_pkt   packet;

  packet.key = cmd;
  packet.argLength = args.size();
  memcpy(packet.args, args.c_str(), args.size());
  _net->getSocket()->Send(packet);
  (STTime::getInstance())->now(_sec, _usec);
}

bool  client::validateIpAddress(const std::string &ipAddress)
{
    struct sockaddr_in sa;
#ifndef WIN32
    return (inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr))) != 0;
#else
	return isIp_v4(ipAddress.c_str());
#endif
}

void  client::setNetwork(std::string const &ip, std::string const &port)
{
  if (!(validateIpAddress(ip) == 0 || std::string::npos == port.find_first_of("0123456789")))
  {
    _net->initClient(ip, std::stoi(port));
    sendToNetwork(0, "");

    std::size_t sec = 0;
    std::size_t sec2 = 0;
    std::size_t usec = 0;

    (STTime::getInstance())->now(sec, usec);
    sec += 2;
    while (sec2 < sec)
    {
      if (_net->update() == true)
      {
        t_pkt packet;
        if (_net->getSocket()->receive(packet) == true && packet.key == 0)
        {
          parseCmd(packet);
          (STTime::getInstance())->now(_sec, _usec);
          return;
        }
      }
      (STTime::getInstance())->now(sec2, usec);
    }
    delete _net;
#ifndef WIN32
    _net = new LClient();
#else
	_net = new WClient();
#endif
    this->_menu->getConnectMenu()->printMessage(true);
  }
}

void  client::quitGame()
{
  this->_connected = true;
  this->_onMenu = true;
  delete this->_game;
  this->_menu = new Menu(this);
  this->_menu->setConnected(true);
}

void  client::parseCmd(t_pkt const &packet)
{
  std::map<int, _fct>::iterator it = fctMap.find(packet.key);

  if (it != fctMap.end())
    (this->*fctMap[packet.key])(packet.argLength, std::string(packet.args, packet.argLength));
  else if (packet.key != 128)
    std::cerr << "Error : Command " << packet.key << " unknown" << std::endl;
}

void  client::_connect(int const size, std::string const &args)
{
  this->_connected = true;
  _menu->setConnected(true);
  (void)size;
  (void)args;
}

void client::_move(int const size, std::string const & args) // OK
{
  if (_onMenu)
    return;

  std::vector<float> _args;

  for (int i = 0; i < size; i += 4) {
    _args.push_back(static_cast<float>(ctos(args.substr(i, i + 4))));
  }

  _game->getEntity(_args[0])->setPos(sf::Vector2f(WidthToWin(_args[1]), HeightToWin(_args[2])));
  _game->getEntity(_args[0])->setVecteur(sf::Vector2f(WidthToWin(_args[3]), HeightToWin(_args[4])));

  if (_args[4] == 0)
    _game->getEntity(_args[0])->setState(STAND);
  if (_args[4] > 0)
    _game->getEntity(_args[0])->setState(UP);
  if (_args[4] < 0)
    _game->getEntity(_args[0])->setState(DOWN);
}

void  client::_loadShoot(int const size, std::string const &args) // OK
{
  if (_onMenu)
    return;

  dynamic_cast<Player*>(_game->getEntity(ctos(args)))->activeShoot();
  (void)size;
}

void  client::_shoot(int const size, std::string const &args) // OK
{
  if (_onMenu)
    return;
  std::vector<float> _args;

  for (int i = 0; i < size; i += 4) {
    _args.push_back((float)ctos(args.substr(i, i + 4)));
  }

  _game->addShoot(_args);
}

void  client::_destroy(int const size, std::string const &args) // OK
{
  if (_onMenu)
    return;

  _game->deleteEntity(ctos(args));
  (void)size;
}

void  client::_Leav(int const size, std::string const &args) // OK
{
  if (_onMenu)
    return;

  _game->deleteEntity(ctos(args));
  (void)size;
}

void  client::_life(int const size, std::string const &args)
{
  if (_onMenu)
    return;

	_game->getEntity(ctos(args.substr(0, 4)))->setHealth(ctos(args.substr(4, 8)));
  _game->getEntity(ctos(args.substr(0, 4)))->hit();
  (void)size;
}

void  client::_pop(int const size, std::string const &args) // OK
{
  if (_onMenu)
    return;

  std::vector<float> _args;

  for (int i = 0; i < size; i += 4) {
    _args.push_back(static_cast<float>(ctos(args.substr(i, i + 4))));
  }

  _game->addEntity(_args[0], _args[1], _args[2], WidthToWin(_args[3]), HeightToWin(_args[4]));
}

void  client::_updateRooms(int const size, std::string const &args) // OK
{
  if (size >= 8 && this->_onMenu == true)
  {
    unsigned int id = 0;
    unsigned int nbPlayer = 0;
    unsigned int NbPlayerReady = 0;

    id = ctos(args.substr(0, 4));
    nbPlayer = ctos(args.substr(4, 4));
    NbPlayerReady = ctos(args.substr(8, 4));
    this->_menu->getRoomMenu()->getPopup()->updateRoom(id, nbPlayer, NbPlayerReady);
  }
}

void  client::_updateMap(int const size, std::string const &args)
{
  (void)size;
  (void)args;
}

void  client::_startGame(int const size, std::string const &args) // OK
{
  this->_onMenu = false;
  this->_connected = true;
  delete this->_menu;
  _game = new graphic(this);
  _game->setIdPlayer(ctos(args.substr(0, 4)));
  (void)size;
}

void  client::_stopGame(int const size, std::string const &args) // OK
{
  quitGame();
  (void)args;
  (void)size;
}
