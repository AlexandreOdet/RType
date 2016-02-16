#ifndef __ROOM__
#define __ROOM__

class Room
{
public:
  explicit Room(const int, const int);
  ~Room();

  int getIdRoom() const;
  int getNbPlayerRoom() const;
  int getReadys() const;
  void setPlayer(int const);
  void addReadys(int const);
  void updateFire();

private:
  int _id;
  int _nbPlayer;
  int _nbPlayerReady;
};


#endif /*__ROOM__*/
