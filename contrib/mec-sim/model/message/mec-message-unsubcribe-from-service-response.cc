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


#include "mec-message-unsubcribe-from-service-response.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("UnsubscribeFromServiceResponse");

TypeId UnsubscribeFromServiceResponse::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::UnsubscribeFromServiceResponse")
    .SetParent<Object> ();
  return tid;
}

UnsubscribeFromServiceResponse::UnsubscribeFromServiceResponse ()
{
  m_respCode=0;
  m_appInstanceId=0;
  NS_LOG_FUNCTION (this);
}

UnsubscribeFromServiceResponse::~UnsubscribeFromServiceResponse ()
{
  NS_LOG_FUNCTION (this);
}

void
UnsubscribeFromServiceResponse::SetAppInstanceId(uint64_t appInstanceId)
{
  NS_LOG_FUNCTION (this << appInstanceId);
  m_appInstanceId = appInstanceId;
}

void
UnsubscribeFromServiceResponse::SetRespCode(uint16_t respCode)
{
  NS_LOG_FUNCTION (this << respCode);
  m_respCode = respCode;
}

void
UnsubscribeFromServiceResponse::SetProblemDetails(std::string problemDetails)
{
  NS_LOG_FUNCTION (this << problemDetails);
  m_problemDetails = problemDetails;
}

uint64_t
UnsubscribeFromServiceResponse::GetAppInstanceId()
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceId;
}

uint16_t
UnsubscribeFromServiceResponse::GetRespCode()
{
  NS_LOG_FUNCTION (this);
  return m_respCode;
}

std::string
UnsubscribeFromServiceResponse::GetProblemDetails()
{
  NS_LOG_FUNCTION (this);
  return m_problemDetails;
}

int
UnsubscribeFromServiceResponse::Size()
{
  int sz = sizeof(m_appInstanceId) + sizeof(m_respCode) + m_problemDetails.length();
  return sz;
}

} // namespace ns3
