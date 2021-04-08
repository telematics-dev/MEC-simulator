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


#include "mec-message-mec-app-instance-configuration-response.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecAppInstanceConfigurationResponse");

TypeId MecAppInstanceConfigurationResponse::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecAppInstanceConfigurationResponse")
    .SetParent<Object> ();
  return tid;
}

MecAppInstanceConfigurationResponse::MecAppInstanceConfigurationResponse ()
{
  m_instanceId=0;
  m_respCode=0;
  NS_LOG_FUNCTION (this);
}

MecAppInstanceConfigurationResponse::~MecAppInstanceConfigurationResponse ()
{
  NS_LOG_FUNCTION (this);
}

void
MecAppInstanceConfigurationResponse::SetInstanceId(uint64_t instanceId)
{
  NS_LOG_FUNCTION (this << instanceId);
  m_instanceId = instanceId;
}

uint64_t
MecAppInstanceConfigurationResponse::GetInstanceId()
{
  NS_LOG_FUNCTION (this);
  return m_instanceId;
}

void
MecAppInstanceConfigurationResponse::SetRespCode(uint16_t respCode)
{
  NS_LOG_FUNCTION (this << respCode);
  m_respCode = respCode;
}

void
MecAppInstanceConfigurationResponse::SetProblemDetails(std::string problemDetails)
{
  NS_LOG_FUNCTION (this << problemDetails);
  m_problemDetails = problemDetails;
}

uint16_t
MecAppInstanceConfigurationResponse::GetRespCode()
{
  NS_LOG_FUNCTION (this);
  return m_respCode;
}

std::string
MecAppInstanceConfigurationResponse::GetProblemDetails()
{
  NS_LOG_FUNCTION (this);
  return m_problemDetails;
}

void
MecAppInstanceConfigurationResponse::SetReferenceUri(Ptr<MecApp> referenceUri)
{
  NS_LOG_FUNCTION (this << referenceUri);
  m_referenceUri = referenceUri;
}

Ptr<MecApp>
MecAppInstanceConfigurationResponse::GetReferenceUri (void)
{
  NS_LOG_FUNCTION (this);
  return m_referenceUri;
}

int
MecAppInstanceConfigurationResponse::Size (void)
{
  NS_LOG_FUNCTION (this);

  int sz = sizeof(m_instanceId) +sizeof(m_respCode) + sizeof(m_referenceUri) + m_problemDetails.length();

  return sz;
}

} //namespace ns3
