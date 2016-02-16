//
// IClient.hh for IClient in /home/lopez_t/rtype/API/interface
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Thu Nov 19 15:38:19 2015 Thibaut Lopez
// Last update Thu Dec  3 01:24:17 2015 Thibaut Lopez
//

#ifndef	ICLIENT_HH
#define	ICLIENT_HH

#include <cstdint>
#include <limits>
#include <list>
#include "ISocket.hh"
#include "Timer.hh"

class	IClient
{
public:
  virtual ~IClient() {}

  virtual bool			initClient(const std::string &, const uint16_t &) = 0;
  virtual const std::string	&getIP() const = 0;
  virtual std::uint16_t		getPort() const = 0;
  virtual ISocket		*getSocket() const  = 0;
  virtual void			addTimer(const Timer &) = 0;
  virtual bool			update() = 0;
};

#endif
