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


#include "ns3/log.h"
#include "ns3/simulator.h"
#include "mec-service.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecService");

TypeId MecService::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecService")
    .SetParent<Object> ();
  return tid;
}

MecService::MecService ()
{
  m_node = 0;
  m_id = 0;
  NS_LOG_FUNCTION (this);
}

MecService::~MecService ()
{
  NS_LOG_FUNCTION (this);
}

Ptr<MecPlataform>
MecService::GetMecPlataform (void)
{
  NS_LOG_FUNCTION (this );
  return m_node;
}

void
MecService::SetMecPlataform(Ptr<MecPlataform> node)
{
  m_node = node;
}

uint64_t
MecService::GetId (void)
{
  NS_LOG_LOGIC (this->GetInstanceTypeId() << "Id:" << m_id);
  return m_id;
}

void
MecService::SetId(uint64_t id)
{
  NS_LOG_LOGIC (this << id);
  m_id = id;
}

void
MecService::SetDelayModel (Ptr<MecDelayModel> delay)
{
  NS_LOG_FUNCTION (this << delay);
  m_delayModel = delay;
}

Ptr<MecDelayModel>
MecService::GetDelayModel()
{
  NS_LOG_FUNCTION (this);
  if(m_delayModel == 0)
    {
      Ptr<MecDelayModel> delayModel = GetMecPlataform()->GetNode()->GetObject<MecDelayModel>();
      if(delayModel==0)
        {
          NS_LOG_ERROR (this << "set DelayModel pointer");
          return delayModel;
        }
      else
        {
          return delayModel;
        }
    }
  else
    {
      return m_delayModel;
    };
}

void
MecService::ProcessSubscriptionRequest(Ptr<ServiceRegistrationInfo> regInfo)
{
  NS_LOG_FUNCTION (this);
  m_registrationInstanceList.push_back(regInfo);
}

void
MecService::SendSubscriptionRequest(Ptr<ServiceRegistrationInfo> regInfo, Ptr<MecService> mecService)
{
  NS_LOG_FUNCTION (this);
  Time delay = m_delayModel->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecService::ProcessSubscriptionRequest, mecService, regInfo);
}

void
MecService::ProcessUnsubscriptionRequest(Ptr<MecApp> mecApp)
{
  NS_LOG_FUNCTION (this);
  for(MecService::Iterator it=m_registrationInstanceList.begin(); it!=m_registrationInstanceList.end(); it++)
    {
          if((*it)->GetMecApp() == mecApp)
            {
              m_registrationInstanceList.erase(it);
              break;
            }
    }
//  std::string subscriber = (*it)->GetSubscriber();
}
void
MecService::SendUnsubscriptionRequest(Ptr<MecApp> mecApp, Ptr<MecService> mecService)
{
  NS_LOG_FUNCTION (this);
  Time delay = m_delayModel->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecService::ProcessUnsubscriptionRequest, mecService, mecApp);
}

}

