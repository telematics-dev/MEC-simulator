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


#include "mec-message-terminate-virtualized-resource-request.h"
#include "ns3/log.h"

namespace ns3 {

 NS_LOG_COMPONENT_DEFINE ("TerminateVirtualResourceRequest");

  TypeId TerminateVirtualResourceRequest::GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::TerminateVirtualResourceRequest")
      .SetParent<Object> ();
    return tid;
  }

  TerminateVirtualResourceRequest::TerminateVirtualResourceRequest ()
  {
    m_virResInstId = 0;
    NS_LOG_FUNCTION (this);
  }

  TerminateVirtualResourceRequest::~TerminateVirtualResourceRequest ()
  {
    NS_LOG_FUNCTION (this);
  }

  void
  TerminateVirtualResourceRequest::SetVirResInstId (uint64_t virResInstId)
  {
    NS_LOG_FUNCTION (this << virResInstId);
    m_virResInstId = virResInstId;
  }

  uint64_t
  TerminateVirtualResourceRequest::GetVirResInstId (void)
  {
    NS_LOG_FUNCTION (this);
    return m_virResInstId;
  }

  int
  TerminateVirtualResourceRequest::Size(void)
  {
    int sz = sizeof(m_virResInstId);
    return sz;
  }
} //namespace ns3
