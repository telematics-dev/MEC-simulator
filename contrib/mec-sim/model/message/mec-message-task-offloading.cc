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


#include "mec-message-task-offloading.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TaskOffloading");

TypeId TaskOffloading::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TaskOffloading")
    .SetParent<Object> ();
  return tid;
}

TaskOffloading::TaskOffloading ()
{
  m_istructions = 0;
  m_startingTime = Seconds(0);
  NS_LOG_FUNCTION (this);
}

TaskOffloading::~TaskOffloading ()
{
  NS_LOG_FUNCTION (this);
}

uint64_t
TaskOffloading::GetIstructionNumber (void)
{
  NS_LOG_FUNCTION (this);
  return m_istructions;
}

Time
TaskOffloading::GetStartingTime (void)
{
  NS_LOG_FUNCTION (this);
  return m_startingTime;
}

Time
TaskOffloading::GetProcessingTime (void)
{
  NS_LOG_FUNCTION (this);
  return m_processingTime;
}


Ptr<ClientApp>
TaskOffloading::GetClientApp (void)
{
  NS_LOG_FUNCTION (this);
  return m_clientApp;
}

Ptr<MecApp>
TaskOffloading::GetMecApp (void)
{
  NS_LOG_FUNCTION (this);
  return m_mecApp;
}

bool
TaskOffloading::GetError (void)
{
  NS_LOG_FUNCTION (this);
  return m_error;
}

void
TaskOffloading::SetIstructionNumber (uint64_t istruction)
{
  NS_LOG_FUNCTION (this << istruction);
  m_istructions = istruction;
}


void
TaskOffloading::SetStartingTime (Time time)
{
  NS_LOG_FUNCTION (this << time);
  m_startingTime = time;
}

void
TaskOffloading::SetProcessingTime (Time time)
{
  NS_LOG_FUNCTION (this << time);
  m_processingTime = time;
}

void
TaskOffloading::SetClientApp (Ptr<ClientApp> clientApp)
{
  NS_LOG_FUNCTION (this << clientApp);
  m_clientApp = clientApp;
}

void
TaskOffloading::SetMecApp (Ptr<MecApp> mecApp)
{
  NS_LOG_FUNCTION (this << mecApp);
  m_mecApp = mecApp;
}

void
TaskOffloading::SetError (bool error)
{
  NS_LOG_FUNCTION (this << error);
  m_error = error;
}

} //namespace ns3
