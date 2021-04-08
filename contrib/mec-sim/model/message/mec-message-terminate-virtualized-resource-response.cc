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


#include "mec-message-terminate-virtualized-resource-response.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TerminateVirtualResourceResponse");

TypeId TerminateVirtualResourceResponse::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TerminateVirtualResourceResponse")
    .SetParent<Object> ();
  return tid;
}

TerminateVirtualResourceResponse::TerminateVirtualResourceResponse ()
{
  m_respCode=0;
  m_virResInstId=0;
  NS_LOG_FUNCTION (this);
}

TerminateVirtualResourceResponse::~TerminateVirtualResourceResponse ()
{
  NS_LOG_FUNCTION (this);
}

void
TerminateVirtualResourceResponse::SetVirResInstId(uint64_t virResInstId)
{
  NS_LOG_FUNCTION (this << virResInstId);
  m_virResInstId = virResInstId;
}

void
TerminateVirtualResourceResponse::SetRespCode(uint16_t respCode)
{
  NS_LOG_FUNCTION (this << respCode);
  m_respCode = respCode;
}

void
TerminateVirtualResourceResponse::SetProblemDetails(std::string problemDetails)
{
  NS_LOG_FUNCTION (this << problemDetails);
  m_problemDetails = problemDetails;
}

uint64_t
TerminateVirtualResourceResponse::GetVirResInstId()
{
  NS_LOG_FUNCTION (this);
  return m_virResInstId;
}

uint16_t
TerminateVirtualResourceResponse::GetRespCode()
{
  NS_LOG_FUNCTION (this);
  return m_respCode;
}

std::string
TerminateVirtualResourceResponse::GetProblemDetails()
{
  NS_LOG_FUNCTION (this);
  return m_problemDetails;
}

int
TerminateVirtualResourceResponse::Size()
{
  int sz = sizeof(m_virResInstId) + sizeof(m_respCode) + m_problemDetails.length();
  return sz;
}

} // namespace ns3
