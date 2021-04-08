/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014 TELEMATICS LAB, DEI - Politecnico di Bari
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
 *         Simona Massari - s.massari@studenti.poliba.it
 */

#ifndef MEC_DATA_TRAFFIC_RULE_DESCRIPTOR_H
#define MEC_DATA_TRAFFIC_RULE_DESCRIPTOR_H



#include <ns3/ipv4-address.h>
#include <ns3/core-module.h>

namespace ns3 {


class TrafficRuleDescriptor : public Object
{
  public:
    static TypeId GetTypeId (void);
    TrafficRuleDescriptor ();
    virtual ~TrafficRuleDescriptor ();

  private:
    Ipv4Address m_srcAddress;
    Ipv4Address m_dstAddress;
    uint16_t    m_srcPort;
    uint16_t    m_dstPort;
    std::string m_protocol;
    uint8_t     m_qos5qi;
    bool        m_qosResourceType;
    double      m_qosGbrDl; //Mbit/s
    double      m_qosGbrUl; //Mbit/s

  public:
    void SetSrcAddress (Ipv4Address srcAddress);
    Ipv4Address GetSrcAddress (void);
    void SetDstAddress (Ipv4Address dstAddress);
    Ipv4Address GetDstAddress (void);
    void SetSrcPort (uint16_t srcPort);
    uint16_t GetSrcPort (void);
    void SetDstPort (uint16_t dstPort);
    uint16_t GetDstPort (void);
    void SetProtocol (std::string protocol);
    std::string GetProtocol (void);
    void SetQos5qi (uint8_t qos5qi);
    uint8_t GetQos5qi (void);
    void SetQosResourceType (bool qosResourceType);
    bool GetQosResourceType (void);
    void SetQosGbrDl (double qosGbrDl);
    double GetQosGbrDl (void);
    void SetQosGbrUl (double qosGbrUl);
    double GetQosGbrUl (void);
    int Size (void);
};


}

#endif /* MEC_DATA_DNS_RULE_DESCRIPTOR_H */

