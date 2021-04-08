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

#ifndef MEC_ENTITY_MEC_PLATAFORM_MANAGER_H
#define MEC_ENTITY_MEC_PLATAFORM_MANAGER_H

#include <string>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-new-types.h"
#include "mec-entity-meo.h"
#include "mec-delay-model.h"
#include "mec-entity-virtualizzation-infrastructure-manager.h"
#include "mec-entity-mec-plataform.h"
#include "mec-entity.h"
#include "mec-entity-host.h"
#include "mec-app-container.h"


namespace ns3 {

class MecAppInstanceConfigurationResponse;
class VirtualizzationInfrastructureManager;
class MecPlataform;
class MobilityProcedureNotificationResponse;
class MobilityProcedureTerminateResponse;
class MobilityProcedureTerminateRequest;
class InstantiateAppRequest;
class TerminateAppRequest;
class TerminateAppResponse;
class FetchAppPackageResponse;
class TerminateVirtualResourceResponse;
class AllocateVirtualizedResResponse;

class MecPlataformManager : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  MecPlataformManager ();
  virtual ~MecPlataformManager ();


// AppPkg
  int16_t AddAppPkg (uint64_t appPkgId, Ptr<AppPkgInfo> appPkgInfo);
  int16_t DeleteAppPkg (uint64_t appPkgId);
  std::pair<Ptr<AppPkgInfo> , int16_t> FindAppPkg (uint64_t appPkgId);
  Ptr<MecPlataform> GetMep (void);
  Ptr<MultiaccessEdgeOrchestrator> GetMeo (void);
  Ptr<VirtualizzationInfrastructureManager> GetVim (void);

  //Application instantiation

  void ProcessCreateAppInstanceIdentifierRequest(Ptr<CreateAppInstanceIdentifierRequest> request, Ptr<AppContext> appContext);
  void SendCreateAppInstanceIdentifierResponse(uint64_t appInstanceId, Ptr<AppContext> appContext);
  void ProcessAppInstanceRequest(Ptr<InstantiateAppRequest> request, Ptr<AppContext> appContext);
  void StartApp (Ptr<InstantiateAppRequest> request, Ptr<AppContext> appContext);
  void SendAllocateVirtualizedResourceRequest(Ptr<InstantiateAppRequest> request, Ptr<AppContext> appContext);
  void ProcessAllocateVirtualizedResourceResponse(Ptr<AllocateVirtualizedResResponse> response, MsgList requestList);
  void SendMecAppInstanceConfigurationRequest(Ptr<InstantiateAppRequest> request, Ptr<AppContext> appContext);
  void ProcessMecAppInstanceConfigurationResponse(Ptr<MecAppInstanceConfigurationResponse> response);
  void SendAppInstanceResponse(Ptr<MecApp> referenceUri, int16_t respCode);
// Da sistemare
  void SendFetchAppPackageRequest(MsgList requestList);
  void ProcessFetchAppPackageResponse(Ptr<FetchAppPackageResponse> response, MsgList requestList);

  // Mec App termination
  void ForwardTerminateAppRequest (Ptr<TerminateAppRequest> request);
  void ProcessTerminateAppResponse (Ptr<TerminateAppResponse> response);
  void SendTerminateVirtualResourceRequest(Ptr<AppInstanceInfo> appInstance);
  void ProcessTerminateVirtualResourceResponse(Ptr<TerminateVirtualResourceResponse> response);
  void ForwardTerminateAppResponse(Ptr<TerminateAppResponse> mepResponse);

  void ForwardMobilityProcedureNotification (Ptr<MobilityProcedureNotification> notification);
  void ForwardMobilityProcedureNotificationResponse (Ptr<MobilityProcedureNotificationResponse> response);
  void ForwardMobilityProcedureTerminateRequest (Ptr<MobilityProcedureTerminateRequest> request);
  void ForwardMobilityProcedureTerminateResponse (Ptr<MobilityProcedureTerminateResponse> response);


private:
  std::map<uint64_t, Ptr<AppPkgInfo>> m_appPkgList;
  uint64_t m_appInstanceIdCounter;
  uint64_t m_mecAppIdCounter;

};

}
#endif /* MEC_ENTITY_MEC_PLATAFORM_MANAGER_H */
