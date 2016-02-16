//
// PacketQueue.hh for PacketQueue in /home/lopez_t/rtype/API
//
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
//
// Started on  Mon Nov 30 15:04:07 2015 Thibaut Lopez
// Last update Tue Dec 15 14:23:14 2015 Thibaut Lopez
//

#ifndef	PACKETQUEUE_HH
#define	PACKETQUEUE_HH
#define	MAGIC_NBR	(0x0453616D)
#define	PACKET_SIZE	(128)
#define	HEADER_SIZE	(6 * sizeof(int))

#include <iostream>
#include <string>
#include <list>

typedef struct		s_pkt
{
  int			magicNbr;
  int			seq;
  int			ack;
  int			ackBF;
  int			key;
  int			argLength;
  char			args[PACKET_SIZE - HEADER_SIZE];
}			t_pkt;

typedef	struct		s_pkt_data
{
  std::size_t	seq;
  std::size_t	sec;
  std::size_t	usec;
}			t_pkt_data;

class PacketQueue : public std::list<t_pkt_data>
{
 public:
  bool		exists(std::size_t) const;
  void		insertSorted(const t_pkt_data &);
};

#endif
