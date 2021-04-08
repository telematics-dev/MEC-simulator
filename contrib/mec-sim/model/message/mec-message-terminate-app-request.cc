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


#include "mec-message-terminate-app-request.h"
#include "ns3/log.h"

namespace ns3 {

 NS_LOG_COMPONENT_DEFINE ("TerminateAppRequest");

  TypeId TerminateAppRequest::GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::TerminateAppRequest")
      .SetParent<Object> ();
    return tid;
  }

  TerminateAppRequest::TerminateAppRequest ()
  {
    m_instance = 0;
    m_terminationType = 0;
    m_gracefullTerminationTimeout = 0;
    NS_LOG_FUNCTION (this);
  }

  TerminateAppRequest::~TerminateAppRequest ()
  {
    NS_LOG_FUNCTION (this);
  }

  void
  TerminateAppRequest::SetInstance (Ptr<AppInstanceInfo> instanceId)
  {
    NS_LOG_FUNCTION (this << instanceId);
    m_instance = instanceId;
  }

  void
  TerminateAppRequest::SetTerminationType (bool terminationType)
  {
    NS_LOG_FUNCTION (this << terminationType);
    m_terminationType = terminationType;
  }

  void
  TerminateAppRequest::SetGracefullTerminationTimeout (double gracefullTerminationTimeout)
  {
    NS_LOG_FUNCTION (this << gracefullTerminationTimeout);
    m_gracefullTerminationTimeout = gracefullTerminationTimeout;
  }

  Ptr<AppInstanceInfo>
  TerminateAppRequest::GetInstance (void)
  {
    NS_LOG_FUNCTION (this);
    return m_instance;
  }

  bool
  TerminateAppRequest::GetTerminationType (void)
  {
    NS_LOG_FUNCTION (this);
    return m_terminationType;
  }

  double
  TerminateAppRequest::GetGracefullTerminationTimeout (void)
  {
    NS_LOG_FUNCTION (this);
    return m_gracefullTerminationTimeout;
  }

  int
  TerminateAppRequest::Size(void)
  {
    int sz = sizeof(m_instance) +
	sizeof(m_terminationType) +
	sizeof(m_gracefullTerminationTimeout);
    return sz;
  }
} //namespace ns3
