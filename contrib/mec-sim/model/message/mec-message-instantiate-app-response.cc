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


#include "mec-message-instantiate-app-response.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("InstantiateAppResponse");

TypeId InstantiateAppResponse::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::InstantiateAppResponse")
    .SetParent<Object> ();
  return tid;
}

InstantiateAppResponse::InstantiateAppResponse ()
{
  m_respCode=0;
  m_appInstanceId=0;
  NS_LOG_FUNCTION (this);
}

InstantiateAppResponse::~InstantiateAppResponse ()
{
  NS_LOG_FUNCTION (this);
}

uint64_t
InstantiateAppResponse::GetAppInstanceId (void)
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceId;
}

void
InstantiateAppResponse::SetAppInstanceId (uint64_t appInstanceId)
{
  NS_LOG_FUNCTION (this << appInstanceId);
  m_appInstanceId = appInstanceId;
}


void
InstantiateAppResponse::SetRespCode(uint16_t respCode)
{
  NS_LOG_FUNCTION (this << respCode);
  m_respCode = respCode;
}

void
InstantiateAppResponse::SetProblemDetails(std::string problemDetails)
{
  NS_LOG_FUNCTION (this << problemDetails);
  m_problemDetails = problemDetails;
}

uint16_t
InstantiateAppResponse::GetRespCode()
{
  NS_LOG_FUNCTION (this);
  return m_respCode;
}

std::string
InstantiateAppResponse::GetProblemDetails()
{
  NS_LOG_FUNCTION (this);
  return m_problemDetails;
}

void
InstantiateAppResponse::SetReferenceUri(Ptr<MecApp> referenceUri)
{
  NS_LOG_FUNCTION (this << referenceUri);
  m_referenceUri = referenceUri;
}

Ptr<MecApp>
InstantiateAppResponse::GetReferenceUri (void)
{
  NS_LOG_FUNCTION (this);
  return m_referenceUri;
}


int
InstantiateAppResponse::Size(void)
{
  int sz = sizeof(m_respCode) + m_problemDetails.length()+ sizeof(m_referenceUri) + sizeof(m_appInstanceId);
  return sz;
}


} //namespace ns3
