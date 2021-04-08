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

#include "ns3/simulator.h"
#include "mec-entity-mec-plataform-manager.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecPlataformManager");

TypeId MecPlataformManager::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecPlataformManager")
    .SetParent<Object> ();
  return tid;
}

MecPlataformManager::MecPlataformManager ()
{
  NS_LOG_FUNCTION (this);
  m_appInstanceIdCounter = 0;
  m_mecAppIdCounter = 0;
}

MecPlataformManager::~MecPlataformManager ()
{
  NS_LOG_FUNCTION (this);
}

Ptr<VirtualizzationInfrastructureManager>
MecPlataformManager::GetVim (void)
{
  NS_LOG_FUNCTION (this);
  return GetNode()->GetObject<VirtualizzationInfrastructureManager>();
}

Ptr<MultiaccessEdgeOrchestrator>
MecPlataformManager::GetMeo()
{
  NS_LOG_FUNCTION (this);
  return DynamicCast<MecHostEntity>(GetNode())->GetMeo();
}

Ptr<MecPlataform>
MecPlataformManager::GetMep (void)
{
  NS_LOG_FUNCTION (this);
  return GetNode()->GetObject<MecPlataform>();
}

int16_t
MecPlataformManager::AddAppPkg (uint64_t appPkgId, Ptr<AppPkgInfo> appPkgInfo)
{
  NS_LOG_FUNCTION (this << appPkgId << appPkgInfo);
  int16_t respCode = FindAppPkg(appPkgId).second;
  if (respCode == 404)
    {
      m_appPkgList.insert ( std::pair <uint64_t, Ptr<AppPkgInfo>> (appPkgId,appPkgInfo) );
      return 201;
    }
  else
    {
      return 409;
    }
}

int16_t
MecPlataformManager::DeleteAppPkg (uint64_t appPkgId)
{
  NS_LOG_FUNCTION (this << appPkgId);
  int16_t respCode = FindAppPkg(appPkgId).second;
  if (respCode == 200)
    {
      m_appPkgList.erase (appPkgId);
      return 200;
    }
  else
    {
      return 404;
    }
}

std::pair<Ptr<AppPkgInfo> , int16_t>
MecPlataformManager::FindAppPkg (uint64_t appPkgId )
{
  NS_LOG_FUNCTION (this << appPkgId);
  std::map<uint64_t, Ptr<AppPkgInfo>>::iterator appAppPkg_it = m_appPkgList.find(appPkgId);
   if(appAppPkg_it != m_appPkgList.end ())
     {
       return ( std::make_pair(appAppPkg_it->second, 200));
     }

   else
     {
       NS_LOG_FUNCTION ("unknown appDId " << appPkgId);
       Ptr<AppPkgInfo> ptrVoid=0;
       return ( std::make_pair(ptrVoid, 404));
     }
}



//Application instantiation

void
MecPlataformManager::ProcessCreateAppInstanceIdentifierRequest(Ptr<CreateAppInstanceIdentifierRequest> request, Ptr<AppContext> appContext)
{
  m_appInstanceIdCounter++;
  uint64_t appInstanceId = m_appInstanceIdCounter;

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << ")\t\t Process\t" << request->GetInstanceTypeId().GetName()
  << " (AppInstanceId: " << appInstanceId <<")");

  SendCreateAppInstanceIdentifierResponse(appInstanceId, appContext);
}

void
MecPlataformManager::SendCreateAppInstanceIdentifierResponse(uint64_t appInstanceId, Ptr<AppContext> appContext)
{
  Ptr<CreateAppInstanceIdentifierResponse> response = CreateObject<CreateAppInstanceIdentifierResponse> ();
  response->SetAppInstanceId(appInstanceId);
  response->SetRespCode(201);
  response->SetProblemDetails("");

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << ")\t\t Send\t\t" << response->GetInstanceTypeId().GetName()
  << "(AppInstanceId: " << response->GetAppInstanceId()
  << ", RespCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails()
  << ")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::ProcessCreateAppInstanceIdentifierResponse, GetMeo(), response, appContext);
  NS_LOG_INFO (delay);
}

