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


#include "mec-data-dns-rule-descriptor.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DnsRuleDescriptor");

TypeId DnsRuleDescriptor::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DnsRuleDescriptor")
    .SetParent<Object> ();
  return tid;
}

DnsRuleDescriptor::DnsRuleDescriptor ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
  SetDnsRuleId("0");
  SetDomainName("app.test.mec");
  SetIpAddressType("ipv4");
  SetIpAddress("000.000.000.000");
  SetTtl(600);
}

DnsRuleDescriptor::~DnsRuleDescriptor()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
DnsRuleDescriptor::SetDnsRuleId (std::string dnsRuleId)
{
  NS_LOG_FUNCTION (this->GetTypeId() << dnsRuleId);
  m_dnsRuleId = dnsRuleId;
}

std::string
DnsRuleDescriptor::GetDnsRuleId (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_dnsRuleId;
}

void
DnsRuleDescriptor::SetDomainName (std::string domainName)
{
  NS_LOG_FUNCTION (this->GetTypeId() << domainName);
  m_domainName = domainName;
}

std::string
DnsRuleDescriptor::GetDomainName (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_domainName;
}

void
DnsRuleDescriptor::SetIpAddressType (std::string ipAddressType)
{
  NS_LOG_FUNCTION (this->GetTypeId() << ipAddressType);
  m_ipAddressType = ipAddressType;
}

std::string
DnsRuleDescriptor::GetIpAddressType (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_ipAddressType;
}

void
DnsRuleDescriptor::SetIpAddress (Ipv4Address ipAddress)
{
  NS_LOG_FUNCTION (this->GetTypeId() << ipAddress);
  m_ipAddress = ipAddress;
}

Ipv4Address
DnsRuleDescriptor::GetIpAddress (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_ipAddress;
}

void
DnsRuleDescriptor::SetTtl (double ttl)
{
  NS_LOG_FUNCTION (this->GetTypeId() << ttl);
  m_ttl = ttl;
}

double
DnsRuleDescriptor::GetTtl(void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_ttl;
}
int
DnsRuleDescriptor::Size (void)
{
  int sz = m_dnsRuleId.length() + m_domainName.length() + m_ipAddressType.length() + sizeof(m_ipAddress.Get()) + sizeof(m_ttl) ;
  return sz;
}
} // namespace ns3
