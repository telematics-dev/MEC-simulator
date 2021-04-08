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
#include "mec-service-rnis.h"
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("RadioNetworkInformationService");

TypeId RadioNetworkInformationService::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::RadioNetworkInformationService")
    .SetParent<Object> ();
  return tid;
}

RadioNetworkInformationService::RadioNetworkInformationService ()
{
  NS_LOG_FUNCTION (this);
}

RadioNetworkInformationService::~RadioNetworkInformationService ()
{
  NS_LOG_FUNCTION (this);
}


void
RadioNetworkInformationService::ProcessSubscriptionRequest(Ptr<ServiceRegistrationInfo> regInfo)
{
  NS_LOG_FUNCTION (this);
  m_registrationInstanceList.push_back(regInfo);
}

void
RadioNetworkInformationService::ProcessUnsubscriptionRequest(Ptr<MecApp> mecApp)
{
  NS_LOG_FUNCTION (this);
  for(ApplicationMobilityService::Iterator it=m_registrationInstanceList.begin(); it!=m_registrationInstanceList.end(); it++)
    {
          if((*it)->GetMecApp() == mecApp)
            {
              m_registrationInstanceList.erase(it);
              break;
            }
    }
}

Ptr<ApplicationMobilityService>
RadioNetworkInformationService::GetAms()
{
  NS_LOG_FUNCTION (this);
  return GetNode()->GetObject<ApplicationMobilityService>();
}

void
RadioNetworkInformationService::CallBackRnisCellChange(Ptr<CellChangeNotification> notification)
{
  for(Iterator it = m_registrationInstanceList.begin(); it != m_registrationInstanceList.end(); it++)
    {
      if ((*it)->GetSubscriptionType() == "CellChangeSubscription" && (*it)->GetImsi() == notification->GetImsi())
        {

          NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Id: " << this->GetId()
          << std::string(")\t\t Forward \t\t") <<  notification->GetInstanceTypeId().GetName()
          << "(Time: " << notification->GetTimeStamp()
          << ", srcBsId: " << notification->GetSrcBs()->GetId()
          << ", trgBsId: " << notification->GetTrgBs()->GetId()
          << ")"
          );
    Time delay = GetDelayModel()->GetControlPlaneDelay();
    Simulator::Schedule(delay, &ApplicationMobilityService::ProcessCellChangeNotification, GetAms() , notification);
        }
    }
}

////void
////RadioNetworkInformationService::CallBackRnisTrafficSteeringState(uint64_t imsi, uint64_t BsId, bool state)
////{
////  for(auto iterator = m_rniSubscriptionList.begin(); iterator != m_rniSubscriptionList.end(); iterator++)
////    {
////      if ((*iterator)->GetSubscriptionType() == "TrafficSteeringStateSubscription" && (*iterator)->GetImsi() == imsi)
////	{
////	  Ptr<CellChangeNotification> notification = CreateObject<CellChangeNotification>();
////	  notification->SetNotificationType("TrafficSteeringStateSubscription");
////	  notification->SetTimeStamp(Simulator::Now());
////	  notification->SetSrcBs(BsId);
////	  notification->SetTrgBs(0);
////	  notification->SetImsi(imsi);
////
////	  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Rnis: " << this->GetRnisId()
////	  << std::string(")\t\t Send \t\t") <<  notification->GetInstanceTypeId().GetName()
////	  << "(Time: " << notification->GetTimeStamp()
////	  << ", BsId: " << notification->GetSrcBs()
////	  << ", Imsi: " << notification->GetImsi()
////	  );
////
//////	  Time delay = m_delayModel->HandleTrasmissionDelay("Mm1", notification->Size());
//////	  Simulator::Schedule(delay, &MecApp::ProcessTrafficSteeringStateNotification, (*iterator)->GetMecApp() , notification);
////	}
////    }
////}


}
