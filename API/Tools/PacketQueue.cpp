//
// PacketQueue.cpp for PacketQueue in /home/lopez_t/rtype/API
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Mon Nov 30 15:04:01 2015 Thibaut Lopez
// Last update Tue Dec  1 14:45:21 2015 Thibaut Lopez
//

#include "PacketQueue.hh"

bool			PacketQueue::exists(std::size_t seq) const
{
  const_iterator	it;

  it = this->begin();
  while (it != this->end())
    {
      if (it->seq == seq)
	return (true);
      ++it;
    }
  return (false);
}

void			PacketQueue::insertSorted(const t_pkt_data &p)
{
  iterator		it;

  it = this->begin();
  while (it != end())
    {
      if (it->seq > p.seq)
	{
	  this->insert(it, p);
	  return ;
	}
      ++it;
    }
  this->push_back(p);
}
