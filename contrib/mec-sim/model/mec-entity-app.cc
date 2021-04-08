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
#include "mec-entity-app.h"
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecApp");

TypeId MecApp::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecApp")
    .SetParent<Object> ();
  return tid;
}

MecApp::MecApp (Ptr<MecDelayModel> delay)
{
  SetDelayModel(delay);
  m_imsi = 0 ;
  m_appInstanceId =0 ;
  NS_LOG_FUNCTION (this);
}

MecApp::~MecApp ()
{
  NS_LOG_FUNCTION (this);
}

void
MecApp::SetAppD (Ptr<AppD> appD)
{
  NS_LOG_FUNCTION (this << appD);
  m_appD = appD;
}

Ptr<MecPlataform>
MecApp::GetMecPlataform ( void)
{
  NS_LOG_FUNCTION (this);
  return m_mecPlataform;
}

void
MecApp::SetMecPlataform ( Ptr<MecPlataform> mp)
{
  NS_LOG_FUNCTION (this << mp);
  m_mecPlataform = mp;
}

Ptr<AppD>
MecApp::GetAppD (void)
{
  NS_LOG_FUNCTION (this);
  return m_appD;
}
void
MecApp::SetAppInstanceId (uint64_t appInstanceId)
{
  NS_LOG_FUNCTION (this << appInstanceId);
m_appInstanceId = appInstanceId;
}

uint64_t
MecApp::GetAppInstanceID (void)
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceId;
}

void
MecApp::SetUeImsi (uint64_t imsi)
{
  NS_LOG_FUNCTION (this << imsi);
  m_imsi = imsi;
}

uint64_t
MecApp::GetUeImsi (void)
{
  NS_LOG_FUNCTION (this);
  return m_imsi;
}

void
MecApp::SendAppReadyConfNotification (void)
{
  Ptr<AppReadyConfirmation> notification = CreateObject<AppReadyConfirmation> ();
  notification->SetMecAppId(GetId());
  notification->SetIndication("READY");

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MecAppId: " << this->GetId()
  << std::string(")\t\t\t\t\t Send \t\t") + notification->GetInstanceTypeId().GetName()
  << std::string("(State: ") + notification->GetIndication() <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataform::ProcessAppReadyConfNotification, m_mecPlataform, notification, this);

}

void
MecApp::ProcessAppReadyConfNotificationResposne(Ptr<AppReadyConfirmationResponse> response)
{
  if(response->GetRespCode() > 300)
    {
      SendAppReadyConfNotification();
    }
  else
    {
      SendRegisterAppMobilityRequest();
//      SendRegisterRnisRequest();

    }
}

void
MecApp::ProcessAppTerminationNotification(void)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MecAppId: " << this->GetId()
  << std::string(")\t\t\t\t\t Process \t") << "AppTerminationNotification");

  if(m_client !=0)
    {
      m_client->SetState(0);
    }
  SendUnsubscribeAppMobilityRequest ();
//  SendUnsubscribeRnisRequest();
  SendAppTerminationConfirmation ();
}

void
MecApp::SendAppTerminationConfirmation (void)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MecAppId: " << this->GetId()
  << std::string(")\t\t\t\t\t Send \t\t") << "AppTerminationConfirmation");


  Time delay = Seconds(0.5);
  Simulator::Schedule(delay, &MecPlataform::ProcessAppTerminationConfirmation, m_mecPlataform, this);
}

void
MecApp::SendRegisterAppMobilityRequest (void)
{
  Ptr<ApplicationMobilityService> ams = GetMecPlataform()->GetObject<ApplicationMobilityService>();
  Ptr<ServiceRegistrationInfo> info = CreateObject<ServiceRegistrationInfo>();
  Ptr<MecEntity> callback = this;
  info->SetCallback(callback);
  info->SetSubscriptionType("CellChangeSubscription");
  info->SetAppInstanceId(m_appInstanceId);
  info->SetImsi(m_imsi);
  info->SetMepId(m_mecPlataform->GetId());
  info->SetMecApp(this);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MecAppId: " << this->GetId()
  << std::string(")\t\t\t\t\t Send \t\t") <<  info->GetInstanceTypeId().GetName()
  << "(AppInstanceId: " << info->GetAppInstanceId()
  << ", Imsi: " << info->GetImsi()
  << ")"
  );
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &ApplicationMobilityService::ProcessSubscriptionRequest, ams , info);

}


