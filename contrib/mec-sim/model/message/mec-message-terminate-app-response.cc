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


#include "mec-message-terminate-app-response.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TerminateAppResponse");

TypeId TerminateAppResponse::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TerminateAppResponse")
    .SetParent<Object> ();
  return tid;
}

TerminateAppResponse::TerminateAppResponse ()
{
  m_respCode=0;
  m_appInstance=0;
  NS_LOG_FUNCTION (this);
}

TerminateAppResponse::~TerminateAppResponse ()
{
  NS_LOG_FUNCTION (this);
}

void
TerminateAppResponse::SetAppInstance(Ptr<AppInstanceInfo> appInstance)
{
  NS_LOG_FUNCTION (this << appInstance);
  m_appInstance = appInstance;
}

void
TerminateAppResponse::SetRespCode(uint16_t respCode)
{
  NS_LOG_FUNCTION (this << respCode);
  m_respCode = respCode;
}

void
TerminateAppResponse::SetProblemDetails(std::string problemDetails)
{
  NS_LOG_FUNCTION (this << problemDetails);
  m_problemDetails = problemDetails;
}

Ptr<AppInstanceInfo>
TerminateAppResponse::GetAppInstance()
{
  NS_LOG_FUNCTION (this);
  return m_appInstance;
}

uint16_t
TerminateAppResponse::GetRespCode()
{
  NS_LOG_FUNCTION (this);
  return m_respCode;
}

std::string
TerminateAppResponse::GetProblemDetails()
{
  NS_LOG_FUNCTION (this);
  return m_problemDetails;
}

int
TerminateAppResponse::Size()
{
  int sz = sizeof(m_appInstance) + sizeof(m_respCode) + m_problemDetails.length();
  return sz;
}

} // namespace ns3
