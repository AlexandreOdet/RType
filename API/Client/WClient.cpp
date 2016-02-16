#include "WClient.hh"

typedef int socklen_t;

WClient::WClient()
{
}

WClient::~WClient()
{
  delete (this->_server);
}

bool			WClient::initClient(const std::string &ip, const uint16_t &port)
{
  struct hostent	*hostinfo;

  hostinfo = gethostbyname(ip.c_str());
  if (hostinfo == NULL)
    throw std::runtime_error("Couldn't get host by its name.");
  this->_ip = ip;
  this->_port = port;
  this->_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (this->_sock == -1)
    throw std::runtime_error("Couldn't create a socket.");
  this->_sin.sin_addr = *(reinterpret_cast<struct in_addr *>(hostinfo->h_addr));
  this->_sin.sin_port = htons(port);
  this->_server = new WSocket(this->_sin);
  return (true);
}

const std::string	&WClient::getIP() const
{
  return (this->_ip);
}

std::uint16_t		WClient::getPort() const
{
  return (this->_port);
}

ISocket			*WClient::getSocket() const
{
  return (this->_server);
}

void			WClient::addTimer(const Timer &timer)
{
  this->_timers.push_back(timer);
}

bool			WClient::update()
{
  socklen_t		sinsize;
  long int		size;
  std::list<Timer>::iterator	it;
  struct timeval	tv;

  sinsize = sizeof(this->_sin);
  FD_ZERO(&this->_rbf);
  FD_ZERO(&this->_wbf);
  FD_SET(this->_sock, &this->_rbf);
  if (this->_server->needToWrite())
    FD_SET(this->_sock, &this->_wbf);
  tv.tv_sec = 0;
  tv.tv_usec = 10000;
  if (select(this->_sock + 1, &this->_rbf, &this->_wbf, NULL, &tv) != -1)
    {
      if (FD_ISSET(this->_sock, &this->_rbf))
    	{
    	  size = recvfrom(this->_sock, reinterpret_cast<char *>(&this->_packet), PACKET_SIZE, 0, reinterpret_cast<struct sockaddr *>(&this->_sin), &sinsize);
    	  if (size == -1)
    	    throw std::runtime_error("RecvFrom failed.");
    	  if (size == PACKET_SIZE && this->_server->compare(this->_sin))
    	    this->_server->put(this->_packet);
    	}
      if (FD_ISSET(this->_sock, &this->_wbf) && !this->_server->Write(this->_sock))
	return (false);
    }
  else
    throw std::runtime_error("Select failed.");
  if (!this->_server->update())
    return (false);
  it = this->_timers.begin();
  while (it != this->_timers.end())
    {
      if ((*it).ring())
      	it = this->_timers.erase(it);
      else
      	++it;
    }
  return (true);
}
