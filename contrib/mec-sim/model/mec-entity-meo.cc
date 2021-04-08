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

#include "mec-entity-meo.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MultiaccessEdgeOrchestrator");

TypeId MultiaccessEdgeOrchestrator::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MultiaccessEdgeOrchestrator")
    .SetParent<Object> ();
  return tid;
}

MultiaccessEdgeOrchestrator::MultiaccessEdgeOrchestrator ()
{
  NS_LOG_FUNCTION (this);
}

MultiaccessEdgeOrchestrator::~MultiaccessEdgeOrchestrator ()
{
  NS_LOG_FUNCTION (this);
}

void
MultiaccessEdgeOrchestrator::SetOss(Ptr<OperationsSupportSystem> oss)
{
  NS_LOG_FUNCTION (this << oss);
  m_oss = oss;
}

Ptr<OperationsSupportSystem>
MultiaccessEdgeOrchestrator::GetOss()
{
  NS_LOG_FUNCTION (this);
  if(m_oss == 0)
    {
      Ptr<OperationsSupportSystem> oss = this->GetNode()->GetObject<OperationsSupportSystem>();
      if(oss==0)
        {
          NS_LOG_ERROR (this << "set OSS pointer");
          return oss;
        }
      else
        {
          return oss;
        }
    }
  else
    {
      return m_oss;
    }
}


void
MultiaccessEdgeOrchestrator::SetAppRepository (Ptr<AppRepository> appRepository)
{
  NS_LOG_FUNCTION (this << appRepository);
  m_appRepository=appRepository;
}

Ptr<AppRepository>
MultiaccessEdgeOrchestrator::GetAppRepository ()
{
  NS_LOG_FUNCTION (this);
  if(m_appRepository == 0)
    {
      Ptr<AppRepository> appRepository = this->GetNode()->GetObject<AppRepository>();
      if(appRepository==0)
        {
          NS_LOG_ERROR (this << "set appRepository pointer");
          return appRepository;
        }
      else
        {
          return appRepository;
        }
    }
  else
    {
      return m_appRepository;
    }
}


void
MultiaccessEdgeOrchestrator::AddIstanceData (Ptr<AppContext> appContext, std::string state)
{
  Ptr<MultiaccessEdgeOrchestrator::Instance> new_ist = CreateObject<MultiaccessEdgeOrchestrator::Instance>();
  new_ist->appContext = appContext;
  new_ist->appD = 0;
  new_ist->instanceInfo = 0;
  new_ist->mecApp = 0;
  new_ist->mecHost = 0;
  new_ist->virtualResource = 0;
  new_ist->state = state;
  new_ist->mobility =0;
  m_instanceDataList.push_back(new_ist);
}
void
MultiaccessEdgeOrchestrator::DeleteIstanceData (Ptr<AppContext> appContext, std::string state)
{
  for(MultiaccessEdgeOrchestrator::Iterator it = m_instanceDataList.begin(); it != m_instanceDataList.end(); it++)
    {
      if((*it)->appContext == appContext && (*it)->state == state)
        {
          m_instanceDataList.erase(it);
          break;
        }
    }
}

Ptr<MultiaccessEdgeOrchestrator::Instance>
MultiaccessEdgeOrchestrator::GetIstanceData (Ptr<AppContext> appContext, std::string state)
{
  Ptr<MultiaccessEdgeOrchestrator::Instance> ist = 0;
  for(MultiaccessEdgeOrchestrator::Iterator it = m_instanceDataList.begin(); it != m_instanceDataList.end(); it++)
    {
      if((*it)->appContext == appContext && (*it)->state == state)
        {
          ist = *it;
          return ist;
        }
    }
  return ist;
}

Ptr<MultiaccessEdgeOrchestrator::Instance>
MultiaccessEdgeOrchestrator::GetIstanceData (std::string appContextId, std::string state)
{
  Ptr<MultiaccessEdgeOrchestrator::Instance> ist = 0;
  for(MultiaccessEdgeOrchestrator::Iterator it = m_instanceDataList.begin(); it != m_instanceDataList.end(); it++)
    {
      if((*it)->appContext->GetContextId() == appContextId && (*it)->state == state)
        {
          ist = *it;
          return ist;
        }
    }
  return ist;
}



