/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 TELEMATICS LAB, DEI - Politecnico di Bari
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Nicholas Mirizzi - n.mirizzi1@studenti.poliba.it
 *         Simona Massari - s.massari1@studenti.poliba.it
 */

#ifndef TRAFFIC_STEERING_INFO_H
#define TRAFFIC_STEERING_INFO_H


#include <vector>
#include <ns3/core-module.h>
#include "ns3/mec-entity-ue.h"

namespace ns3 {

  class UserEquipment;

class TrafficSteeringInfo : public Object
{
public:
  static TypeId GetTypeId (void);

  TrafficSteeringInfo ();
  virtual ~TrafficSteeringInfo ();

private:
  Ptr<UserEquipment> m_ue;
  uint64_t m_appInstanceId;
  double m_guaranteedUplink;
  double m_guaranteedDownlink;
  bool m_state;

public:
  Ptr<UserEquipment> GetUe (void);
  void SetUe (Ptr<UserEquipment> ue);
  uint64_t GetAppInstanceId (void);
  void SetAppInstanceId (uint64_t appInstanceId);
  double GetGuaranteedUplink (void);
  void SetGuaranteedUplink (double guaranteedUplink);
  double GetGuaranteedDownlink (void);
  void SetGuaranteedDownlink (double guaranteedDownlink);
  bool GetState (void);
  void SetState (bool state);
};
} // end namespace ns3

#endif /* TRAFFIC_STEERING_INFO_H */

