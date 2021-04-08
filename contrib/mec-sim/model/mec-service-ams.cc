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
#include "mec-service-ams.h"
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ApplicationMobilityService");

TypeId ApplicationMobilityService::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ApplicationMobilityService")
    .SetParent<Object> ();
  return tid;
}

ApplicationMobilityService::ApplicationMobilityService ()
{
  NS_LOG_FUNCTION (this);
}

ApplicationMobilityService::~ApplicationMobilityService ()
{
  NS_LOG_FUNCTION (this);
}

void
ApplicationMobilityService::ProcessSubscriptionRequest(Ptr<ServiceRegistrationInfo> regInfo)
{
  NS_LOG_FUNCTION (this);
  m_registrationInstanceList.push_back(regInfo);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Id: " << this->GetId()
  << std::string(")\t\t\t\t\t Process \t\t") <<  regInfo->GetInstanceTypeId().GetName()
  << "(AppInstanceId: " << regInfo->GetAppInstanceId()
  << ", Imsi: " << regInfo->GetImsi()
  << ")"
  );

  Ptr<ServiceRegistrationInfo> request = CopyObject(regInfo);
  Ptr<MecEntity> callback = this;
  request->SetCallback(callback);

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &RadioNetworkInformationService::ProcessSubscriptionRequest, GetRnis() , request);
}

void
ApplicationMobilityService::ProcessUnsubscriptionRequest(Ptr<MecApp> mecApp)
{
  NS_LOG_FUNCTION (this);
  uint64_t toBeUnsubscribed = mecApp->GetId();
  ApplicationMobilityService::Iterator it_final = m_registrationInstanceList.end();
  for(ApplicationMobilityService::Iterator it=m_registrationInstanceList.begin(); it!=m_registrationInstanceList.end(); it++)
    {
      uint64_t courrent = (*it)->GetMecApp()->GetId();
          if(toBeUnsubscribed == courrent)
            {
              it_final = it;
            }
    }
  if(it_final!=m_registrationInstanceList.end())
    {
      NS_LOG_FUNCTION ("App: " << toBeUnsubscribed << " erased");
      m_registrationInstanceList.erase(it_final);
      GetRnis()->ProcessUnsubscriptionRequest(mecApp);
    }
}


Ptr<RadioNetworkInformationService>
ApplicationMobilityService::GetRnis (void)
{
  NS_LOG_FUNCTION (this);
  return GetNode()->GetObject<RadioNetworkInformationService>();
}

void
ApplicationMobilityService::ProcessCellChangeNotification (Ptr<CellChangeNotification> notification)
{
  for(Iterator it = m_registrationInstanceList.begin(); it != m_registrationInstanceList.end(); it++)
    {
      if ((*it)->GetImsi() == notification->GetImsi())
        {
          Ptr<MobilityProcedureNotification> notificationToMeo = CreateObject<MobilityProcedureNotification>();
          notificationToMeo->SetMecApp((*it)->GetMecApp());
          notificationToMeo->SetAppInstanceId((*it)->GetAppInstanceId());
          notificationToMeo->SetSrcBs(notification->GetSrcBs()->GetId());
          notificationToMeo->SetTrgBs(notification->GetTrgBs()->GetId());
          notificationToMeo->SetImsi(notification->GetImsi());

          NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Ams: " << this->GetId()
          << std::string(")\t\t\t Send \t\t") <<  notificationToMeo->GetInstanceTypeId().GetName()
          << "(appInstanceId: " << notificationToMeo->GetAppInstanceId()
          << ", srcBsId: " << notificationToMeo->GetSrcBs()
          << ", trgBsId: " << notificationToMeo->GetTrgBs()
          << ", Imsi: " << notificationToMeo->GetImsi()
          << ")"
          );

          Ptr<MecPlataformManager> mpm = DynamicCast<MecPlataform>(GetNode())->GetMepm();
          Time delay = GetDelayModel()->GetControlPlaneDelay();
          Simulator::Schedule(delay, &MecPlataformManager::ForwardMobilityProcedureNotification, mpm , notificationToMeo);
        }
    }
}


void
ApplicationMobilityService::ProcessMobilityProcedureNotificationResponse (Ptr<MobilityProcedureNotificationResponse> notification)
{
  SendMobilityProcedureTerminateRequest( notification->GetSrcMecApp(), notification->GetTrgMecApp());
}

void
ApplicationMobilityService::SendMobilityProcedureTerminateRequest(Ptr<MecApp> srcMecApp, Ptr<MecApp> trgMecApp)
{
  Ptr<MobilityProcedureTerminateRequest> request = CreateObject<MobilityProcedureTerminateRequest>();
  request->SetSrcMecApp(srcMecApp);
  request->SetTrgMecApp(trgMecApp);
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Ams: " << this->GetId()
  << std::string(")\t\t\t Send \t\t") <<  request->GetInstanceTypeId().GetName()
  << "(appInstanceId: " << request->GetSrcMecApp()->GetAppInstanceID()
  << ")"
  );

  Ptr<MecPlataformManager> mpm = DynamicCast<MecPlataform>(GetNode())->GetMepm();
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataformManager::ForwardMobilityProcedureTerminateRequest, mpm , request);
}

void
ApplicationMobilityService::ProcessMobilityProcedureTerminateResponse(Ptr<MobilityProcedureTerminateResponse> response)
{
  NS_LOG_INFO("MecAppTermination started...");
}

}