Ptr<MultiaccessEdgeOrchestrator::Instance>
MultiaccessEdgeOrchestrator::GetIstanceData (Ptr<MecApp> mecApp)
{
  Ptr<MultiaccessEdgeOrchestrator::Instance> ist = 0;
  for(MultiaccessEdgeOrchestrator::Iterator it = m_instanceDataList.begin(); it != m_instanceDataList.end(); it++)
    {
      if((*it)->mecApp == mecApp)
        {
          ist = *it;
          return ist;
        }
    }
  return ist;
}

Ptr<MultiaccessEdgeOrchestrator::Instance>
MultiaccessEdgeOrchestrator::GetIstanceData (Ptr<AppInstanceInfo> instance)
{
  Ptr<MultiaccessEdgeOrchestrator::Instance> ist = 0;
  for(MultiaccessEdgeOrchestrator::Iterator it = m_instanceDataList.begin(); it != m_instanceDataList.end(); it++)
    {
      if((*it)->instanceInfo == instance)
        {
          ist = *it;
          return ist;
        }
    }
  return ist;
}
















int16_t
MultiaccessEdgeOrchestrator::AddAppPkgInfo (uint64_t appPkgId, Ptr<AppPkgInfo> appPkgInfo)
{
  NS_LOG_FUNCTION (this << appPkgId << appPkgInfo);
  int16_t respCode = FindAppPkgInfo(appPkgId).second;
  if (respCode == 404)
    {
      m_appPkgInfoList.insert ( std::pair <uint64_t, Ptr<AppPkgInfo>> (appPkgId,appPkgInfo) );

      return 201;
    }
  else
    {
      return 409;
    }
}

int16_t
MultiaccessEdgeOrchestrator::DeleteAppPkgInfo (uint64_t appPkgId)
{
  NS_LOG_FUNCTION (this << appPkgId);
  int16_t respCode = FindAppPkgInfo(appPkgId).second;
  if (respCode == 200)
    {
      m_appPkgInfoList.erase (appPkgId);
      return 200;
    }
  else
    {
      return 404;
    }
}

std::pair<Ptr<AppPkgInfo> , int16_t>
MultiaccessEdgeOrchestrator::FindAppPkgInfo (uint64_t appPkgId)
{
  NS_LOG_FUNCTION (this << appPkgId);
  std::map<uint64_t, Ptr<AppPkgInfo>>::iterator appInfo_it = m_appPkgInfoList.find (appPkgId);
   if(appInfo_it != m_appPkgInfoList.end ())
     {
       return ( std::make_pair(appInfo_it->second, 200));
     }

   else
     {
     NS_LOG_FUNCTION ("unknown appPkgId " << appPkgId);
     Ptr<AppPkgInfo> nan =0 ;
     return ( std::make_pair(nan, 404));
     }
}

std::pair<Ptr<AppPkgInfo> , int16_t>
MultiaccessEdgeOrchestrator::FindAppPkgInfo (std::string appName, std::string appSoftVersion)
{
  NS_LOG_FUNCTION (this << appName << appSoftVersion);
  std::map<uint64_t, Ptr<AppPkgInfo>>::iterator appInfo_it;
  std::map<uint64_t, Ptr<AppPkgInfo>>::iterator best_appInfo_it = m_appPkgInfoList.end();

  for(appInfo_it= m_appPkgInfoList.begin(); appInfo_it!=m_appPkgInfoList.end();appInfo_it++)
    {
      if(appInfo_it->second->GetAppName() == appName && appInfo_it->second->GetSoftwareVersion() == appSoftVersion)
	{
	  best_appInfo_it = appInfo_it;
	}
    }

   if(appInfo_it != m_appPkgInfoList.end ())
     {
       return ( std::make_pair(best_appInfo_it->second, 200));
     }

   else
     {
       NS_LOG_FUNCTION ("unknown appName " << appName);
       return ( std::make_pair(best_appInfo_it->second, 404));
     }
}

