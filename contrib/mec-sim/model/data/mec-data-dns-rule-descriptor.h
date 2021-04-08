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

#ifndef MEC_DATA_DNS_RULE_DESCRIPTOR_H
#define MEC_DATA_DNS_RULE_DESCRIPTOR_H


#include <ns3/ipv4-address.h>
#include <ns3/core-module.h>

namespace ns3 {

class DnsRuleDescriptor : public Object
{
public:
  static TypeId GetTypeId (void);
  DnsRuleDescriptor ();
  virtual ~DnsRuleDescriptor ();

private:
  std::string m_dnsRuleId;
  std::string m_domainName;
  std::string m_ipAddressType;
  Ipv4Address m_ipAddress;
  double      m_ttl;

public:
  void SetDnsRuleId (std::string dnsRuleId);
  std::string GetDnsRuleId (void);
  void SetDomainName (std::string domainName);
  std::string GetDomainName (void);
  void SetIpAddressType (std::string ipAddressType);
  std::string GetIpAddressType (void);
  void SetIpAddress (Ipv4Address ipAddress);
  Ipv4Address GetIpAddress (void);
  void SetTtl (double ttl);
  double GetTtl(void);
  int Size (void);
};

}

#endif /* MEC_DATA_DNS_RULE_DESCRIPTOR_H */

