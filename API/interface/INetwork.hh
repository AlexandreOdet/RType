// INetwork.hh for INetwork in /home/lopez_t/Babel/API/interface
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Thu Oct  8 15:54:43 2015 Thibaut Lopez
// Last update Tue Dec 15 14:33:34 2015 Thibaut Lopez
//

#ifndef	INETWORK_HH
#define	INETWORK_HH

#include <cstdint>
#include <limits>
#include <list>
#include "ISocket.hh"
#include "Timer.hh"

class	IHandler
{
public:
  virtual void		handleConnection(ISocket *) = 0;
  virtual void		handleDisconnection(ISocket *) = 0;
};

class	INetwork
{
public:
  virtual ~INetwork() {}

  virtual bool		initServer(const uint16_t &, IHandler *) = 0;
  virtual std::uint16_t	getPort() const = 0;
  virtual bool		eraseSocket(ISocket *) = 0;
  virtual void		addTimer(const Timer &) = 0;
  virtual bool		update() = 0;
};

#endif