std::map<uint64_t, Ptr<AppPkgInfo>>
MultiaccessEdgeOrchestrator::GetAppPkgInfoList(void)
{
 return m_appPkgInfoList;
}



// Istantiation

void
MultiaccessEdgeOrchestrator::ProcessCreateAppContextRequest(Ptr<CreateAppContextRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Process\t") << request->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") << request->GetAppContext()->GetContextId() <<")");

  Ptr<AppContext> appContext = request->GetAppContext();
  Ptr<AppD> new_appD = GetAppRepository()->FindApp(appContext->GetAppDId()).first;

  AddIstanceData(appContext, "Instantiation");
  GetIstanceData(appContext, "Instantiation")->appD = new_appD;

  IstantiateApplication(appContext);

}

void
MultiaccessEdgeOrchestrator::SendPreAllocateVirtualizedResRequest(Ptr<AppContext> appContext, Ptr<MecHostEntity> bestHost)
{
  Ptr<AllocateVirtualizedResRequest> reqPreAlloc = CreateObject<AllocateVirtualizedResRequest>();
  Ptr<VirtualResourceInstance> resourceInstance = CreateObject<VirtualResourceInstance>();
  Ptr<VirtualResourceDescriptor> virtualResourceDescriptor = GetIstanceData(appContext, "Instantiation")->appD->GetVirtualResourceDescriptor();

  reqPreAlloc->SetVirtualResourceInstance(resourceInstance);
  resourceInstance->SetVirResInstId(0);
  resourceInstance->SetHostId(bestHost->GetId());
  resourceInstance->SetVirtualResource(virtualResourceDescriptor);
  resourceInstance->SetAllocationType(1); //  Pre-allocation
  resourceInstance->CreateUserData(0);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << ")\t Send \t\t" << reqPreAlloc->GetInstanceTypeId().GetName()
  << "(VirResInstId: " << resourceInstance->GetVirResInstId()
  << ", AllocationType: PreAllocation"
  << ")");
//  bestHost->GetObject<VirtualizzationInfrastructureManager>()->ProcessPreAllocateVirtualizedResourceRequest(reqPreAlloc, appContext);
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &VirtualizzationInfrastructureManager::ProcessPreAllocateVirtualizedResourceRequest, bestHost->GetObject<VirtualizzationInfrastructureManager>(), reqPreAlloc, appContext);
}

void
MultiaccessEdgeOrchestrator::ProcessPreAllocateVirtualizedResourceResponse(Ptr<AllocateVirtualizedResResponse> response, Ptr<AppContext> appContext)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Process\t") << response->GetInstanceTypeId().GetName()
  << std::string("(VirResInstId: ") << response->GetVirtualResourceInstance()->GetVirResInstId() <<")");

  GetIstanceData(appContext, "Instantiation")->virtualResource = response->GetVirtualResourceInstance();

}

void
MultiaccessEdgeOrchestrator::SendCreateAppInstanceIdentifierRequest(Ptr<AppContext> appContext, Ptr<MecHostEntity> bestHost)
{
  Ptr<AppD> appD = GetIstanceData(appContext, "Instantiation")->appD;
  Ptr<CreateAppInstanceIdentifierRequest> request = CreateObject<CreateAppInstanceIdentifierRequest> ();
  request->SetAppDId(appD->GetAppDId());
  request->SetAppInstanceName(appD->GetAppName());
  request->SetAppInstanceDescription(appD->GetAppDescription());

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << ")\t Send \t\t" << request->GetInstanceTypeId().GetName()
  << "(AppDId: " << request->GetAppDId()
  << ", AppInstanceName: " << request->GetAppInstanceName()
  << ", AppInstanceDescription: " << request->GetAppInstanceDescription()
  << ")");

