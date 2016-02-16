#ifndef __MAIN_WINDOW__
#define __MAIN_WINDOW__

#include <SFML/Graphics.hpp>
#include <iostream>

#include "myPopUp.hh"
#include "AManager.hh"
#include "InsertCoin.hh"

#define WIN_Y (1200)
#define WIN_X (1800)
#define FPS (60)

class MainWindow
{
public:
  MainWindow(client *);
  ~MainWindow();

  void HandleKeyBoard(sf::Event &, sf::RenderWindow &);
  void printWindow(sf::RenderWindow &);
  myPopUp  *getPopup() const;

private:
  sf::Texture _img;
  sf::Texture _img_logo;
  sf::Texture _highlight_Texture;
  sf::Texture _earth_img;

  sf::Sprite _sprite;
  sf::Sprite _logo;
  sf::Sprite _highlight_Sprite;
  sf::Sprite _earth_sprite;
  sf::Sprite _highlight_ship;
  sf::Color  _Orange;
  sf::Font   _font;

  sf::Text _play;
  sf::Text _exit;
  sf::Text _Title;
  client      *_cli;
  myPopUp     *roomPrint;
  InsertCoin *_insertCoin;

  bool _ismyPopUpOpened;
  bool _highlight;
  bool _highlightShip;

  void initRes();

  void selectEventHandling();

  void highlightExit();
  void backToNormal();
  void highlightPlay();
};

#endif /*__MAIN_WINDOW__*/
