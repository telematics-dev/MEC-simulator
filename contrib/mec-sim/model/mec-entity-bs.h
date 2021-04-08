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

#ifndef MEC_ENTITY_BS_H
#define MEC_ENTITY_BS_H


#include "string.h"
#include "ns3/node.h"
#include "ns3/callback.h"
#include "ns3/traced-callback.h"
#include "ns3/ptr.h"
#include <map>
#include <math.h>
#include "mec-entity-ue.h"
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "ns3/mec-entity.h"
#include <ns3/mobility-model.h>
#include "mec-entity-host.h"

namespace ns3 {

  class UserEquipment;
  class MecMobilityManagement;
  class TrafficSteeringInfo;
  class MecHostEntity;
  class CellChangeNotification;

class BaseStation : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  BaseStation ();
  virtual ~BaseStation ();
  struct LinkedHost {
    uint64_t hostId;
    double latency;
    Ptr<MecHostEntity> host;
  };
  typedef std::vector<LinkedHost>::const_iterator Iterator;

private:
  std::vector<LinkedHost> m_linkedHostList;
  double m_posx;
  double m_posy;
  double m_sizecell;
  std::map<uint64_t,Ptr<UserEquipment>> m_ueList;
  double m_hb;
  double m_cf;
  double m_bandwidthUl;
  double m_bandwidthDl;
  double m_txPower;
  double m_txAntennaGain;
  Ptr<MobilityModel> m_mob;

public:
  double GetPosX (void);
  double GetPosY (void);
  double GetPosZ (void);
  double GetSizeCell (void);
  Ptr<MobilityModel> GetMob (void);
  void SetMob (Ptr<MobilityModel> mob);
  void AddActiveFlow(int appDiD);
  void DeleteActiveFlow(int appDiD);
  int GetAtiveFlow(int appDiD);

  int16_t AddUe (uint64_t imsi ,Ptr<UserEquipment> ue);
  int16_t DeleteUe (uint64_t imsi);
  std::pair<Ptr<UserEquipment>,int16_t> FindUe (uint64_t imsi);
  std::map<uint64_t, Ptr<UserEquipment>> GetUeList(void);
  void SetUeList (std::map<uint64_t, Ptr<UserEquipment>>);
  void AddLinkedHost (uint64_t hostId, double latency, Ptr<MecHostEntity> host);
  LinkedHost FindLinkedHost(uint64_t hostId);
//  Ptr<RadioNetworkInformationService> GetRnis (void);
//  void SetRnis (Ptr<RadioNetworkInformationService> rnis);

  double GetCf (void);
  void SetCf (double cf);
  double GetBandwidthUl (void);
  void SetBandwidthUl (double bandwidthUl);
  double GetBandwidthDl (void);
  void SetBandwidthDl (double bandwidthDl);
  double GetTxPower (void);
  void SetTxPower (double txPower);
  double GetTxAntennaGain (void);
  void SetTxAntennaGain (double txAntennaGain);
  void ForwardRnisUpdate(Ptr<CellChangeNotification> notification);

  void ForwardTaskOffloadingRequest(Ptr<TaskOffloading> task);
  void ForwardTaskOffloadingResponse(Ptr<TaskOffloading> task);

  int m_activeFlow[3] = {0, 0, 0};

};

} // end namespace ns3

#endif /* MEC_ENTITY_BS_H */