//  bestHost->GetObject<MecPlataformManager>()->ProcessCreateAppInstanceIdentifierRequest(request, appContext);
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataformManager::ProcessCreateAppInstanceIdentifierRequest, bestHost->GetObject<MecPlataformManager>(), request, appContext);
}

void
MultiaccessEdgeOrchestrator::ProcessCreateAppInstanceIdentifierResponse(Ptr<CreateAppInstanceIdentifierResponse> response, Ptr<AppContext> appContext)
{


  Ptr<MecHostEntity> host = GetIstanceData(appContext, "Instantiation")->mecHost;
  Ptr<AppD> appD = GetIstanceData(appContext, "Instantiation")->appD;
  Ptr<AppInstanceInfo> instance = CreateObject<AppInstanceInfo>();

  instance->SetAppInstanceId(response->GetAppInstanceId());
  instance->SetAppInstanceName(appD->GetAppName());
  instance->SetAppInstanceDescription(appD->GetAppDescription());
  instance->SetAppDId(appD->GetAppDId());
  instance->SetAppProvider(appD->GetAppProvider());
  instance->SetAppName(appD->GetAppName());
  instance->SetContextId(appContext->GetContextId());
  instance->SetInstantiationState(0);
  instance->SetOperationalState(0);
  instance->SetHostId(host->GetId());
  GetIstanceData(appContext, "Instantiation")->instanceInfo = instance;

      NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
      << ")\t Process \t" << response->GetInstanceTypeId().GetName()
      << "(InstanceInfoId: " << instance->GetAppInstanceId()
      << ", AppPkgId: " << instance->GetAppPkgId()
      << ", AppDId: " << instance->GetAppDId()
      << ", ContextId: " << appContext->GetContextId()
      << ")");

      SendCreateAppInstanceRequest(instance, appContext);
}

void
MultiaccessEdgeOrchestrator::SendCreateAppInstanceRequest(Ptr<AppInstanceInfo> appInstanceInfo, Ptr<AppContext> appContext)
{
  Ptr<InstantiateAppRequest> request = CreateObject<InstantiateAppRequest> ();
  request->SetAppInstanceId(appInstanceInfo->GetAppInstanceId());
  Ptr<AppD> appD = GetIstanceData(appContext, "Instantiation")->appD;
  request->SetVirtualResourceDescriptor(appD->GetVirtualResourceDescriptor()) ;
  request->SetSelectedMECHostInfo(appInstanceInfo->GetHostId());

  Ptr<MecPlataformManager> dest = GetIstanceData(appContext, "Instantiation")->mecHost->GetObject<MecPlataformManager>();

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << ")\t Send \t\t" << request->GetInstanceTypeId().GetName()
  << "(AppInstanceId: " << request->GetAppInstanceId()
  << ")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataformManager::ProcessAppInstanceRequest, dest, request, appContext);

}

void
MultiaccessEdgeOrchestrator::ProcessInstantiateAppResponse (Ptr<InstantiateAppResponse> response)
{

  std::string state = GetIstanceData(response->GetReferenceUri())->state;
  bool mobility = GetIstanceData(response->GetReferenceUri())->mobility;
  Ptr<AppContext> appContext = GetIstanceData(response->GetReferenceUri())->appContext;
  appContext->SetReferenceUri(response->GetReferenceUri());
  Ptr<AppInstanceInfo> instance = GetIstanceData(response->GetReferenceUri())->instanceInfo;
  instance->SetOperationalState(1);
  GetIstanceData(response->GetReferenceUri())->state = "Ready";

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << ")\t Process \t" << response->GetInstanceTypeId().GetName()
  << "(InstanceInfoId: " << instance->GetAppInstanceId()
  << ", AppPkgId: " << instance->GetAppPkgId()
  << ", AppDId: " << instance->GetAppDId()
  << ", ContextId: " << appContext->GetContextId()
  << ")");

  if(state == "Instantiation" && mobility == 0)
    {
      SendCreateAppContextResponse(appContext, 201, "MecApp successfull instantiate!");
    }
  else if(state == "Instantiation" && mobility == 1)
    {
      Ptr<MecApp> srcMecApp = GetIstanceData(appContext, "WaitingTermination")->mecApp;
      Ptr<MecApp> trgMecApp = appContext->GetReferenceUri();

      SendMobilityProcedureNotificationResponse(srcMecApp, trgMecApp, 201, "MecApp successfull instantiate!");
    }

}

