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

#ifndef MEC_SERVICE_AMS_H
#define MEC_SERVICE_AMS_H

#include <string>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-entity-mec-plataform.h"
#include "mec-delay-model.h"
#include "mec-service-rnis.h"
#include <ns3/mec-service.h>


namespace ns3 {

class MecPlataform;
class MobilityProcedureNotificationResponse;
class MobilityProcedureTerminateResponse;
class UnsubscribeFromServiceResponse;
class CellChangeNotification;
class ServiceRegistrationInfo;
class RadioNetworkInformationService;

class ApplicationMobilityService : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  ApplicationMobilityService ();
  virtual ~ApplicationMobilityService ();

  typedef std::list<Ptr<ServiceRegistrationInfo>>::const_iterator Iterator;
  Ptr<RadioNetworkInformationService>  GetRnis (void);

  void ProcessSubscriptionRequest(Ptr<ServiceRegistrationInfo> regInfo);
  void ProcessUnsubscriptionRequest(Ptr<MecApp> mecApp);
  void ProcessCellChangeNotification (Ptr<CellChangeNotification> notification);
  void ProcessMobilityProcedureNotificationResponse (Ptr<MobilityProcedureNotificationResponse> notification);
  void SendMobilityProcedureTerminateRequest(Ptr<MecApp> srcMecApp, Ptr<MecApp> trgMecApp);
  void ProcessMobilityProcedureTerminateResponse(Ptr<MobilityProcedureTerminateResponse> response);

private:
  std::list<Ptr<ServiceRegistrationInfo>> m_registrationInstanceList;

};
}
#endif /* MEC_SERVICE_AMS_H */
