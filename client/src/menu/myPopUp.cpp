#include "myPopUp.hh"
#include "client.hh"
#include <iostream>

myPopUp::myPopUp(client *cli) : _cli(cli)
{
  this->_posCursor = 0;
  this->_posSelected = -1;
  this->_oldRoom = NULL;
  this->_readyPlayer = 0;
  this->_isReady = false;
  this->initResources();

  this->_popUpWindow.setSize(sf::Vector2f(700, 850));
  this->_popUpWindow.setFillColor(sf::Color(224, 224, 224));
  this->_popUpWindow.setPosition(30, 50);
  this->_popUpWindow.setOutlineThickness(10);
  this->_popUpWindow.setOutlineColor(sf::Color(153, 204, 255));

  this->_CreateButton.setSize(sf::Vector2f(200, 75));
  this->_CreateButton.setFillColor(sf::Color(255, 255, 255));
  this->_CreateButton.setPosition(500, 200);
  this->_CreateButton.setOutlineThickness(10);
  this->_CreateButton.setOutlineColor(sf::Color(0, 0, 0));

  this->_JoinButton.setSize(sf::Vector2f(200, 75));
  this->_JoinButton.setFillColor(sf::Color(255, 255, 255));
  this->_JoinButton.setPosition(500, 400);
  this->_JoinButton.setOutlineThickness(10);
  this->_JoinButton.setOutlineColor(sf::Color(0, 0, 0));

  this->_ReadyButton.setSize(sf::Vector2f(200, 75));
  this->_ReadyButton.setFillColor(sf::Color(255, 255, 255));
  this->_ReadyButton.setPosition(500, 600);
  this->_ReadyButton.setOutlineThickness(10);
  this->_ReadyButton.setOutlineColor(sf::Color(0, 0, 0));

  this->_borderLine.setSize(sf::Vector2f(10, 775));
  this->_borderLine.setFillColor(sf::Color(153, 204, 255));
  this->_borderLine.setPosition(200, 110);
  this->readys = new readyLighter(550, 800, 0);
}

myPopUp::~myPopUp()
{
}

void myPopUp::updateRoom(int const id, int const nbPlayer, int const NbPlayerReady)
{
  if (roomList.size() > 0)
  {
    std::vector<std::pair<int, Room *> >::iterator it;

    for (it = roomList.begin(); it != roomList.end(); ++it)
    {
      if ((*it).second->getIdRoom() == id)
      {
        if (nbPlayer == 0)
        {
          _cli->sendToNetwork(5, _cli->itos(id));
          it = roomList.erase(it);
        }
        else
          (*it).second->setPlayer(nbPlayer);
        return;
      }
    }
    roomList.push_back(std::pair<int, Room*>((roomList.end() - 1)->first + 1,new Room(id, nbPlayer)));
  }
  else
    roomList.push_back(std::pair<int, Room*>(0, new Room(id, nbPlayer)));
  (void)NbPlayerReady;
}

void myPopUp::joinRoom()
{
  if (this->_isReady)
    this->_isReady = false;
  int   toJoin = 0;
  int   oldSelected = this->_posSelected;

  this->_posSelected = this->_posCursor;
  for (size_t i = 0; i < roomList.size(); i++)
  {
    if (roomList[i].second->getIdRoom() == _posSelected)
    {
      toJoin = roomList[i].second->getIdRoom();
      this->readys->updateLights(roomList[i].second->getReadys());
      break;
    }
  }
  if (oldSelected != -1)
    _cli->sendToNetwork(4, _cli->itos(oldSelected));
  _cli->sendToNetwork(3, _cli->itos(toJoin));
}

void myPopUp::readyRoom()
{
  this->_isReady = !this->_isReady;
  for (size_t i = 0; i < roomList.size(); i++)
  {
    if (roomList[i].second->getIdRoom() == _posSelected)
    {
      roomList[i].second->addReadys(roomList[i].second->getReadys());
      _cli->sendToNetwork(6, _cli->itos(roomList[i].second->getIdRoom()) + _cli->itos(this->_isReady));
      this->readys->updateLights(roomList[i].second->getReadys());
      break;
    }
  }
}

void myPopUp::createRoom()
{
  if (this->_posSelected != -1)
  {
    _cli->sendToNetwork(4, _cli->itos(this->_posSelected));
    this->_posSelected = roomList.size() - 1;
    this->_posCursor = roomList.size() - 1;
  }
  else
  {
    this->_posSelected = 0;
    this->_posCursor = 0;
  }
  this->_cli->sendToNetwork(2, "");
}