void
MultiaccessEdgeOrchestrator::SendCreateAppContextResponse(Ptr<AppContext> appContext, int16_t respCode, std::string problemDetails)
{
  Ptr<CreateAppContextResponse> responseOss =CreateObject<CreateAppContextResponse> ();
  responseOss->SetAppContext(appContext);
  responseOss->SetRespCode(respCode);
  responseOss->SetProblemDetails(problemDetails);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Send \t\t") + responseOss->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + responseOss->GetAppContext()->GetContextId()
  << ", referenceURI: " << responseOss->GetAppContext()->GetReferenceUri()
  << ", respCode: " << responseOss->GetRespCode()
  << ", ProblemDetails: " << responseOss->GetProblemDetails() <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &OperationsSupportSystem::ForwardCreateAppContextResponse, GetOss(),responseOss);
}


// App Termiantion
void
MultiaccessEdgeOrchestrator::ProcessDeleteAppContextRequest(Ptr<DeleteAppContextRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Process\t") + request->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + request->GetContextId() <<")");
  if(GetIstanceData (request->GetContextId(), "Ready")  !=0)
    {
      Ptr<AppContext> appContext = GetIstanceData (request->GetContextId(), "Ready")->appContext;
      GetIstanceData (request->GetContextId(), "Ready")->state = "WaitingTermination";
      TerminateApplication(appContext);
    }
  else
    {
//      SendDeleteAppContextResponse()
    }
}

void
MultiaccessEdgeOrchestrator::ProcessTerminateAppResponse(Ptr<TerminateAppResponse> response)
{
  Ptr<AppInstanceInfo> instance = response->GetAppInstance();
  Ptr<AppContext> appContext = GetIstanceData(instance)->appContext;
  Ptr<AppPkgInfo> pkg = FindAppPkgInfo(instance->GetAppPkgId()).first;

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Process \t") + response->GetInstanceTypeId().GetName()
  << std::string("(appInstaceId: ") << response->GetAppInstance()->GetAppInstanceId()
  << ", RespCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails()
  <<")");

  if (GetIstanceData(instance)->mobility == 0)
    {
      SendDeleteAppContextResponse(appContext,  response->GetRespCode(), response->GetProblemDetails());
    }
  else
    {
      DeleteIstanceData(appContext, "WaitingTermination");
    }

}

void
MultiaccessEdgeOrchestrator::SendDeleteAppContextResponse(Ptr<AppContext> appContext, int16_t respCode, std::string problemDetails)
{
  Ptr<DeleteAppContextResponse> response = CreateObject<DeleteAppContextResponse> ();
  response->SetContext(appContext);
  response->SetRespCode(respCode);
  response->SetProblemDetails(problemDetails);
  DeleteIstanceData(appContext, "WaitingTermination");


  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Send \t\t") + response->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") << response->GetContext()->GetContextId()
  << ", RespCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails()
  <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &OperationsSupportSystem::ForwardDeleteAppContextResponse, GetOss(), response);
}

void
MultiaccessEdgeOrchestrator::SendTerminateAppRequest(Ptr<AppInstanceInfo> instance)
{
   Ptr<TerminateAppRequest> request = CreateObject<TerminateAppRequest> ();
   request->SetInstance(instance);
   request->SetTerminationType(1);
   request->SetGracefullTerminationTimeout(GetIstanceData(instance)->appD->GetTerminateAppInstanceOpConfig()->GetMaxRecommendedGracefulTerminationTimeout());

   NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
    << std::string(")\t Send \t\t") + request->GetInstanceTypeId().GetName()
    << std::string("(InstanceId: ") << request->GetInstance()
    << ", Termination Timeout: " << request->GetGracefullTerminationTimeout() <<"s )");

   Ptr<MecPlataformManager> mpm = GetIstanceData(instance)->mecHost->GetObject<MecPlataformManager>();
    MsgList requestList;
    Time delay = GetDelayModel()->GetControlPlaneDelay();
    Simulator::Schedule(delay, &MecPlataformManager::ForwardTerminateAppRequest, mpm, request);
}

