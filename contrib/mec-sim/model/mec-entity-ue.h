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

#ifndef MEC_ENTITY_UE_H
#define MEC_ENTITY_UE_H

#include <string.h>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include <map>
#include "mec-new-types.h"
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-delay-model.h"
#include "mec-entity-ualcmp.h"
#include "mec-entity-bs.h"
#include <ns3/propagation-loss-model.h>
#include <ns3/mobility-model.h>
#include "mec-entity-container.h"
#include "client-app.h"

namespace ns3 {

class UserApplicationLcmProxy;
class DeleteAppContextResponse;
class BaseStation;
class MecMobilityManagement;
class ClientApp;

class UserEquipment : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  UserEquipment ();
  virtual ~UserEquipment ();

  struct ClientAppInfo
  {
    std::string contextId;
    Ptr<AppContext> context;
    Ptr<ClientApp> clientApp;
  };

private:
  std::list<ClientAppInfo> m_clientAppList;
  Ptr<UserApplicationLcmProxy> m_ualcmp;


public:

  Ptr<AppContext> CreateAppContext (Ptr<AppD> appD);
  void AddClientApp (ClientAppInfo clientApp);
  void DeleteClientApp (std::string contextId);
  ClientAppInfo FindClientApp (std::string contextId);
  Ptr<UserApplicationLcmProxy> GetUalcmp (void);
  void SetUalcmp (Ptr<UserApplicationLcmProxy> ualcmp);

  // AppContext

  void SendCreateAppContextRequest(Ptr<AppContext> appContext);
  void ProcessCreateAppContextResponse(Ptr<CreateAppContextResponse> response);

  void SendDeleteAppContextRequest(std::string contextId);
  void ProcessDeleteAppContextResponse(Ptr<DeleteAppContextResponse> response);

  void ProcessUpdateAppContextNotification(Ptr<UpdateAppContextNotification> notification);


//  MOBILITY ///

private:
// Mobility
  Ptr<BaseStation> m_bs;
  double m_txPower;
  double m_txAntennaGain;
  int m_cqi;
  Ptr<MobilityModel> m_mob;
  Ptr<PropagationLossModel> m_propagationLossModel;
  Ptr<MecEntityContainer> m_bsList;
  double m_handoverMargin;

public:
//Mobility
  Ptr<MobilityModel> GetMob (void);
  void SetMob (Ptr<MobilityModel> mob);
  int GetCqi();
  Ptr<BaseStation> GetTargetBs (void);
  void SetTargetBs (Ptr<BaseStation> bs);
  Ptr<MecEntityContainer> GetBsList (void);
  void SetBsList (Ptr<MecEntityContainer> bsList);
  Ptr<PropagationLossModel> GetPropagationLossModel (void);
  void SetPropagationLossModel (Ptr<PropagationLossModel> propLossMod);
  double GetTxPower (void);
  void SetTxPower (double txPower);
  double GetTxAntennaGain (void);
  void SetTxAntennaGain (double txAntennaGain);

  int FromSinrToCqi (double sinr);
  void UpdateCqi (void);
  bool Handover(void);
  void CourseChange (Ptr<const MobilityModel> mobility);
  void SendRnisUpdate(Ptr<BaseStation> srcBs, Ptr<BaseStation> trgBs);
};

}

#endif /* MEC_ENTITY_UE_H */

