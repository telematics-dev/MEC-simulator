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
#include "client-app.h"
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ClientApp");

TypeId ClientApp::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ClientApp")
    .SetParent<Object> ();
  return tid;
}

ClientApp::ClientApp ()
{
  NS_LOG_FUNCTION (this);
  m_state = 0;
  sum_e2e = 0;
  sum_processing = 0;
  n_e2e = 0;
  n_processing = 0;
  m_appDiD = 0;
  m_startTime = Now();
  m_activeTime = 3600*4;
  m_idleTime = 100;
}

ClientApp::~ClientApp ()
{
}

Ptr<MecDelayModel>
ClientApp::GetDelayModel()
{
 return m_ue->GetDelayModel();
}

void
ClientApp::SetState(bool state)
{
  NS_LOG_FUNCTION (this << state);
  m_state = state;
  m_appDiD = m_mecApp->GetAppD()->GetAppDId();
  if(state==1)
    {
      DoActive();
    }
}

void
ClientApp::SetActiveIdle(double active, double idle)
{
  m_activeTime = active;
  m_idleTime = idle;
}


void
ClientApp::SetUe(Ptr<UserEquipment> ue)
{
  NS_LOG_FUNCTION (this  << ue);
  m_ue = ue;
}

void
ClientApp::SetContextId(std::string contextId)
{
  NS_LOG_FUNCTION (this  << contextId);
  m_contextId = contextId;
}

void
ClientApp::SetMecApp(Ptr<MecApp> mecApp)
{
  NS_LOG_FUNCTION (this << mecApp);
  m_mecApp = mecApp;
}
void
ClientApp::SetTaskSize(Ptr<RandomVariableStream> taskSize)
{
  NS_LOG_FUNCTION (this);
  m_taskSize = taskSize;
}

void
ClientApp::SetInterarrivalTime(Ptr<RandomVariableStream> taskInterarrivalTime)
{
  NS_LOG_FUNCTION (this);
  m_taskInterarrivalTime = taskInterarrivalTime;
}

bool
ClientApp::GetState(void)
{
  NS_LOG_FUNCTION (this);
  return m_state;
}

Ptr<UserEquipment>
ClientApp::GetUe(void)
{
  NS_LOG_FUNCTION (this);
  return m_ue;
}

Ptr<MecApp>
ClientApp::GetMecApp(void)
{
  NS_LOG_FUNCTION (this);
  return m_mecApp;
}

void
ClientApp::Start(void)
{
  NS_LOG_FUNCTION (this);
  if(m_state == 1)
    {
      SendTaskOffloadingRequest();
      Time delay = Seconds(m_taskInterarrivalTime->GetValue());
      Simulator::Schedule(delay, &ClientApp::Start, this);
    }
}

void
ClientApp::SendTaskOffloadingRequest(void)
{
  NS_LOG_FUNCTION (this);
  Ptr<TaskOffloading> task = CreateObject<TaskOffloading>();
  task->SetIstructionNumber(m_taskSize->GetInteger());
  NS_LOG_INFO (m_taskSize->GetInteger());
  task->SetStartingTime(Now());
  task->SetClientApp(this);
  task->SetMecApp(GetMecApp());
  task->SetError(0);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(imsi: " << this->GetUe()->GetId()
  << ")\t\t\t\t Send \t\t" << task->GetInstanceTypeId().GetName()
  << "(Task size: "<< task->GetIstructionNumber() << " MI"
//  << "Starting Time: " << std::to_string(task->GetStartingTime().GetSeconds())
  << ")");
  if(m_state == 1)
    {
  Time delay = GetDelayModel()->GetRadioDelay(GetUe()->GetTargetBs()->GetAtiveFlow(task->GetMecApp()->GetAppD()->GetAppDId()), task->GetMecApp()->GetAppD()->GetAppDId());
  Simulator::Schedule(delay, &BaseStation::ForwardTaskOffloadingRequest, GetUe()->GetTargetBs(), task);
    }
}

void
ClientApp::ProcessTaskOffloadingResponse(Ptr<TaskOffloading> task)
{
  NS_LOG_FUNCTION (this);

  NS_LOG_DEBUG ("   \t" << this->GetInstanceTypeId() << "(imsi: " << this->GetUe()->GetId()
  << ")\t\t\t\t Process \t" << task->GetInstanceTypeId().GetName()
  << "(Task size: "<< task->GetIstructionNumber() << " MI, "
  << "Error: "<< task->GetError()
  << ", Starting Time: " << std::to_string(task->GetStartingTime().GetSeconds())
  << ", End-To-End Delay: " << std::to_string((Now() - task->GetStartingTime()).GetSeconds())
  << ", Processing Delay: " << std::to_string(task->GetProcessingTime().GetSeconds())
  << ")");

  double e2e = (Now() - task->GetStartingTime()).GetSeconds();
  double processing = task->GetProcessingTime().GetSeconds();

  sum_e2e = sum_e2e + e2e;
  n_e2e = n_e2e + 1;
  sum_processing = sum_processing + processing;
  n_processing = n_processing + 1;

  uint64_t hostId = DynamicCast<MecHostEntity>(GetMecApp()->GetMecPlataform()->GetNode())->GetId();
  GetUe()->GetLog()->TaskDelay(GetUe()->GetId(), m_contextId, m_appDiD,  hostId, e2e, processing);
}

void
ClientApp::DoActive(void)
{
  NS_LOG_FUNCTION (this);
  m_state = 1;
  Start();
  Time delay = Seconds(m_activeTime);
  Simulator::Schedule(delay, &ClientApp::DoIdle, this);
}

void
ClientApp::DoIdle(void)
{
  NS_LOG_FUNCTION (this);
  m_state = 0;
  Time delay = Seconds(m_idleTime);
  Simulator::Schedule(delay, &ClientApp::DoActive, this);
}

}
