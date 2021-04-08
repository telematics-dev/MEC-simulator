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


#include "mec-data-virtual-resource-descriptor.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("VirtualResourceDescriptor");

TypeId VirtualResourceDescriptor::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::VirtualResourceDescriptor")
    .SetParent<Object> ();
  return tid;
}

VirtualResourceDescriptor::VirtualResourceDescriptor ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

VirtualResourceDescriptor::~VirtualResourceDescriptor()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
VirtualResourceDescriptor::SetVirtualCpu (Ptr<VirtualCpu> virtualCpu)
{
  NS_LOG_FUNCTION (this->GetTypeId() << virtualCpu->GetTypeId());
  m_virtualCpu = virtualCpu;
}

Ptr<VirtualCpu>
VirtualResourceDescriptor::GetVirtualCpu (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_virtualCpu;
}

void
VirtualResourceDescriptor::SetVirtualMemory (Ptr<VirtualMemory> virtualMemory)
{
  NS_LOG_FUNCTION (this->GetTypeId() << virtualMemory->GetTypeId());
  m_virtualMemory = virtualMemory;
}

Ptr<VirtualMemory>
VirtualResourceDescriptor::GetVirtualMemory (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_virtualMemory;

}

void
VirtualResourceDescriptor::SetVirtualStorage (Ptr<VirtualStorage> virtualStorage)
{
  NS_LOG_FUNCTION (this->GetTypeId() << virtualStorage->GetTypeId());
  m_virtualStorage = virtualStorage;
}

Ptr<VirtualStorage>
VirtualResourceDescriptor::GetVirtualStorage (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_virtualStorage;

}

void
VirtualResourceDescriptor::SetAccelerationCapability (Ptr<AccelerationCapability> accelerationCapability)
{
  NS_LOG_FUNCTION (this->GetTypeId() << accelerationCapability->GetTypeId());
  m_accelerationCapability = accelerationCapability;
}

Ptr<AccelerationCapability>
VirtualResourceDescriptor::GetAccelerationCapability (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_accelerationCapability;
}

int
VirtualResourceDescriptor::Size (void)
{
  int sz = m_virtualCpu->Size() + m_virtualMemory->Size() + m_virtualStorage->Size() + m_accelerationCapability->Size();
  return sz;
}

} // namespace ns3
