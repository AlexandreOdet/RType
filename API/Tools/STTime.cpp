//
// STTime.cpp for STTime in /home/lopez_t/rtype/API/Tools
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Tue Dec 01 18:46:38 2015 Thibaut Lopez
// Last update Tue Dec  1 18:51:28 2015 Thibaut Lopez
//

#include "STTime.hh"

ITime	*STTime::_instance = NULL;

STTime::STTime()
{
}

STTime::~STTime()
{
}

ITime	*STTime::getInstance()
{
  if (_instance == NULL)
    {
#ifdef	_WIN32
      _instance = new WTime();
#else
      _instance = new LTime();
#endif
    }
  return (_instance);
}
