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


#include "mec-message-instantiate-app-request.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("InstantiateAppRequest");

TypeId InstantiateAppRequest::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::InstantiateAppRequest")
    .SetParent<Object> ();
  return tid;
}

InstantiateAppRequest::InstantiateAppRequest ()
{
  NS_LOG_FUNCTION (this);
}

InstantiateAppRequest::~InstantiateAppRequest ()
{
  NS_LOG_FUNCTION (this);
}

uint64_t
InstantiateAppRequest::GetAppInstanceId (void)
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceId;
}

void
InstantiateAppRequest::SetAppInstanceId (uint64_t appInstanceId)
{
  NS_LOG_FUNCTION (this << appInstanceId);
  m_appInstanceId = appInstanceId;
}

void
InstantiateAppRequest::SetVirtualResourceDescriptor (Ptr<VirtualResourceDescriptor> virtualResourceDescriptor)
{
  NS_LOG_FUNCTION (this << virtualResourceDescriptor);
  m_virtualResourceDescriptor = virtualResourceDescriptor;
}

Ptr<VirtualResourceDescriptor>
InstantiateAppRequest::GetVirtualResourceDescriptor (void)
{
  NS_LOG_FUNCTION (this);
  return m_virtualResourceDescriptor;
}

void
InstantiateAppRequest::SetSelectedMECHostInfo (uint64_t hostId)
{
  NS_LOG_FUNCTION (this << hostId);
  m_selectedMECHostInfo = hostId;
}

uint64_t
InstantiateAppRequest::GetSelectedMECHostInfo(void)
{
  NS_LOG_FUNCTION (this);
  return m_selectedMECHostInfo;
}

void
InstantiateAppRequest::SetLocationConstraints (std::string locationConstraints)
{
  NS_LOG_FUNCTION (this << locationConstraints);
  m_locationConstraints = locationConstraints;
}

std::string
InstantiateAppRequest::GetLocationConstraints(void)
{
  NS_LOG_FUNCTION (this);
  return m_locationConstraints;
}

int
InstantiateAppRequest::Size(void)
{
  int sz = m_virtualResourceDescriptor->Size() + m_locationConstraints.length() + sizeof(m_selectedMECHostInfo)+ sizeof(m_appInstanceId);
  return sz;
}


} //namespace ns3
