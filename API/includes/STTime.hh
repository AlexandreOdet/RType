//
// STTime.hh for STTime in /home/lopez_t/rtype/API/includes
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 01 18:46:38 2015 Thibaut Lopez
// Last update Tue Dec  1 18:52:21 2015 Thibaut Lopez
//

#ifndef	STTIME_HH
#define	STTIME_HH

#ifdef	_WIN32
#include "WTime.hh"
#else
#include "LTime.hh"
#endif

class	STTime
{
private:
  static ITime	*_instance;
  STTime();
  virtual ~STTime();

public:
  static ITime	*getInstance();
};

#endif
