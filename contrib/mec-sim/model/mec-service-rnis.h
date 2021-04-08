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

#ifndef MEC_SERVICE_RNIS_H
#define MEC_SERVICE_RNIS_H

#include <string>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-entity-mec-plataform.h"
#include "mec-delay-model.h"
#include "mec-service-ams.h"
#include "mec-entity-app.h"
#include "mec-service.h"




namespace ns3 {

class MecPlataform;
class ApplicationMobilityService;
class RniSubscription;
class CreateRniSubscriptionRequest;
class UnsubscribeFromServiceRequest;
class ServiceRegistrationInfo;
class CellChangeNotification;

class RadioNetworkInformationService : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  RadioNetworkInformationService ();
  virtual ~RadioNetworkInformationService ();

  typedef std::list<Ptr<ServiceRegistrationInfo>>::const_iterator Iterator;

  void ProcessSubscriptionRequest(Ptr<ServiceRegistrationInfo> regInfo);
  void ProcessUnsubscriptionRequest(Ptr<MecApp> mecApp);
  Ptr<ApplicationMobilityService>  GetAms (void);
  void CallBackRnisCellChange(Ptr<CellChangeNotification> notification);

private:
  std::list<Ptr<ServiceRegistrationInfo>> m_registrationInstanceList;

  //public:

////  void ProcessCreateRniSubscriptionRequest(Ptr<CreateRniSubscriptionRequest> request);
////  void ProcessUnsubscribeRnisRequest(Ptr<UnsubscribeFromServiceRequest> request);
////  void SendUnsubscribeRnisResponse(uint64_t appInstanceId, int16_t respCode, std::string problemDetails);
//  void CallBackRnisTrafficSteeringState(uint64_t imsi, uint64_t BsId, bool state);

};

}
#endif /* MEC_SERVICE_RNIS_H */
