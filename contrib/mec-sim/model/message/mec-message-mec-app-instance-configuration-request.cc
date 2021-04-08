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


#include "mec-message-mec-app-instance-configuration-request.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecAppInstanceConfigurationRequest");

TypeId MecAppInstanceConfigurationRequest::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecAppInstanceConfigurationRequest")
    .SetParent<Object> ();
  return tid;
}

MecAppInstanceConfigurationRequest::MecAppInstanceConfigurationRequest ()
{
  NS_LOG_FUNCTION (this);
}

MecAppInstanceConfigurationRequest::~MecAppInstanceConfigurationRequest ()
{
  NS_LOG_FUNCTION (this);
}

void
MecAppInstanceConfigurationRequest::SetAppD(Ptr<AppD> appD)
{
  NS_LOG_FUNCTION (this << appD);
  m_appD = appD;
}

Ptr<AppD>
MecAppInstanceConfigurationRequest::GetAppD()
{
  NS_LOG_FUNCTION (this);
  return m_appD;
}

void
MecAppInstanceConfigurationRequest::SetMecApp(Ptr<MecApp> mecApp)
{
  NS_LOG_FUNCTION (this << mecApp);
  m_mecApp = mecApp;
}

Ptr<MecApp>
MecAppInstanceConfigurationRequest::GetMecApp()
{
  NS_LOG_FUNCTION (this);
  return m_mecApp;
}

uint64_t
MecAppInstanceConfigurationRequest::GetInstanceId (void)
{
  NS_LOG_FUNCTION (this);
  return m_instanceId;
}

void
MecAppInstanceConfigurationRequest::SetInstanceId (uint64_t instanceId)
{
  NS_LOG_FUNCTION (this << instanceId);
  m_instanceId = instanceId;
}

int
MecAppInstanceConfigurationRequest::Size (void)
{
  NS_LOG_FUNCTION (this);

  int sz = sizeof(m_mecApp) + m_appD->Size() + sizeof(m_instanceId);

  return sz;
}

} //namespace ns3