void
MecPlataformManager::ProcessAppInstanceRequest(Ptr<InstantiateAppRequest> request, Ptr<AppContext> appContext)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << ")\t\t Process\t" << request->GetInstanceTypeId().GetName()
  << "(AppInstanceId: " << request->GetAppInstanceId()
  << ")");


////  check if appPkg is presente in MEPM or VIM
//  uint64_t appPkgId = GetMeo()->FindAppInstanceInfo(request->GetAppInstanceId()).first->GetAppPkgId();
//  std::pair<Ptr<AppPkgInfo> , int16_t> pkg = FindAppPkg(appPkgId);
//  if(pkg.second!=201)
//    {
//      SendFetchAppPackageRequest(requestList);
//    }
//  else
//    {

      SendAllocateVirtualizedResourceRequest(request, appContext);
      StartApp (request, appContext);

//    }

}

void
MecPlataformManager::SendFetchAppPackageRequest(MsgList requestList)
{
//  Ptr<InstantiateAppRequest> request = DynamicCast<InstantiateAppRequest>(requestList.back());
//  Ptr<AppInstanceInfo> instance = GetMeo()->FindAppInstanceInfo(request->GetAppInstanceId()).first;
//  Ptr<FetchAppPackageRequest> reqFetch =CreateObject<FetchAppPackageRequest> ();
//  reqFetch->SetAppPkgId(instance->GetAppPkgId());
//
//  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
//  << ")\t\t Send\t\t" << reqFetch->GetInstanceTypeId().GetName()
//  << "(appPkgId: " << instance->GetAppPkgId()
//  << ")");
//
//  requestList.push_back(reqFetch);
//  Time delay = GetDelayModel()->GetControlPlaneDelay("Mm3", reqFetch->Size());
//  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::ProcessFetchAppPackageResponse, GetMeo(), reqFetch, DynamicCast<MecHostEntity>(GetNode())->GetId(), requestList);
}



void
MecPlataformManager::ProcessFetchAppPackageResponse(Ptr<FetchAppPackageResponse> response, MsgList requestList)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << ")\t\t Process\t" << response->GetInstanceTypeId().GetName()
  << "(AppPkgId: " << response->GetAppPkgInfo()->GetAppPkgId()
  << ", RespCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails()
  << ")");

  AddAppPkg (response->GetAppPkgInfo()->GetAppPkgId(), response->GetAppPkgInfo());
//  SendAllocateVirtualizedResourceRequest(requestList);
}

void
MecPlataformManager::StartApp (Ptr<InstantiateAppRequest> request, Ptr<AppContext> appContext)
{
  m_mecAppIdCounter++;
  uint64_t appInstanceId = request->GetAppInstanceId();
  Ptr<MecApp> app = CreateObject<MecApp> (GetDelayModel());
  app->SetId(m_mecAppIdCounter);
  app->SetAppD(GetMeo()->GetIstanceData(appContext, "Instantiation")->appD);
  app->SetUeImsi(appContext->GetCallbackReference()->GetId());
  app->SetAppInstanceId(appInstanceId);
  app->SetMecPlataform(GetNode()->GetObject<MecPlataform>());
  (GetNode()->GetObject<MecAppContainer>())->Add(app);
  app->SetNode(GetNode()->GetObject<MecAppContainer>());
  GetMeo()->GetIstanceData(appContext, "Instantiation")->mecApp = app;

  double bootNoContention = app->GetAppD()->GetBootingTime();
  double cpuUtilizzation = GetVim()->GetCpu().used;

  Time delay = GetDelayModel()->GetBootingTime(bootNoContention, cpuUtilizzation);
  Simulator::Schedule(delay, &MecApp::SendAppReadyConfNotification, app);
  SendMecAppInstanceConfigurationRequest(request, appContext);
}

