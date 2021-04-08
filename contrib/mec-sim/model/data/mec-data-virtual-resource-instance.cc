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


#include "mec-data-virtual-resource-instance.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("VirtualResourceInstance");

TypeId VirtualResourceInstance::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::VirtualResourceInstance")
    .SetParent<Object> ();
  return tid;
}

VirtualResourceInstance::VirtualResourceInstance ()
{
  m_hostId = 0;
  m_virResInstId =0;
  m_allocationType = 0;
  NS_LOG_FUNCTION (this);
}

VirtualResourceInstance::~VirtualResourceInstance ()
{
  NS_LOG_FUNCTION (this);
}

void
VirtualResourceInstance::CreateUserData (double sz)
{
  NS_LOG_FUNCTION (this << sz);
  m_userData = CreateObject<UserData> ();
  m_userData->SetSize(sz);
}

uint64_t
VirtualResourceInstance::GetVirResInstId(void)
{
  NS_LOG_FUNCTION (this);
  return m_virResInstId;
}

Ptr<VirtualResourceDescriptor>
VirtualResourceInstance::GetVirtualResource(void)
{
  NS_LOG_FUNCTION (this);
  return m_virtualResource;
}

uint64_t
VirtualResourceInstance::GetHostId(void)
{
  NS_LOG_FUNCTION (this);
  return m_hostId;
}

uint8_t
VirtualResourceInstance::GetAllocationType (void)
{
  NS_LOG_FUNCTION (this);
  return m_allocationType;
}


void
VirtualResourceInstance::SetVirResInstId(uint64_t virResInstId)
{
  NS_LOG_FUNCTION (this << virResInstId);
  m_virResInstId = virResInstId;
}

void
VirtualResourceInstance::SetVirtualResource(Ptr<VirtualResourceDescriptor> virtualResource)
{
  NS_LOG_FUNCTION (this << virtualResource);
  m_virtualResource = virtualResource;
}

void
VirtualResourceInstance::SetHostId(uint64_t hostId)
{
  NS_LOG_FUNCTION (this << hostId);
  m_hostId = hostId;
}

void
VirtualResourceInstance::SetAllocationType (uint8_t allocationType)
{
  NS_LOG_FUNCTION (this << allocationType);
  m_allocationType = allocationType;
}


int
VirtualResourceInstance::Size (void)
{
  int sz = sizeof(m_virResInstId) +
      sizeof(m_virtualResource) +
      sizeof(m_hostId) +
//      m_userData->GetSize()+
      sizeof(m_allocationType);
  return sz;
}

VirtualResourceInstance::UserData::UserData ()
{
  m_size = 0;
  NS_LOG_FUNCTION (this);
}

VirtualResourceInstance::UserData::~UserData ()
{
  NS_LOG_FUNCTION (this);
}

TypeId VirtualResourceInstance::UserData::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::UserData")
    .SetParent<Object> ();
  return tid;
}

void
VirtualResourceInstance::UserData::SetSize(double sz)
{
  NS_LOG_FUNCTION (this << sz);
  m_size = sz;
}

double
VirtualResourceInstance::UserData::GetSize(void)
{
  NS_LOG_FUNCTION (this);
  return m_size;
}
} // namespace ns3
