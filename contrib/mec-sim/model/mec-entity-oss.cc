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
#include "mec-entity-oss.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("OperationsSupportSystem");

TypeId OperationsSupportSystem::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::OperationsSupportSystem")
    .SetParent<Object> ();
  return tid;
}

OperationsSupportSystem::OperationsSupportSystem ()
{
  NS_LOG_FUNCTION (this);
}

OperationsSupportSystem::~OperationsSupportSystem ()
{
  NS_LOG_FUNCTION (this);
}

void
OperationsSupportSystem::SetUalcmp(Ptr<UserApplicationLcmProxy> ualcmp)
{
  NS_LOG_FUNCTION (this << ualcmp);
  m_ualcmp = ualcmp;
}

Ptr<UserApplicationLcmProxy>
OperationsSupportSystem::GetUalcmp()
{
  NS_LOG_FUNCTION (this);
  if(m_ualcmp == 0)
    {
      Ptr<UserApplicationLcmProxy> ualcmp = this->GetNode()->GetObject<UserApplicationLcmProxy>();
      if(ualcmp==0)
        {
          NS_LOG_ERROR (this << "set UALCMP pointer");
          return ualcmp;
        }
      else
        {
          return ualcmp;
        }
    }
  else
    {
      return m_ualcmp;
    }
}

void
OperationsSupportSystem::SetMeo(Ptr<MultiaccessEdgeOrchestrator> meo)
{
  NS_LOG_FUNCTION (this << meo);
  m_meo = meo;
}

Ptr<MultiaccessEdgeOrchestrator>
OperationsSupportSystem::GetMeo()
{
  NS_LOG_FUNCTION (this);
  if(m_meo == 0)
    {
      Ptr<MultiaccessEdgeOrchestrator> meo = this->GetNode()->GetObject<MultiaccessEdgeOrchestrator>();
      if(meo==0)
        {
          NS_LOG_ERROR (this << "set MEO pointer");
          return meo;
        }
      else
        {
          return meo;
        }
    }
  else
    {
      return m_meo;
    }
}





// MESSAGES

void
OperationsSupportSystem::ForwardCreateAppContextRequest(Ptr<CreateAppContextRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(OssId: " << this->GetId()
  << std::string(")\t\t Forword\t") + request->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + request->GetAppContext()->GetContextId() <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::ProcessCreateAppContextRequest, GetMeo(), request);
}

void
OperationsSupportSystem::ForwardCreateAppContextResponse(Ptr<CreateAppContextResponse> response)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(OssId: " << this->GetId()
  << std::string(")\t\t Forward \t") + response->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + response->GetAppContext()->GetContextId()
  << std::string(", RespCode: ") << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails() << ")"
  );

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &UserApplicationLcmProxy::ForwardCreateAppContextResponse, GetUalcmp(), response);

}

void
OperationsSupportSystem::ForwardDeleteAppContextRequest(Ptr<DeleteAppContextRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(OssId: " << this->GetId()
  << std::string(")\t\t Forword\t") + request->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + request->GetContextId() <<")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::ProcessDeleteAppContextRequest, GetMeo(), request);
}

void
OperationsSupportSystem::ForwardDeleteAppContextResponse(Ptr<DeleteAppContextResponse> response)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(OssId: " << this->GetId()
  << std::string(")\t\t Forword\t") + response->GetInstanceTypeId().GetName());

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &UserApplicationLcmProxy::ForwardDeleteAppContextResponse, GetUalcmp(), response);

}

void
OperationsSupportSystem::ForwardUpdateAppContextNotification(Ptr<UpdateAppContextNotification> notification)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(OssId: " << this->GetId()
  << std::string(")\t\t Forword\t") + notification->GetInstanceTypeId().GetName());

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &UserApplicationLcmProxy::ForwardUpdateAppContextNotification, GetUalcmp(), notification);

}


}

