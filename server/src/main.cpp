//
// main.cpp for main in /home/lopez_t/rtype/server
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Tue Nov 24 14:54:20 2015 Thibaut Lopez
// Last update Sat Jan  2 19:10:34 2016 Thibaut Lopez
//

#include "Server.hh"

int		main()
{
  try
    {
      Server	srv;

      if (!srv.initServer(6667))
	return (1);
      std::cout << srv.getPort() << std::endl;
      srv.run();
    }
  catch (std::runtime_error &err)
    {
      std::cerr << err.what() << std::endl;
      return (1);
    }
  return (0);
}
