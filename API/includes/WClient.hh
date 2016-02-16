#ifndef _WClient_
#define _WClient_

#include "IClient.hh"
#include "ISocket.hh"
#ifdef _WIN32
#include "WSocket.hh"
#endif
class WClient : public IClient
{
  public:
    explicit WClient();
    virtual ~WClient();

    bool			initClient(const std::string &, const uint16_t &);
    const std::string	&getIP() const;
    std::uint16_t		getPort() const;
    ISocket		*getSocket() const;
    void			addTimer(const Timer &);
    bool			update();
  private:
    int			_sock;
    std::string		_ip;
    std::uint16_t		_port;
    struct sockaddr_in	_sin;
    fd_set		_rbf;
    fd_set		_wbf;
    WSocket		*_server;
    t_pkt			_packet;
    std::list<Timer>	_timers;
};

#endif /*_WClient_*/
