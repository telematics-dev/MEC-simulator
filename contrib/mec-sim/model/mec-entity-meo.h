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

#ifndef MEC_ENTITY_MEO_H
#define MEC_ENTITY_MEO_H

#include <string.h>
#include <ns3/ptr.h>
#include <map>
#include <list>
#include "mec-entity.h"
#include "mec-new-types.h"
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-entity-oss.h"
#include "mec-delay-model.h"
#include "mec-entity-virtualizzation-infrastructure-manager.h"
#include "mec-entity-mec-plataform-manager.h"
#include "mec-entity-ue.h"
#include "app-repository.h"
#include "mec-host-container.h"
#include "mec-entity-host.h"




namespace ns3 {

class OperationsSupportSystem;
class MecPlataformManager;
class VirtualizzationInfrastructureManager;
class UserEquipment;
class AppRepository;
class AppContext;
class CreateAppContextRequest;
class DeleteAppContextRequest;
class InstantiateAppResponse;
class CreateAppInstanceIdentifierResponse;
class OnboardAppPkgRequest;
class MobilityProcedureNotification;
class FetchAppPackageRequest;
class MecHostEntity;

class MultiaccessEdgeOrchestrator : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  MultiaccessEdgeOrchestrator ();
  virtual ~MultiaccessEdgeOrchestrator ();

  Ptr<OperationsSupportSystem> GetOss (void);
  void SetOss (Ptr<OperationsSupportSystem> oss);
  void SetAppRepository (Ptr<AppRepository> appRepository);
  Ptr<AppRepository> GetAppRepository (void);

  class Instance : public Object
  {
  public:
    Ptr<AppContext> appContext;
    Ptr<MecHostEntity> mecHost;
    Ptr<AppInstanceInfo> instanceInfo;
    Ptr<VirtualResourceInstance> virtualResource;
    Ptr<MecApp> mecApp;
    Ptr<AppD> appD;
    std::string state;
    bool mobility;
  };

//  Istance data
  typedef std::list<Ptr<Instance>>::const_iterator Iterator;
  void AddIstanceData (Ptr<AppContext> appContext, std::string state);
  void DeleteIstanceData (Ptr<AppContext> appContext, std::string state);
  Ptr<Instance> GetIstanceData (Ptr<AppContext> appContext, std::string state);
  Ptr<Instance> GetIstanceData (std::string appContextId, std::string state);
  Ptr<Instance> GetIstanceData (Ptr<MecApp> mecApp);
  Ptr<Instance> GetIstanceData (Ptr<AppInstanceInfo> instance);
// AppPkgInfo
  int16_t AddAppPkgInfo (uint64_t appPkgId, Ptr<AppPkgInfo> appPkgInfo);
  int16_t DeleteAppPkgInfo (uint64_t appPkgId);
  std::pair<Ptr<AppPkgInfo> , int16_t> FindAppPkgInfo (uint64_t appPkgId);
  std::pair<Ptr<AppPkgInfo> , int16_t> FindAppPkgInfo (std::string appName, std::string appSoftVersion);
  std::map<uint64_t, Ptr<AppPkgInfo>> GetAppPkgInfoList(void);

// App Istanziation
  void ProcessCreateAppContextRequest(Ptr<CreateAppContextRequest> request);
  void SendPreAllocateVirtualizedResRequest(Ptr<AppContext> appContext, Ptr<MecHostEntity> bestHost);
  void ProcessPreAllocateVirtualizedResourceResponse(Ptr<AllocateVirtualizedResResponse> response, Ptr<AppContext> appContext);
  void SendCreateAppInstanceIdentifierRequest(Ptr<AppContext> appContext, Ptr<MecHostEntity> bestHost);
  void ProcessCreateAppInstanceIdentifierResponse(Ptr<CreateAppInstanceIdentifierResponse> response, Ptr<AppContext> appContext);
  void SendCreateAppInstanceRequest(Ptr<AppInstanceInfo> appInstanceInfo, Ptr<AppContext> appContext);
  void ProcessInstantiateAppResponse (Ptr<InstantiateAppResponse> response);
  void SendCreateAppContextResponse(Ptr<AppContext> appContext, int16_t respCode, std::string problemDetails);

//  App Termination
  void ProcessDeleteAppContextRequest(Ptr<DeleteAppContextRequest> request);
  void SendTerminateAppRequest(Ptr<AppInstanceInfo> instance);
  void ProcessTerminateAppResponse(Ptr<TerminateAppResponse> response);
  void SendDeleteAppContextResponse(Ptr<AppContext> appContext, int16_t respCode, std::string problemDetails);

  // Mobility
  void ProcessMobilityProcedureNotification (Ptr<MobilityProcedureNotification> notification);
  void SendMobilityProcedureNotificationResponse(Ptr<MecApp> srcMecApp, Ptr<MecApp> trgMecApp, int16_t respCode, std::string problemDetails);
  void ProcessMobilityProcedureTerminateRequest (Ptr<MobilityProcedureTerminateRequest> request);
  void SendUpdateAppContextNotification(Ptr<AppContext> appContext);
//  void SendUpdateAppContextNotification();

  // AppOnboarding
  Time Onboarding(Ptr<AppD> appD);
  void ProcessFetchAppPackageResponse (Ptr<FetchAppPackageRequest> request, uint64_t hostId, MsgList requestList);
  void SendFetchAppPackageResponse (Ptr<AppPkgInfo> appPkgInfo, int16_t respCode,  uint64_t hostId, MsgList requestList);

  //
  bool IsAppOnboarded(Ptr<AppContext> appContext);
  void IstantiateApplication(Ptr<AppContext> appContext);
  void TerminateApplication(Ptr<AppContext> appContext);
  Ptr<MecHostEntity> FindBestMecHost(Ptr<AppContext> appContext);

private:
  Ptr<OperationsSupportSystem> m_oss;
  Ptr<AppRepository> m_appRepository;
  std::list<Ptr<Instance>> m_instanceDataList;
  std::map<uint64_t, Ptr<AppPkgInfo>> m_appPkgInfoList;

};

}

#endif /* MEC_ENTITY_MEO_H */

