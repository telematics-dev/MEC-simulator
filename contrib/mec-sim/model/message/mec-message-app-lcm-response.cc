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


#include "mec-message-app-lcm-response.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AppLcmResponse");

TypeId AppLcmResponse::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AppLcmResponse")
    .SetParent<Object> ();
  return tid;
}

AppLcmResponse::AppLcmResponse ()
{
  m_lifecycleOperationOccurrenceId =0;
  m_respCode=0;
  NS_LOG_FUNCTION (this);
}

AppLcmResponse::~AppLcmResponse ()
{
  NS_LOG_FUNCTION (this);
}


void
AppLcmResponse::SetLifecycleOperationOccurrenceId(uint64_t lifecycleOperationOccurrenceId)
{
  NS_LOG_FUNCTION (this << lifecycleOperationOccurrenceId);
  m_lifecycleOperationOccurrenceId = lifecycleOperationOccurrenceId;
}

void
AppLcmResponse::SetRespCode(uint16_t respCode)
{
  NS_LOG_FUNCTION (this << respCode);
  m_respCode = respCode;
}

void
AppLcmResponse::SetProblemDetails(std::string problemDetails)
{
  NS_LOG_FUNCTION (this << problemDetails);
  m_problemDetails = problemDetails;
}

uint64_t
AppLcmResponse::GetLifecycleOperationOccurrenceId()
{
  NS_LOG_FUNCTION (this);
  return m_lifecycleOperationOccurrenceId;
}

uint16_t
AppLcmResponse::GetRespCode()
{
  NS_LOG_FUNCTION (this);
  return m_respCode;
}

std::string
AppLcmResponse::GetProblemDetails()
{
  NS_LOG_FUNCTION (this);
  return m_problemDetails;
}

int
AppLcmResponse::Size (void)
{
  int sz = sizeof(m_respCode) + sizeof(m_lifecycleOperationOccurrenceId)+ m_problemDetails.length();
  return sz;
}

} //namespace ns3