// Mobility

void
MultiaccessEdgeOrchestrator::ProcessMobilityProcedureNotification (Ptr<MobilityProcedureNotification> notification)
{
Ptr<AppContext> appContext = GetIstanceData(notification->GetMecApp())->appContext;
if(GetIstanceData(appContext, "Ready") != 0)
  {
  GetIstanceData(appContext, "Ready")->state = "WaitingTermination";
  GetIstanceData(appContext, "WaitingTermination")->mobility = 1;
  AddIstanceData(appContext, "Instantiation");
  GetIstanceData(appContext, "Instantiation")->mobility = 1;
  GetIstanceData(appContext, "Instantiation")->appD = GetIstanceData(appContext, "WaitingTermination")->appD;

  IstantiateApplication(appContext);
  }
}

void
MultiaccessEdgeOrchestrator::SendMobilityProcedureNotificationResponse(Ptr<MecApp> srcMecApp, Ptr<MecApp> trgMecApp, int16_t respCode, std::string problemDetails)
{
  Ptr<MobilityProcedureNotificationResponse> response = CreateObject<MobilityProcedureNotificationResponse>();
  response->SetSrcMecApp(srcMecApp);
  response->SetTrgMecApp(trgMecApp);
  response->SetRespCode(respCode);
  response->SetProblemDetails(problemDetails);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Send \t\t") + response->GetInstanceTypeId().GetName()
  << std::string("(srcAppInstanceId: ") << response->GetSrcMecApp()->GetAppInstanceID()
  << ", trgAppInstanceId: " << response->GetTrgMecApp()->GetAppInstanceID()
  << ", respCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails() <<")");

  Ptr<MecPlataformManager> mepm = (GetIstanceData(srcMecApp)->mecHost)->GetObject<MecPlataformManager>();
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataformManager::ForwardMobilityProcedureNotificationResponse, mepm, response);
}

void
MultiaccessEdgeOrchestrator::ProcessMobilityProcedureTerminateRequest (Ptr<MobilityProcedureTerminateRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Process\t") << request->GetInstanceTypeId().GetName()
  << std::string("(appInstanceId: ") << request->GetSrcMecApp()->GetAppInstanceID() <<")");

  Ptr<AppContext> appContext = GetIstanceData(request->GetTrgMecApp())->appContext;
  appContext->SetReferenceUri(request->GetTrgMecApp());

  SendUpdateAppContextNotification(appContext);

  TerminateApplication(appContext);
}

void
MultiaccessEdgeOrchestrator::SendUpdateAppContextNotification(Ptr<AppContext> appContext)
{
  Ptr<UpdateAppContextNotification> response =CreateObject<UpdateAppContextNotification> ();
  response->SetAppContext(appContext);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Send \t\t") + response->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + response->GetAppContext()->GetContextId()
  << ", referenceURI: " << response->GetAppContext()->GetReferenceUri()
  <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &OperationsSupportSystem::ForwardUpdateAppContextNotification, GetOss(), response);
}

// AppOnboarding

