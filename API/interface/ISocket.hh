//
// ISocket.hh for ISocket in /home/lopez_t/rtype/API/interface
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Thu Nov 19 11:42:59 2015 Thibaut Lopez
// Last update Tue Dec 15 17:26:52 2015 Thibaut Lopez
//

#ifndef	ISOCKET_HH
#define	ISOCKET_HH

#include <iostream>
#include <string>
#include <stdexcept>
#include "ReliabilitySystem.hh"
#include "FlowControl.hh"
#ifdef	_WIN32
#include "WMutex.hh"
#else
#include "LMutex.hh"
#endif

class	ISocket : public Mutex
{
public: 
  virtual ~ISocket() {}
  virtual bool		receive(t_pkt &) = 0;
  virtual void		Send(const t_pkt &) = 0;
  virtual void		printStats() const = 0;
};

#endif
