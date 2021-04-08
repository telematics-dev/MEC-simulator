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


#include "mec-message-delete-app-context-request.h"
#include "ns3/log.h"

namespace ns3 {

 NS_LOG_COMPONENT_DEFINE ("DeleteAppContextRequest");

  TypeId DeleteAppContextRequest::GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::DeleteAppContextRequest")
      .SetParent<Object> ();
    return tid;
  }

  DeleteAppContextRequest::DeleteAppContextRequest ()
  {
    NS_LOG_FUNCTION (this);
  }

  DeleteAppContextRequest::~DeleteAppContextRequest ()
  {
    NS_LOG_FUNCTION (this);
  }

  void
  DeleteAppContextRequest::SetContextId(std::string contextId)
  {
    NS_LOG_FUNCTION (this << contextId);
    m_contextId = contextId;
  }

  std::string
  DeleteAppContextRequest::GetContextId()
  {
    NS_LOG_FUNCTION (this);
    return m_contextId;
  }

  void
  DeleteAppContextRequest::SetCallbackReference(Ptr<UserEquipment> callbackReference)
  {
    NS_LOG_FUNCTION (this << callbackReference);
    m_callbackReference = callbackReference;
  }

  Ptr<UserEquipment>
  DeleteAppContextRequest::GetCallbackReference (void)
  {
    NS_LOG_FUNCTION (this);
    return m_callbackReference;
  }

  int
  DeleteAppContextRequest::Size(void)
  {
    int sz = m_contextId.length()+ sizeof(m_callbackReference);
    return sz;
  }

} //namespace ns3
