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


#include "mec-data-service-descriptor.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ServiceDescriptor");

TypeId ServiceDescriptor::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ServiceDescriptor")
    .SetParent<Object> ();
  return tid;
}

ServiceDescriptor::ServiceDescriptor ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

ServiceDescriptor::~ServiceDescriptor()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
ServiceDescriptor::SetSerName (std::string serName)
{
  NS_LOG_FUNCTION (this->GetTypeId() << serName);
  m_serName = serName;
}

std::string
ServiceDescriptor::GetSerName (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_serName;
}

void
ServiceDescriptor::SetSerCategory (std::string serCategory)
{
  NS_LOG_FUNCTION (this->GetTypeId() << serCategory);
  m_serCategory = serCategory;
}

std::string
ServiceDescriptor::GetSerCategory (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_serCategory;
}

void
ServiceDescriptor::SetVersion (std::string version)
{
  NS_LOG_FUNCTION (this->GetTypeId() << version);
  m_version = version;
}

std::string
ServiceDescriptor::GetVersion (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_version;
}

void
ServiceDescriptor::SetTransportsSupported (std::string transportsSupported)
{
  NS_LOG_FUNCTION (this->GetTypeId() << transportsSupported);
  m_transportsSupported = transportsSupported;
}

std::string
ServiceDescriptor::GetTransportsSupported (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_transportsSupported;
}

int
ServiceDescriptor::Size (void)
{
  int sz = m_serName.length() + m_serCategory.length() + m_version.length() + m_transportsSupported.length();
  return sz;
}
} // namespace ns3
