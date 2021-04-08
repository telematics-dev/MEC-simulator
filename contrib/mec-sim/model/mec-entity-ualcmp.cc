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


#include "mec-entity-ualcmp.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("UserApplicationLcmProxy");

TypeId UserApplicationLcmProxy::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::UserApplicationLcmProxy")
    .SetParent<Object> ();
  return tid;
}

UserApplicationLcmProxy::UserApplicationLcmProxy ()
{
  NS_LOG_FUNCTION (this);
}

UserApplicationLcmProxy::~UserApplicationLcmProxy ()
{
  NS_LOG_FUNCTION (this);
}

void
UserApplicationLcmProxy::SetOss(Ptr<OperationsSupportSystem> oss)
{
  NS_LOG_FUNCTION (this << oss);
  m_oss = oss;
}

Ptr<OperationsSupportSystem>
UserApplicationLcmProxy::GetOss()
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


// MESSAGES

void
UserApplicationLcmProxy::ForwardCreateAppContextRequest(Ptr<CreateAppContextRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(UalcmpId: " << this->GetId()
  << std::string(")\t\t Forward \t") + request->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + request->GetAppContext()->GetContextId() <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &OperationsSupportSystem::ForwardCreateAppContextRequest, GetOss(), request);
}

void
UserApplicationLcmProxy::ForwardCreateAppContextResponse(Ptr<CreateAppContextResponse> response)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(UalcmpId: " << this->GetId()
  << std::string(")\t\t Forward \t") + response->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + response->GetAppContext()->GetContextId()
  << std::string(", RespCode: ") << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails() << ")"
  );

  Ptr<UserEquipment> ue = response->GetAppContext()->GetCallbackReference();
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  EventId x =Simulator::Schedule(delay, &UserEquipment::ProcessCreateAppContextResponse, ue, response);

}

void
UserApplicationLcmProxy::ForwardDeleteAppContextRequest(Ptr<DeleteAppContextRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(UalcmpId: " << this->GetId()
  << std::string(")\t\t Forward \t") + request->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + request->GetContextId() <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &OperationsSupportSystem::ForwardDeleteAppContextRequest, GetOss(), request);
}

void
UserApplicationLcmProxy::ForwardDeleteAppContextResponse(Ptr<DeleteAppContextResponse> response)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(UalcmpId: " << this->GetId()
  << std::string(")\t\t Forword\t") + response->GetInstanceTypeId().GetName());


  Ptr<UserEquipment> ue = response->GetContext()->GetCallbackReference();
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &UserEquipment::ProcessDeleteAppContextResponse, ue, response);

}

void
UserApplicationLcmProxy::ForwardUpdateAppContextNotification(Ptr<UpdateAppContextNotification> notification)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(OssId: " << this->GetId()
  << std::string(")\t\t Forword\t") + notification->GetInstanceTypeId().GetName());

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &UserEquipment::ProcessUpdateAppContextNotification, notification->GetAppContext()->GetCallbackReference(), notification);

}
}
