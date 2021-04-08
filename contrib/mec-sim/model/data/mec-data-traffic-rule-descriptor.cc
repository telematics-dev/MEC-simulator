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


#include "mec-data-traffic-rule-descriptor.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TrafficRuleDescriptor");

TypeId TrafficRuleDescriptor::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TrafficRuleDescriptor")
    .SetParent<Object> ();
  return tid;
}

TrafficRuleDescriptor::TrafficRuleDescriptor ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
  SetSrcAddress("000.000.000.000");
  SetDstAddress("000.000.000.000");
  SetSrcPort(5120);
  SetDstPort(5120);
  SetProtocol("tcp");
  SetQos5qi(3);
  SetQosResourceType(1);
}

TrafficRuleDescriptor::~TrafficRuleDescriptor()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
TrafficRuleDescriptor::SetSrcAddress (Ipv4Address srcAddress)
{
  NS_LOG_FUNCTION (this->GetTypeId() << srcAddress);
  m_srcAddress = srcAddress;
}

Ipv4Address
TrafficRuleDescriptor::GetSrcAddress (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_srcAddress;
}

void
TrafficRuleDescriptor::SetDstAddress (Ipv4Address dstAddress)
{
  NS_LOG_FUNCTION (this->GetTypeId() << dstAddress);
  m_dstAddress = dstAddress;
}

Ipv4Address
TrafficRuleDescriptor::GetDstAddress (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_dstAddress;
}

void
TrafficRuleDescriptor::SetSrcPort (uint16_t srcPort)
{
  NS_LOG_FUNCTION (this->GetTypeId() << srcPort);
  m_srcPort = srcPort;
}

uint16_t
TrafficRuleDescriptor::GetSrcPort (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_srcPort;
}

void
TrafficRuleDescriptor::SetDstPort (uint16_t dstPort)
{
  NS_LOG_FUNCTION (this->GetTypeId() << dstPort);
  m_dstPort = dstPort;
}

uint16_t
TrafficRuleDescriptor::GetDstPort (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_dstPort;
}

void
TrafficRuleDescriptor::SetProtocol (std::string protocol)
{
  NS_LOG_FUNCTION (this->GetTypeId() << protocol);
  m_protocol = protocol;
}

std::string
TrafficRuleDescriptor::GetProtocol (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_protocol;
}

void
TrafficRuleDescriptor::SetQos5qi (uint8_t qos5qi)
{
  NS_LOG_FUNCTION (this->GetTypeId() << qos5qi);
  m_qos5qi = qos5qi;
}

uint8_t
TrafficRuleDescriptor::GetQos5qi (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_qos5qi;
}

void
TrafficRuleDescriptor::SetQosResourceType (bool qosResourceType)
{
  NS_LOG_FUNCTION (this->GetTypeId() << qosResourceType);
  m_qosResourceType = qosResourceType;
}

bool
TrafficRuleDescriptor::GetQosResourceType (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_qosResourceType;
}

void
TrafficRuleDescriptor::SetQosGbrDl (double qosGbrDl)
{
  NS_LOG_FUNCTION (this->GetTypeId() << qosGbrDl);
  m_qosGbrDl = qosGbrDl;
}

double
TrafficRuleDescriptor::GetQosGbrDl (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_qosGbrDl;
}

void
TrafficRuleDescriptor::SetQosGbrUl (double qosGbrUl)
{
  NS_LOG_FUNCTION (this->GetTypeId() << qosGbrUl);
  m_qosGbrUl = qosGbrUl;
}

double
TrafficRuleDescriptor::GetQosGbrUl (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_qosGbrUl;
}

int
TrafficRuleDescriptor::Size (void)
{
  int sz = sizeof(m_srcAddress.Get()) +
	    sizeof(m_dstAddress.Get()) +
	    sizeof(m_srcPort) +
	    sizeof(m_dstPort) +
	    m_protocol.length() +
	    sizeof(m_qos5qi) +
	    sizeof(m_qosResourceType) +
	    sizeof(m_qosGbrDl) +
	    sizeof(m_qosGbrUl);
  return sz;
}
} // namespace ns3
