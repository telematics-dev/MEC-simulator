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

#ifndef MEC_ENTITY_APP_H
#define MEC_ENTITY_APP_H

#include <string>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-entity-mec-plataform.h"
#include "mec-delay-model.h"
#include "mec-service-ams.h"
#include "mec-service-rnis.h"
#include "mec-entity.h"



namespace ns3 {

class MecPlataform;
class ApplicationMobilityService;
class CreateAppMobilityServiceResponse;
class AppReadyConfirmationResponse;

class MecApp : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  MecApp (Ptr<MecDelayModel> delay);
  virtual ~MecApp ();

private:
  uint64_t m_appInstanceId;
  uint64_t m_imsi;
  Ptr<AppD> m_appD;
  Ptr<MecPlataform> m_mecPlataform;
  Ptr<ClientApp> m_client;
//  Ptr<ApplicationMobilityService> m_ams;
//  Ptr<RadioNetworkInformationService> m_rnis;
public:
  void SetAppD (Ptr<AppD> appD);
  Ptr<MecPlataform> GetMecPlataform ( void);
  void SetMecPlataform ( Ptr<MecPlataform> mp);
  Ptr<AppD> GetAppD (void);
  void SetAppInstanceId (uint64_t appInstanceId);
  uint64_t GetAppInstanceID (void);
  void SetUeImsi (uint64_t imsi); // convert to app context
  uint64_t GetUeImsi (void);

  void SendAppReadyConfNotification (void);
  void ProcessAppReadyConfNotificationResposne(Ptr<AppReadyConfirmationResponse> response);
  void ProcessAppTerminationNotification(void);
  void SendAppTerminationConfirmation (void);

  void SendRegisterAppMobilityRequest (void);
  void SendUnsubscribeAppMobilityRequest (void);
//  void SendRegisterRnisRequest (void);
//  void SendUnsubscribeRnisRequest (void);

  void ProcessTaskOffloadingRequest(Ptr<TaskOffloading> task);
  void SendTaskOffloadingResponse(Ptr<TaskOffloading> task);
};
}
#endif /* MEC_ENTITY_APP_H */