Time
MultiaccessEdgeOrchestrator::Onboarding(Ptr<AppD> appD)
{
  Ptr<AppPkgInfo> appPkgInfo = CreateObject<AppPkgInfo> ();

  uint64_t pkgId = rand() % 100000000;
  appPkgInfo->SetAppPkgId(pkgId);
  appPkgInfo->SetAppDId(appD->GetAppDId());
  appPkgInfo->SetAppProvider(appD->GetAppProvider());
  appPkgInfo->SetAppName(appD->GetAppName());
  appPkgInfo->SetSoftwareVersion(appD->GetAppSoftwareVersion());
  appPkgInfo->SetAppDVersion(appD->GetAppDVersion());
  appPkgInfo->SetChecksum("");
  appPkgInfo->SetAppD(appD);

  appPkgInfo->SetOnboardingState(1);

  AddAppPkgInfo(pkgId, appPkgInfo);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << std::string(")\t Process \tOnboardingAppPkg")
  << std::string("(AppPkgId: ") << appPkgInfo->GetAppPkgId()
  << std::string(", AppDId: ") << appPkgInfo->GetAppDId() << ")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
//  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::FindBestMecHost, this, appPkgInfo->GetAppD(), requestList);
  return delay;
}

void
MultiaccessEdgeOrchestrator::ProcessFetchAppPackageResponse (Ptr<FetchAppPackageRequest> request, uint64_t hostId, MsgList requestList)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
  << ")\t Process \t" << request->GetInstanceTypeId().GetName()
  << "(AppPkgId: " << request->GetAppPkgId()
  << ")");

  std::pair<Ptr<AppPkgInfo> , int16_t> pkg = FindAppPkgInfo (request->GetAppPkgId());
  SendFetchAppPackageResponse(pkg.first, pkg.second, hostId, requestList);
}

void
MultiaccessEdgeOrchestrator::SendFetchAppPackageResponse (Ptr<AppPkgInfo> appPkgInfo, int16_t respCode,  uint64_t hostId, MsgList requestList)
{
 Ptr<FetchAppPackageResponse> response = CreateObject<FetchAppPackageResponse>();
 response->SetAppPkgInfo(appPkgInfo);
 response->SetRespCode(respCode);

 NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
 << ")\t Send \t\t" << response->GetInstanceTypeId().GetName()
 << "(AppPkgId: " << response->GetAppPkgInfo()->GetAppPkgId()
 << ", RespCode: " << response->GetRespCode()
 << ", ProblemDetails: " << response->GetProblemDetails()
 << ")");

 requestList.pop_back();
// Time delay = GetDelayModel()->GetControlPlaneDelay("Mm3", response->Size());
// Simulator::Schedule(delay, &MecPlataformManager::ProcessFetchAppPackageResponse, m_mecHostList[hostId].first, response, requestList);

}

//

void
MultiaccessEdgeOrchestrator::IstantiateApplication(Ptr<AppContext> appContext)
{
  Time delay = Seconds(0);
  Ptr<MecHostEntity> besthost = 0;

  if (IsAppOnboarded(appContext)==0)
    {
       delay = delay + Onboarding(GetIstanceData(appContext, "Instantiation")->appD);
    }
  besthost = FindBestMecHost(appContext);

  if (besthost != 0)
    {
      GetIstanceData(appContext, "Instantiation")->mecHost = besthost;
      NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MeoId: " << this->GetId()
      << std::string(")\t Process\tFindBestMecHost")
      << "(HostId: " << GetIstanceData(appContext, "Instantiation")->mecHost->GetId()
      << ", ContextId: " << appContext->GetContextId()
      << ")"
      );

      Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::SendPreAllocateVirtualizedResRequest, this, appContext, besthost);
      Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::SendCreateAppInstanceIdentifierRequest, this, appContext, besthost);
    }
  else if(besthost == 0 && GetIstanceData(appContext, "Instantiation")->mobility == 0)
    {
      SendCreateAppContextResponse(appContext, 503, "Mec System is unable to process the request due to internal overload.");
    }
  else
    {
      // If a mobility procedure is started but there isn't a good mec host, the simulator do nothing
      GetIstanceData(appContext, "WaitingTermination")->state = "Ready";
      DeleteIstanceData(appContext, "Instantiation");
    }
}

