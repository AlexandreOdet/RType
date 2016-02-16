#include "MainWindow.hh"

MainWindow::MainWindow(client *cli) : _cli(cli)
{
  this->_ismyPopUpOpened = false;
  this->_highlight = false;
  this->_highlightShip = false;
  this->_Orange = sf::Color(255, 153, 51, 50);

  this->_font = fontManager["spaceage"];
  this->_img = imageManager["MainBG"];
  this->_img_logo = imageManager["rtype_logo"];
  this->_highlight_Texture = imageManager["highlight"];
  this->_earth_img = imageManager["earth"];

  this->initRes();
  this->roomPrint = new myPopUp(_cli);
  this->_insertCoin = new InsertCoin(this->_font, 50, 960);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initRes()
{
  this->_sprite.setTexture(this->_img);

  this->_logo.setTexture(this->_img_logo);
  this->_logo.setPosition(1450, 960);

  this->_highlight_Sprite.setTexture(this->_highlight_Texture);
  this->_highlight_Sprite.setScale(0.6, 0.6);
  this->_highlight_Sprite.setPosition(615, 685);

  this->_highlight_ship.setTexture(this->_highlight_Texture);
  this->_highlight_ship.setPosition(1160, 720);
  this->_highlight_ship.setScale(0.7, 0.4);

  this->_earth_sprite.setTexture(this->_earth_img);
  this->_earth_sprite.setPosition(0, 0);

  this->_play.setString("play");
  this->_play.setFont(this->_font);
  this->_play.setCharacterSize(100);
  this->_play.setColor(this->_Orange);
  this->_play.setPosition(10, 10);

  this->_exit.setString("exit");
  this->_exit.setFont(this->_font);
  this->_exit.setCharacterSize(100);
  this->_exit.setColor(this->_Orange);
  this->_exit.setPosition(1600, 10);
}

void MainWindow::HandleKeyBoard(sf::Event &event, sf::RenderWindow &window)
{
  if (this->_ismyPopUpOpened == false)
  {
    if (event.type == sf::Event::MouseMoved)
      {
        if ((event.mouseMove.x < (1900) && event.mouseMove.x > (1600)
          && event.mouseMove.y < (100) && event.mouseMove.y > (0))
          ||  (event.mouseMove.x < (1350) && event.mouseMove.x > (1130)
              && (event.mouseMove.y < (810) && event.mouseMove.y > (700))))
                this->highlightExit();
          else if ((event.mouseMove.x < (740) && event.mouseMove.x > (600)
              && event.mouseMove.y < (810) && event.mouseMove.y > (700)) ||
                  (event.mouseMove.x < (500) && event.mouseMove.x > (0)
                && event.mouseMove.y < (150) && event.mouseMove.y > (0)))
                  this->highlightPlay();
          else
            this->backToNormal();
        }
      else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
              if ((event.mouseMove.x < (1900) && event.mouseMove.x > (1600)
                && event.mouseMove.y < (100) && event.mouseMove.y > (0))
              ||  (event.mouseButton.x < (1350) && event.mouseButton.x > (1130)
                  && (event.mouseButton.y < (810) && event.mouseButton.y > (700))))
                window.close();
        else if ((event.mouseButton.x < (740) && event.mouseButton.x > (600)
          && event.mouseButton.y < (810) && event.mouseButton.y > (700)) ||
          (event.mouseButton.x < (450) && event.mouseButton.x > (0)
          && event.mouseButton.y < (100) && event.mouseButton.y > (00)))
          this->_ismyPopUpOpened = true;
      }
    }
  }
  else
  {
    if (event.key.code == sf::Keyboard::P)
      this->_ismyPopUpOpened = false;
    this->roomPrint->HandleKeyBoard(event);
  }
}

void MainWindow::printWindow(sf::RenderWindow &window)
{
  window.draw(this->_sprite);
  window.draw(this->_logo);
  this->_insertCoin->makeItBlink();
  window.draw(this->_insertCoin->getText());
  window.draw(this->_exit);
  if (this->_highlight == true)
    window.draw(this->_highlight_Sprite);
  if (this->_highlightShip == true)
    window.draw(this->_highlight_ship);
  window.draw(this->_play);
  if (this->_ismyPopUpOpened == true)
    this->roomPrint->printWindow(window);
}

void MainWindow::highlightExit()
{
  this->_highlightShip = true;
  this->_exit.setCharacterSize(105);
  this->_exit.setColor(sf::Color::Yellow);
}

void MainWindow::backToNormal()
{
  this->_play.setCharacterSize(100);
  this->_play.setColor(this->_Orange);
  this->_exit.setCharacterSize(100);
  this->_exit.setColor(this->_Orange);
  this->_highlight = false;
  this->_highlightShip = false;
}

void MainWindow::highlightPlay()
{
  this->_highlight = true;
  this->_play.setCharacterSize(105);
  this->_play.setColor(sf::Color::Yellow);
}

myPopUp  *MainWindow::getPopup() const
{
  return roomPrint;
}
