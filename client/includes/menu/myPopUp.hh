#ifndef MYPOPUP_HH
#define MYPOPUP_HH

#include <SFML/Graphics.hpp>
#include <list>

#include "AManager.hh"
#include "Room.hh"
#include "readyLighter.hh"

class client;

class myPopUp
{
public:
  myPopUp(client *cli);
  ~myPopUp();

  void HandleKeyBoard(sf::Event &_event);
  void printWindow(sf::RenderWindow &);

  void updateRoom(int const, int const, int const);
  void joinRoom();
  void createRoom();
  void setReady();
  void readyRoom();
  bool getIsReady() const;

private:
  sf::Font  _titleFont;
  sf::Font  _listingFont;

  sf::RectangleShape _CreateButton;
  sf::RectangleShape _JoinButton;
  sf::RectangleShape _popUpWindow;
  sf::RectangleShape _selectedRoom;
  sf::RectangleShape _borderLine;
  sf::RectangleShape _ReadyButton;

  sf::Text _titleText;
  sf::Text _columnIdTitle;
  sf::Text _columnPlayerTitle;
  sf::Text _CreateText;
  sf::Text _JoinText;
  sf::Text _ReadyText;

  std::list<sf::CircleShape> _readyLight;

  Room                *_oldRoom;
  client              *_cli;
  std::vector<std::pair<int, Room *> > roomList;
  readyLighter *readys;

  int _posSelected;
  int _posCursor;
  int _readyPlayer;
  bool _isReady;

  void initResources();
};

#endif