void
MecPlataformManager::SendAllocateVirtualizedResourceRequest(Ptr<InstantiateAppRequest> requestMeo, Ptr<AppContext> appContext)
{
  Ptr<AllocateVirtualizedResRequest> request = CreateObject<AllocateVirtualizedResRequest>();
  Ptr<VirtualResourceInstance> resourceInstance = CreateObject<VirtualResourceInstance>();

  request->SetVirtualResourceInstance(resourceInstance);
  resourceInstance->SetVirResInstId(GetMeo()->GetIstanceData(appContext, "Instantiation")->virtualResource->GetVirResInstId());
  resourceInstance->SetHostId(DynamicCast<MecHostEntity>(GetNode())->GetId());
  resourceInstance->SetVirtualResource(requestMeo->GetVirtualResourceDescriptor());
  resourceInstance->SetAllocationType(2); //  Allocation
  resourceInstance->CreateUserData(0);
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << ")\t\t Send \t\t" << request->GetInstanceTypeId().GetName()
  << "(VirResInstId: " << resourceInstance->GetVirResInstId()
  << ")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &VirtualizzationInfrastructureManager::ProcessAllocateVirtualizedResourceRequest, GetVim(), request);
}

void
MecPlataformManager::ProcessAllocateVirtualizedResourceResponse(Ptr<AllocateVirtualizedResResponse> response, MsgList requestList)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << ")\t\t Process \t" << response->GetInstanceTypeId().GetName()
  << "(VirResInstId: " << response->GetVirtualResourceInstance()->GetVirResInstId()
  << ")");
}

void
MecPlataformManager::SendMecAppInstanceConfigurationRequest(Ptr<InstantiateAppRequest> request, Ptr<AppContext> appContext)
{
  uint64_t appInstanceId = request->GetAppInstanceId();
  Ptr<MecAppInstanceConfigurationRequest> requestMep = CreateObject<MecAppInstanceConfigurationRequest> ();
  requestMep->SetAppD(GetMeo()->GetIstanceData(appContext, "Instantiation")->appD);
  requestMep->SetMecApp(GetMeo()->GetIstanceData(appContext, "Instantiation")->mecApp);
  requestMep->SetInstanceId(appInstanceId);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << ")\t\t Send \t\t" << requestMep->GetInstanceTypeId().GetName()
  << "(AppDId: " << requestMep->GetAppD()->GetAppDId()
  << ")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataform::ProcessMecAppInstanceConfigurationRequest, GetMep(), requestMep);


}

void
MecPlataformManager::ProcessMecAppInstanceConfigurationResponse(Ptr<MecAppInstanceConfigurationResponse> response)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << ")\t\t Process \t" << response->GetInstanceTypeId().GetName()
  << "(AppInstanceId: " << response->GetInstanceId()
  << ")");

  SendAppInstanceResponse(response->GetReferenceUri(), 201);
}

void
MecPlataformManager::SendAppInstanceResponse(Ptr<MecApp> referenceUri, int16_t respCode)
{
  Ptr<InstantiateAppResponse> responseMeo = CreateObject<InstantiateAppResponse>();
  responseMeo->SetAppInstanceId(referenceUri->GetAppInstanceID());
  responseMeo->SetRespCode(201);
  responseMeo->SetProblemDetails("");
  responseMeo->SetReferenceUri(referenceUri);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << ")\t\t Send \t\t" << responseMeo->GetInstanceTypeId().GetName()
  << "(AppInstanceId: " << responseMeo->GetAppInstanceId()
  << ")");
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::ProcessInstantiateAppResponse, GetMeo(), responseMeo);

}



void
MecPlataformManager::ForwardTerminateAppRequest (Ptr<TerminateAppRequest> request)
{
//  Simulator::Schedule(Seconds(request->GetGracefullTerminationTimeout()), &MecPlataformManager::SendTerminateVirtualResourceRequest, this, request->GetInstance());


  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Mepm: " << this->GetId()
  << std::string(")\t\t\t Forword\t") + request->GetInstanceTypeId().GetName()
  << std::string("(InstanceId: ") << request->GetInstance()
  << ", Termination Timeout: " << request->GetGracefullTerminationTimeout() <<"s )");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataform::ProcessTerminateAppRequest, GetMep(), request);
}

void
MecPlataformManager::ProcessTerminateAppResponse (Ptr<TerminateAppResponse> mepResponse)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Mepm: " << this->GetId()
  << std::string(")\t\t\t Process\t") + mepResponse->GetInstanceTypeId().GetName()
  << std::string("(appInstanceId: ") << mepResponse->GetAppInstance()->GetAppInstanceId() <<")");

  SendTerminateVirtualResourceRequest(mepResponse->GetAppInstance());
  ForwardTerminateAppResponse(mepResponse);

}

