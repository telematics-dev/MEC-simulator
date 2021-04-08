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


#include "mec-message-create-app-instance-identifier-request.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("CreateAppInstanceIdentifierRequest");

TypeId CreateAppInstanceIdentifierRequest::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CreateAppInstanceIdentifierRequest")
    .SetParent<Object> ();
  return tid;
}

CreateAppInstanceIdentifierRequest::CreateAppInstanceIdentifierRequest ()
{
  NS_LOG_FUNCTION (this);
}

CreateAppInstanceIdentifierRequest::~CreateAppInstanceIdentifierRequest ()
{
  NS_LOG_FUNCTION (this);
}

void
CreateAppInstanceIdentifierRequest::SetAppDId(uint64_t appDId)
{
  NS_LOG_FUNCTION (this << appDId);
  m_appDId = appDId;
}

void
CreateAppInstanceIdentifierRequest::SetAppInstanceName(std::string appInstanceName)
{
  NS_LOG_FUNCTION (this << appInstanceName);
  m_appInstanceName = appInstanceName;
}

void
CreateAppInstanceIdentifierRequest::SetAppInstanceDescription(std::string appInstanceDescription)
{
  NS_LOG_FUNCTION (this << appInstanceDescription);
  m_appInstanceDescription = appInstanceDescription;
}

uint64_t
CreateAppInstanceIdentifierRequest::GetAppDId()
{
  NS_LOG_FUNCTION (this);
  return m_appDId;
}

std::string
CreateAppInstanceIdentifierRequest::GetAppInstanceName()
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceName;
}

std::string
CreateAppInstanceIdentifierRequest::GetAppInstanceDescription()
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceDescription;
}

int
CreateAppInstanceIdentifierRequest::Size (void)
{
  int sz = sizeof(m_appDId) + m_appInstanceDescription.length() + m_appInstanceName.length();
  return sz;
}
} // namespace ns3