void
MultiaccessEdgeOrchestrator::TerminateApplication(Ptr<AppContext> appContext)
{
  NS_LOG_FUNCTION(this << appContext);
  std::string state = GetIstanceData (appContext, "WaitingTermination")->state;
      if (appContext != 0)
        {
          Ptr<AppInstanceInfo> instance = GetIstanceData (appContext, "WaitingTermination")->instanceInfo;
          if (instance != 0)
            {
              SendTerminateAppRequest(instance);
            }
          else
            {
//              SendDeleteAppContextResponse(contextId,  404, "Instance not found",  requestList);
            }
        }
      else
        {
//          SendDeleteAppContextResponse(contextId,  404, "AppContext not found",  requestList);
        }
}

Ptr<MecHostEntity>
MultiaccessEdgeOrchestrator::FindBestMecHost(Ptr<AppContext> appContext)
{
  Ptr<UserEquipment> ue = appContext->GetCallbackReference();
  Ptr<MecHostContainer> hosts = GetNode()->GetObject<MecHostContainer>();
  MecHostContainer::Iterator host_it;

  Ptr<AppD> appD = GetAppRepository()->FindApp(appContext->GetAppDId()).first;
  uint64_t bsId = ue->GetTargetBs()->GetId();
  double neededMemory = appD->GetVirtualResourceDescriptor()->GetVirtualMemory()->GetVirtualMemSize();
  double neededStorage = appD->GetVirtualResourceDescriptor()->GetVirtualStorage()->GetSizeOfStorage();
  //double tmpLatency = std::numeric_limits<double>::infinity ();
  //double bestHostLatency = std::numeric_limits<double>::infinity ();
  Ptr<MecHostEntity> bestHost = 0;
  MecHostEntity::LinkedBs bs;


//  for (host_it=hosts->Begin(); host_it!=hosts->End(); host_it++)
//    {
//      Ptr<VirtualizzationInfrastructureManager> vim = (*host_it)->GetObject<VirtualizzationInfrastructureManager>();
//      Ptr<VirtualizzationInfrastructure> vi = (*host_it)->GetObject<VirtualizzationInfrastructure>();
//      bs = (*host_it)->FindLinkedBs(bsId);
//      if ( vim->GetMemory().available > neededMemory && vim->GetStorage().available > neededStorage && bs.bsId != 0)
//        {
//          tmpLatency = 2*bs.latency + (appD->GetTaskLength()->GetValue())/(1-vi->GetCpuUsage()*0.9999)*vi->GetMipsCpu();
//          if(bestHost != 0)
//            {
//              if(tmpLatency < bestHostLatency)
//                {
//                  bestHost = (*host_it);
//                  bestHostLatency = tmpLatency;
//                }
//            }
//          else
//            {
//              bestHost = (*host_it);
//              bestHostLatency = tmpLatency;
//            }
//        }
//    }

  for (host_it=hosts->Begin(); host_it!=hosts->End(); host_it++)
    {
      Ptr<VirtualizzationInfrastructureManager> vim = (*host_it)->GetObject<VirtualizzationInfrastructureManager>();
      Ptr<VirtualizzationInfrastructure> vi = (*host_it)->GetObject<VirtualizzationInfrastructure>();
      bs = (*host_it)->FindLinkedBs(bsId);
      if ( vim->GetMemory().available > neededMemory && vim->GetStorage().available > neededStorage && bs.latency == 0)
        {
              bestHost = (*host_it);
        }
    }
return bestHost;

}

bool
MultiaccessEdgeOrchestrator::IsAppOnboarded(Ptr<AppContext> app)
{
  std::map<uint64_t, Ptr<AppPkgInfo>> :: iterator it;
  for(it = m_appPkgInfoList.begin(); it != m_appPkgInfoList.end(); ++it)
  {
    if(app->GetAppDId() == it->second->GetAppDId())
    {
      NS_LOG_FUNCTION ("\n \t\t" << this->GetInstanceTypeId() << std::string("ID: ") + std::to_string(this->GetId()) << std::string("\n\t\tThe app is already ondoarded"));
      return 1;
    }
  }

  NS_LOG_FUNCTION ("\n \t\t" << this->GetInstanceTypeId() << std::string("ID: ") + std::to_string(this->GetId()) << std::string("\n\t\tThe app is not ondoarded"));
  return 0;
}


}