void
MecApp::SendUnsubscribeAppMobilityRequest (void)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MecAppId: " << this->GetId()
  << std::string(")\t\t\t\t\t Send \t\t") << "ProcessUnsubscriptionRequest"
  << "(appInstanceId: " << m_appInstanceId
  );

  Ptr<ApplicationMobilityService> ams = GetMecPlataform()->GetObject<ApplicationMobilityService>();
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &ApplicationMobilityService::ProcessUnsubscriptionRequest, ams , this);
}


//void
//MecApp::SendRegisterRnisRequest (void)
//{
//  SetRnis(m_mecPlataform->GetRnis());
//  Ptr<CreateRniSubscriptionRequest> request = CreateObject<CreateRniSubscriptionRequest>();
//  Ptr<RniSubscription> info = CreateObject<RniSubscription>();
//  request->SetRniSubscription(info);
//  info->SetSubscriber("ns3::MecApp");
//  info->SetMecApp(this);
//  info->SetAppInstanceId(m_appInstanceId);
//  info->SetImsi(m_imsi);
//  info->SetMepId(m_mecPlataform->GetId());
//  info->SetSubscriptionType("TrafficSteeringStateSubscription");
//
//  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MecAppId: " << this->GetId()
//  << std::string(")\t\t\t\t\t Send \t\t") <<  request->GetInstanceTypeId().GetName()
//  << "(RnisSubscriptionType: " << info->GetSubscriptionType()
//  << ", AppInstanceId: " << info->GetAppInstanceId()
//  << ", Imsi: " << info->GetImsi()
//  );
//  Time delay = GetDelayModel()->GetControlPlaneDelay("Mm1", request->Size());
//  Simulator::Schedule(delay, &RadioNetworkInformationService::ProcessCreateRniSubscriptionRequest,m_rnis , request);
//
//}
//
//void
//MecApp::SendUnsubscribeRnisRequest (void)
//{
//  Ptr<UnsubscribeFromServiceRequest> request = CreateObject<UnsubscribeFromServiceRequest>();
//  request->SetServiceId(m_appInstanceId);
//
//  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(MecAppId: " << this->GetId()
//  << std::string(")\t\t\t\t\t Send \t\t") <<  request->GetInstanceTypeId().GetName()
//  << "(appInstanceId: " << request->GetServiceId()
//  );
//
//  Time delay = GetDelayModel()->GetControlPlaneDelay("Mm1", request->Size());
//  Simulator::Schedule(delay, &RadioNetworkInformationService::ProcessUnsubscribeRnisRequest,m_rnis , request);
//}

void
MecApp::ProcessTaskOffloadingRequest(Ptr<TaskOffloading> task)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(AppId: " << this->GetId()
  << ")\t Process \t\t" << task->GetInstanceTypeId().GetName()
  << "(Task size: "<< task->GetIstructionNumber() << " MI, "
  << "Starting Time: " << std::to_string(task->GetStartingTime().GetSeconds())
  << ")");
  m_client = task->GetClientApp();
  task->SetProcessingTime(Now());
  GetMecPlataform()->GetNode()->GetObject<VirtualizzationInfrastructure>()->AddActiveProcess(task);
}

void
MecApp::SendTaskOffloadingResponse(Ptr<TaskOffloading> task)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "((AppId: " << this->GetId()
  << ")\t Send \t\t" << task->GetInstanceTypeId().GetName()
  << "(Task size: "<< task->GetIstructionNumber() << " MI, "
  << "Starting Time: " << std::to_string(task->GetStartingTime().GetSeconds())
  << ")");
  task->SetProcessingTime(Now()-task->GetProcessingTime());


  Ptr<BaseStation> bs = task->GetClientApp()->GetUe()->GetTargetBs();
  Ptr<MecHostEntity> host = DynamicCast<MecHostEntity>(GetMecPlataform()->GetNode());

  Time delay = GetDelayModel()->GetBackhaulDelay(host->FindLinkedBs(bs->GetId()).latency);
  Simulator::Schedule(delay, &BaseStation::ForwardTaskOffloadingResponse, bs, task);

}

}
