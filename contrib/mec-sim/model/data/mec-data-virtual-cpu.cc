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


#include "mec-data-virtual-cpu.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("VirtualCpu");

TypeId VirtualCpu::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::VirtualCpu")
    .SetParent<Object> ();
  return tid;
}

VirtualCpu::VirtualCpu ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
  m_cpuArchitecture = "64bit";
  m_numVirtualCpu = 0;
  m_cpuClock = 0;
}

VirtualCpu::VirtualCpu (std::string cpuArchitecture,
			uint8_t numVirtualCpu,
			double cpuClock)
{
  m_cpuArchitecture = cpuArchitecture;
  m_numVirtualCpu = numVirtualCpu;
  m_cpuClock = cpuClock;
  NS_LOG_FUNCTION (this->GetTypeId());
}

VirtualCpu::~VirtualCpu()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
VirtualCpu::SetCpuArchitecture (std::string cpuArchitecture)
{
  NS_LOG_FUNCTION (this->GetTypeId() << cpuArchitecture);
  m_cpuArchitecture = cpuArchitecture;
}

std::string
VirtualCpu::GetCpuArchitecture (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_cpuArchitecture;
}

void
VirtualCpu::SetNumVirtualCpu (uint8_t numVirtualCpu)
{
  NS_LOG_FUNCTION (this->GetTypeId() << numVirtualCpu);
  m_numVirtualCpu = numVirtualCpu;
}

uint8_t
VirtualCpu::GetNumVirtualCpu (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_numVirtualCpu;
}

void
VirtualCpu::SetCpuClock (double cpuClock)
{
  NS_LOG_FUNCTION (this->GetTypeId() << cpuClock);
  m_cpuClock = cpuClock;
}

double
VirtualCpu::GetCpuClock (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_cpuClock;
}

int
VirtualCpu::Size (void)
{
  int sz = sizeof(m_cpuClock) + sizeof(m_numVirtualCpu) + m_cpuArchitecture.length();
  return sz;
}
} // namespace ns3
