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


#include "mec-data-virtual-memory.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("VirtualMemory");

TypeId VirtualMemory::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::VirtualMemory")
    .SetParent<Object> ();
  return tid;
}

VirtualMemory::VirtualMemory ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

VirtualMemory::VirtualMemory (double virtualMemSize)
{
  m_virtualMemSize = virtualMemSize;
  NS_LOG_FUNCTION (this->GetTypeId());
}

VirtualMemory::~VirtualMemory()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
VirtualMemory::SetVirtualMemSize (double virtualMemSize)
{
  NS_LOG_FUNCTION (this->GetTypeId() << virtualMemSize);
  m_virtualMemSize =virtualMemSize;
}

double
VirtualMemory::GetVirtualMemSize (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_virtualMemSize;
}

int
VirtualMemory::Size (void)
{
  int sz = sizeof(m_virtualMemSize);
  return sz;
}

} // namespace ns3
