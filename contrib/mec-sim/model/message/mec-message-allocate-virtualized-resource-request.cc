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


#include "mec-message-allocate-virtualized-resource-request.h"

#include "ns3/log.h"

namespace ns3 {

 NS_LOG_COMPONENT_DEFINE ("AllocateVirtualizedResRequest");

  TypeId AllocateVirtualizedResRequest::GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::AllocateVirtualizedResRequest")
      .SetParent<Object> ();
    return tid;
  }

  AllocateVirtualizedResRequest::AllocateVirtualizedResRequest ()
  {
    NS_LOG_FUNCTION (this);
  }

  AllocateVirtualizedResRequest::~AllocateVirtualizedResRequest ()
  {
    NS_LOG_FUNCTION (this);
  }

  void
  AllocateVirtualizedResRequest::SetVirtualResourceInstance(Ptr<VirtualResourceInstance> virtualResourceInstance)
  {
    NS_LOG_FUNCTION (this << virtualResourceInstance);
    m_virtualResourceInstance = virtualResourceInstance;
  }

  Ptr<VirtualResourceInstance>
  AllocateVirtualizedResRequest::GetVirtualResourceInstance()
   {
     NS_LOG_FUNCTION (this);
     return m_virtualResourceInstance;
   }

  int
  AllocateVirtualizedResRequest::Size (void)
  {
    int sz = m_virtualResourceInstance->Size();
    return sz;
  }
} //namespace ns3
