//
// ReliabilitySystem.hh for ReliabilitySystem in /home/lopez_t/rtype/API
// 
// Made by Thibaut Lopez
// Login   <lopez_t@epitech.net>
// 
// Started on  Mon Nov 30 15:23:28 2015 Thibaut Lopez
// Last update Thu Dec  3 11:32:49 2015 Thibaut Lopez
//

#ifndef	RELIABILITYSYSTEM_HH
#define	RELIABILITYSYSTEM_HH
#define EPSILON	(0.001f)

#include "PacketQueue.hh"
#include "STTime.hh"
#include <vector>

class ReliabilitySystem
{
 private:
  std::size_t		_localSeq;
  std::size_t		_remoteSeq;
  std::size_t		_sentPkts;
  std::size_t		_recvPkts;
  std::size_t		_lostPkts;
  std::size_t		_ackedPkts;
  float			_sentBandwidth;
  float			_ackedBandwidth;
  float			_rtt;
  float			_rttMax;
  std::vector<std::size_t>	_acks;
  PacketQueue		_sent;
  PacketQueue		_pAck;
  PacketQueue		_recved;
  PacketQueue		_acked;
  float			_getTime(const std::size_t &, const std::size_t &) const;
  int			_indexForSeq(const std::size_t &, const std::size_t &) const;
  void			_updateQueues();
  void			_updateStats();

 public:
  ReliabilitySystem();
  void			reset();
  void			sent();
  void			received(const std::size_t &);
  std::size_t		generateAckBF() const;
  void			processAck(const std::size_t &, const std::size_t &);
  void			update();
  std::size_t		getLocalSeq() const;
  std::size_t		getRemoteSeq() const;
  std::size_t		getSentPkts() const;
  std::size_t		getReceivedPkts() const;
  std::size_t		getLostPkts() const;
  std::size_t		getAckedPkts() const;
  float			getSentBandwidth() const;
  float			getAckedBandwidth() const;
  float			getRoundTripTime() const;
};

#endif
