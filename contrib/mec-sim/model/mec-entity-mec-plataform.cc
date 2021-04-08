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

#include <ns3/simulator.h>
#include "mec-entity-mec-plataform.h"
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecPlataform");

TypeId MecPlataform::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecPlataform")
    .SetParent<Object> ();
  return tid;
}

MecPlataform::MecPlataform ()
{
  NS_LOG_FUNCTION (this);
}


MecPlataform::~MecPlataform()
{
  NS_LOG_FUNCTION (this);
}

Ptr<MecPlataformManager>
MecPlataform::GetMepm (void)
{
  NS_LOG_FUNCTION (this);
  return GetNode()->GetObject<MecPlataformManager>();
}

Ptr<MultiaccessEdgeOrchestrator>
MecPlataform::GetMeo (void)
{
  NS_LOG_FUNCTION(this);
  return DynamicCast<MecHostEntity>(GetNode())->GetMeo();
}

//void
//MecPlataform::SetAms (Ptr <ApplicationMobilityService> ams)
//{
//  NS_LOG_FUNCTION (this << ams);
//  m_ams = ams;
//
//}
//
//Ptr <ApplicationMobilityService>
//MecPlataform::GetAms (void)
//{
//  NS_LOG_FUNCTION (this);
//  return m_ams;
//}
//
//void
//MecPlataform::SetRnis (Ptr<RadioNetworkInformationService> rnis)
//{
//  NS_LOG_FUNCTION (this << rnis);
//  m_rnis = rnis;
//
//}
//
//Ptr<RadioNetworkInformationService>
//MecPlataform::GetRnis (void)
//{
//  NS_LOG_FUNCTION (this);
//  return m_rnis;
//}


void
MecPlataform::ProcessMecAppInstanceConfigurationRequest(Ptr<MecAppInstanceConfigurationRequest> request)
{

//  //Base Station traffic steering

//  Ptr<TrafficSteeringInfo> newTS = CreateObject<TrafficSteeringInfo> ();;
//  Ptr<UserEquipment> ue = GetMeo()->FindUeByImsi(request->GetMecApp()->GetUeImsi());
//  newTS->SetUe(ue);
//  newTS->SetAppInstanceId(request->GetMecApp()->GetId());
//  newTS->SetGuaranteedDownlink(request->GetMecApp()->GetAppD()->GetAppTrafficRule()->GetQosGbrDl());
//  newTS->SetGuaranteedUplink(request->GetMecApp()->GetAppD()->GetAppTrafficRule()->GetQosGbrDl());
//  ue->GetTargetBs()->AddTrafficSteeringInfo(newTS->GetAppInstanceId(), newTS);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepId: " << this->GetId()
  << std::string(")\t\t\t Process \t") + request->GetInstanceTypeId().GetName()
  << std::string("(MecAppId: ") << request->GetMecApp()->GetId()
  <<")");
}

void
MecPlataform::SendsMecAppInstanceConfigurationResponse(Ptr<AppInstanceInfo> instanceInfo, Ptr<MecApp> mecApp)
{
  uint64_t appInstanceId = instanceInfo->GetAppInstanceId();
  Ptr<MecAppInstanceConfigurationResponse> response = CreateObject<MecAppInstanceConfigurationResponse> ();
  response->SetInstanceId(appInstanceId);
  response->SetRespCode(204);
  response->SetProblemDetails("");
  response->SetReferenceUri(mecApp);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepId: " << this->GetId()
  << std::string(")\t\t\t Send \t\t") + response->GetInstanceTypeId().GetName()
  << std::string("(MecAppId: ") << mecApp->GetId()
  << ", respCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails() <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataformManager::ProcessMecAppInstanceConfigurationResponse, GetMepm(), response);

}

void
MecPlataform::ProcessTerminateAppRequest(Ptr<TerminateAppRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepId: " << this->GetId()
  << std::string(")\t\t\t Process \t") << request->GetInstanceTypeId().GetName()
  << std::string("(InstanceId: ") << request->GetInstance()
  << ")"
  );

  Ptr<MecApp> mecApp = GetMeo()->GetIstanceData(request->GetInstance())->mecApp;
  SendAppTerminationNotification( mecApp);
}

void
MecPlataform::SendAppTerminationNotification(Ptr<MecApp> mecApp)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepId: " << this->GetId()
  << std::string(")\t\t\t Send \t\t") << "AppTerminationNotification");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecApp::ProcessAppTerminationNotification, mecApp);
}

void
MecPlataform::ProcessAppTerminationConfirmation(Ptr<MecApp> mecApp)
{
//	Codicce per recuperare la vecchia bs dell'utente e rilasciarne le risorse

//  GetMepm()->GetVim()->GetLinkedBaseStation()->DeleteTrafficSteeringInfo(mecAppId);
  Ptr<AppInstanceInfo> instance = GetMeo()->GetIstanceData(mecApp)->instanceInfo;


  int16_t respCode = 202;
  std::string problemDetails = "App succesfull gracefull terminated";

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepId: " << this->GetId()
  << std::string(")\t\t\t Process \t") << "AppTerminationConfirmation"
  );

  SendTerminateAppResponse(instance, respCode, problemDetails);
}

void
MecPlataform::SendTerminateAppResponse(Ptr<AppInstanceInfo> instance, int16_t respCode, std::string problemDetails)
{
  Ptr<TerminateAppResponse> response = CreateObject<TerminateAppResponse> ();
  response->SetRespCode(respCode);
  response->SetProblemDetails(problemDetails);
  response->SetAppInstance(instance);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepId: " << this->GetId()
  << std::string(")\t\t\t Send \t\t") + response->GetInstanceTypeId().GetName()
  << std::string("(appInstanceId: ") << response->GetAppInstance()->GetAppInstanceId()
  << ", respCode: " << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails() <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataformManager::ProcessTerminateAppResponse, GetMepm(), response);
}



void
MecPlataform::DeleteMecApp(int64_t mecAppId)
{

}


void
MecPlataform::ProcessAppReadyConfNotification(Ptr<AppReadyConfirmation> notification, Ptr<MecApp> mecApp)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MepId: " << this->GetId()
  << std::string(")\t\t\t Process \t\t") + notification->GetInstanceTypeId().GetName()
  << std::string("(mecAppId: ") << notification->GetMecAppId()
  << ", status: " << notification->GetIndication()
  <<")");

  Ptr<AppInstanceInfo> instanceInfo = GetMeo()->GetIstanceData(mecApp)->instanceInfo;
  SendsMecAppInstanceConfigurationResponse(instanceInfo, mecApp);
  SendAppReadyConfNotificationResponse(204, mecApp);

}

void
MecPlataform::SendAppReadyConfNotificationResponse(int respCode, Ptr<MecApp> mecApp)
{
  Ptr<AppReadyConfirmationResponse> response = CreateObject<AppReadyConfirmationResponse>();
  response->SetRespCode(respCode);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Mep: " << this->GetId()
  << std::string(")\t\t\t\t Send \t\t") << response->GetInstanceTypeId().GetName()
  << "( RespCode: " << respCode << ")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecApp::ProcessAppReadyConfNotificationResposne, mecApp, response);

}

}
