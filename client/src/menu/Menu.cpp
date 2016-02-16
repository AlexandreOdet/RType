#include "Menu.hh"
#include "client.hh"

Menu::Menu(client *cli) : _cli(cli)
{
  _res.setMenuRessource();
  this->_window.create(sf::VideoMode(1920, 1080), "R-Type");// , sf::Style::Fullscreen);
  this->_window.setFramerateLimit(60);
  this->_connect = new ConnectMenu(_cli);
  this->_rooms = new MainWindow(_cli);

  this->isConnected = false;
  mapEvent[sf::Event::Closed] = &Menu::closeApp;
  mapEvent[sf::Event::KeyPressed] = &Menu::HandleKeyBoard;
  mapEvent[sf::Event::MouseMoved] = &Menu::HandleKeyBoard;
  mapEvent[sf::Event::MouseButtonPressed] = &Menu::HandleKeyBoard;
}

Menu::~Menu()
{
}

bool Menu::handleEvent()
{
  if (this->_window.isOpen())
  {
    while (this->_window.pollEvent(this->_event))
    {
      ptr = mapEvent[this->_event.type];
      if (ptr)
        (this->*ptr)();
    }
    this->printWindow();
    return true;
  }
  else
    return false;
}

void Menu::closeApp()
{
  this->_window.close();
}

void Menu::HandleKeyBoard()
{
  if (_event.key.code == sf::Keyboard::Escape)
    this->_window.close();
  if (isConnected == false)
    _connect->HandleKeyBoard(this->_event);
  else
    _rooms->HandleKeyBoard(this->_event, this->_window);
}

void Menu::printWindow()
{
  this->_window.clear();
  if (isConnected == false)
    _connect->printWindow(this->_window);
  else
    _rooms->printWindow(this->_window);
  this->_window.display();
}

void Menu::setConnected(bool const c)
{
  this->isConnected = c;
}

ConnectMenu   *Menu::getConnectMenu()
{
  return _connect;
}

MainWindow    *Menu::getRoomMenu()
{
  return _rooms;
}