void myPopUp::initResources()
{
  this->_titleFont = fontManager["spaceage"];
  this->_listingFont = fontManager["Android"];

  this->_columnIdTitle.setString("Room");
  this->_columnIdTitle.setFont(this->_listingFont);
  this->_columnIdTitle.setStyle(sf::Text::Regular);
  this->_columnIdTitle.setCharacterSize(50);
  this->_columnIdTitle.setColor(sf::Color::Red);
  this->_columnIdTitle.setPosition(50, 50);

  this->_columnPlayerTitle.setString("Players");
  this->_columnPlayerTitle.setFont(this->_listingFont);
  this->_columnPlayerTitle.setStyle(sf::Text::Regular);
  this->_columnPlayerTitle.setCharacterSize(50);
  this->_columnPlayerTitle.setColor(sf::Color::Red);
  this->_columnPlayerTitle.setPosition(250, 50);

  this->_CreateText.setString("Create");
  this->_CreateText.setFont(this->_titleFont);
  this->_CreateText.setStyle(sf::Text::Regular);
  this->_CreateText.setCharacterSize(35);
  this->_CreateText.setColor(sf::Color::Black);
  this->_CreateText.setPosition(505, 215);

  this->_JoinText.setString("Join");
  this->_JoinText.setFont(this->_titleFont);
  this->_JoinText.setStyle(sf::Text::Regular);
  this->_JoinText.setCharacterSize(35);
  this->_JoinText.setColor(sf::Color::Black);
  this->_JoinText.setPosition(540, 415);

  this->_ReadyText.setString("Ready");
  this->_ReadyText.setFont(this->_titleFont);
  this->_ReadyText.setStyle(sf::Text::Regular);
  this->_ReadyText.setCharacterSize(35);
  this->_ReadyText.setColor(sf::Color::Black);
  this->_ReadyText.setPosition(520, 615);

}

void myPopUp::HandleKeyBoard(sf::Event &_event)
{
  if (_event.type == sf::Event::KeyPressed)
  {
    if (_event.key.code == sf::Keyboard::Down)
        this->_posCursor = ((unsigned long)this->_posCursor == this->roomList.size() -1) ? 0 : this->_posCursor + 1;
    if (_event.key.code == sf::Keyboard::Up)
      this->_posCursor = (this->_posCursor == 0) ? this->roomList.size() -1 : this->_posCursor - 1;
    if (_event.key.code == sf::Keyboard::Space)
      this->joinRoom();
  }
  else if (_event.type == sf::Event::MouseButtonPressed)
  {
    if (_event.mouseButton.button == sf::Mouse::Left)
    {
      if (_event.mouseButton.x < (700) && _event.mouseButton.x > (500)
          && _event.mouseButton.y < (475) && _event.mouseButton.y > (400))
            this->joinRoom();
      else if (_event.mouseButton.x < (700) && _event.mouseButton.x > (500)
          && _event.mouseButton.y < (475) && _event.mouseButton.y > (200))
            this->createRoom();
      else if (_event.mouseButton.x < (700) && _event.mouseButton.x > (500)
              && _event.mouseButton.y < (675) && _event.mouseButton.y > (600))
            this->readyRoom();
    }
  }
}

void myPopUp::printWindow(sf::RenderWindow & window)
{
    int x, y, count = 0;

    window.draw(this->_titleText);
    window.draw(this->_popUpWindow);
    window.draw(this->_columnIdTitle);
    window.draw(this->_columnPlayerTitle);
    window.draw(this->_CreateButton);
    window.draw(this->_JoinButton);
    window.draw(this->_CreateText);
    window.draw(this->_JoinText);
    window.draw(this->_borderLine);
    if (this->roomList.size() <1)
      return;
    x = 75;
    y = 75;

    std::vector<std::pair<int, Room*> >::iterator it;
    for (it = this->roomList.begin(); it != this->roomList.end(); ++it)
    {
      sf::Text idRoom(std::to_string((*it).second->getIdRoom()), _listingFont, 100);
      sf::Text nbPlayer(std::to_string((*it).second->getNbPlayerRoom()) + "/4", _listingFont, 100);

      if (this->_posSelected == count)
      {
        idRoom.setColor(sf::Color::Red);
        nbPlayer.setColor(sf::Color::Red);
      }
      else
      {
        idRoom.setColor(sf::Color::White);
        nbPlayer.setColor(sf::Color::White);
      }
      if (count == this->_posCursor)
      {
        this->_selectedRoom.setSize(sf::Vector2f(430, 70));
        this->_selectedRoom.setFillColor(sf::Color(0, 0, 0, 0));
        this->_selectedRoom.setOutlineThickness(5);
        this->_selectedRoom.setOutlineColor(sf::Color(153, 204, 255));
        this->_selectedRoom.setPosition(x - 25, y + 35);
        window.draw(this->_selectedRoom);
      }
      idRoom.setPosition(x, y);
      window.draw(idRoom);
      nbPlayer.setPosition(x + 200, y);
      window.draw(nbPlayer);
      count++;
      y += 100;
    }
    window.draw(this->_ReadyButton);
    window.draw(this->_ReadyText);
    readys->printLights(window);
}

bool myPopUp::getIsReady() const
{
  return this->_isReady;
}
