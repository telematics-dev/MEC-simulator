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

#ifndef MEC_ENTITY_MEC_PLATAFORM_H
#define MEC_ENTITY_MEC_PLATAFORM_H

#include <string.h>
#include "ns3/node.h"
#include "ns3/ptr.h"
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-entity-meo.h"
#include "mec-entity-app.h"
#include "mec-service-ams.h"
#include "mec-service-rnis.h"
#include "mec-entity.h"




namespace ns3 {

class MultiaccessEdgeOrchestrator;
class MecApp;
class MecPlataformManager;
class MecAppInstanceConfigurationRequest;
class TrafficSteeringInfo;
class AppReadyConfirmation;


class MecPlataform : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  MecPlataform ();
  virtual ~MecPlataform ();


  Ptr<MultiaccessEdgeOrchestrator> GetMeo (void);
  Ptr<MecPlataformManager> GetMepm (void);
//  void SetAms (Ptr <ApplicationMobilityService> ams);
//  Ptr <ApplicationMobilityService> GetAms (void);
//  void SetRnis (Ptr<RadioNetworkInformationService> rnis);
//  Ptr<RadioNetworkInformationService> GetRnis (void);

// MecPlataformManager
  void ProcessMecAppInstanceConfigurationRequest(Ptr<MecAppInstanceConfigurationRequest> request);
  void ProcessTerminateAppRequest(Ptr<TerminateAppRequest> request);
  void SendAppTerminationNotification(Ptr<MecApp> mecApp);
  void SendsMecAppInstanceConfigurationResponse(Ptr<AppInstanceInfo> instanceInfo, Ptr<MecApp> mecApp);
  void SendTerminateAppResponse(Ptr<AppInstanceInfo> instance, int16_t respCode, std::string problemDetails);

// Mec App
  void ProcessAppReadyConfNotification(Ptr<AppReadyConfirmation> notification, Ptr<MecApp> mecApp);
  void SendAppReadyConfNotificationResponse(int respCode, Ptr<MecApp> mecApp);
  void SendAppTerminationNotification(void);
  void ProcessAppTerminationNotification(void);
  void ProcessAppTerminationConfirmation(Ptr<MecApp> mecApp);
  void DeleteMecApp(int64_t mecAppId);


private:
//  Ptr<ApplicationMobilityService> m_ams;
//  Ptr<RadioNetworkInformationService> m_rnis;

  std::map<uint64_t, Ptr<MecApp>> m_MecAppList;
};

}
#endif /* MEC_ENTITY_MEC_PLATAFORM_H */