void
MecPlataformManager::SendTerminateVirtualResourceRequest(Ptr<AppInstanceInfo> appInstance)
{
  uint64_t virResInstId = GetMeo()->GetIstanceData(appInstance)->virtualResource->GetVirResInstId();

  if (virResInstId != 0)
    {
      Ptr<TerminateVirtualResourceRequest> request = CreateObject<TerminateVirtualResourceRequest> ();
      request->SetVirResInstId(virResInstId);

      NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Mepm: " << this->GetId()
      << std::string(")\t\t\t Send\t\t") + request->GetInstanceTypeId().GetName()
      << std::string("(VirResInstId: ") << request->GetVirResInstId() <<")");

      Time delay = GetDelayModel()->GetControlPlaneDelay();
      Simulator::Schedule(delay, &VirtualizzationInfrastructureManager::ProcessTerminateVirtualResourceRequest, GetVim(), request);
    }
  else
    {

    }
}

void
MecPlataformManager::ProcessTerminateVirtualResourceResponse(Ptr<TerminateVirtualResourceResponse> response)
{

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Mepm: " << this->GetId()
  << std::string(")\t\t\t Process \t") + response->GetInstanceTypeId().GetName()
  << std::string("(VirResInstId: ") << response->GetVirResInstId()
  << ", respCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails() <<")");

}

void
MecPlataformManager::ForwardTerminateAppResponse(Ptr<TerminateAppResponse> mepResponse)
{

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Mepm: " << this->GetId()
  << std::string(")\t\t\t Forword\t") + mepResponse->GetInstanceTypeId().GetName()
  << std::string("(InstanceId: ") << mepResponse->GetAppInstance()->GetAppInstanceId()
  << ", respCode: " << mepResponse->GetRespCode()
  << ", ProblemDetails: " << mepResponse->GetProblemDetails() <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::ProcessTerminateAppResponse, GetMeo(), mepResponse);

}



void
MecPlataformManager::ForwardMobilityProcedureNotification (Ptr<MobilityProcedureNotification> notification)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Mepm: " << this->GetId()
  << std::string(")\t\t\t Send \t\t") <<  notification->GetInstanceTypeId().GetName()
  << "(appInstanceId: " << notification->GetAppInstanceId()
  << ", srcBsId: " << notification->GetSrcBs()
  << ", trgBsId: " << notification->GetTrgBs()
  << ", Imsi: " << notification->GetImsi()
  << ")"
  );

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::ProcessMobilityProcedureNotification, GetMeo(), notification);
}

void
MecPlataformManager::ForwardMobilityProcedureNotificationResponse (Ptr<MobilityProcedureNotificationResponse> response)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << std::string(")\t\t Send \t\t") + response->GetInstanceTypeId().GetName()
  << std::string("(srcAppInstanceId: ") << response->GetSrcMecApp()->GetAppInstanceID()
  << ", trgAppInstanceId: " << response->GetTrgMecApp()->GetAppInstanceID()
  << ", respCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails() <<")");

  Ptr<ApplicationMobilityService> ams = GetMep()->GetObject<ApplicationMobilityService>();
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &ApplicationMobilityService::ProcessMobilityProcedureNotificationResponse, ams, response);
}

void
MecPlataformManager::ForwardMobilityProcedureTerminateRequest (Ptr<MobilityProcedureTerminateRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Mepm: " << this->GetId()
  << std::string(")\t\t\t Send \t\t") <<  request->GetInstanceTypeId().GetName()
  << "(appInstanceId: " << request->GetSrcMecApp()->GetAppInstanceID()
  << ")"
  );

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::ProcessMobilityProcedureTerminateRequest, GetMeo(), request);
}

void
MecPlataformManager::ForwardMobilityProcedureTerminateResponse (Ptr<MobilityProcedureTerminateResponse> response)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepmId: " << this->GetId()
  << std::string(")\t\t Send \t\t") + response->GetInstanceTypeId().GetName()
  << std::string("(AppInstanceId: ") << response->GetAppInstanceId()
  << ", respCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails() <<")");
  Ptr<ApplicationMobilityService> ams = GetMep()->GetObject<ApplicationMobilityService>();

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &ApplicationMobilityService::ProcessMobilityProcedureTerminateResponse, ams, response);
}
}
