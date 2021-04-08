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

#include <ns3/simulator.h>
#include "mec-entity-virtualizzation-infrastructure.h"
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("VirtualizzationInfrastructure");

TypeId VirtualizzationInfrastructure::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::VirtualizzationInfrastructure")
    .SetParent<Object> ();
  return tid;
}

VirtualizzationInfrastructure::VirtualizzationInfrastructure (
							      std::string cpuArchitecture,
							      uint8_t numVirtualCpu,
							      double cpuClock,
							      double virtualMemSize,
							      double sizeOfStorage,
							      std::string accelerationCapabilityType)
{
  NS_LOG_FUNCTION (this << cpuArchitecture << numVirtualCpu << cpuClock << virtualMemSize << sizeOfStorage);
  m_totalCpu = CreateObject<VirtualCpu> (cpuArchitecture, numVirtualCpu, cpuClock);
  m_totalMemory = CreateObject<VirtualMemory>(virtualMemSize);
  m_totalStorage = CreateObject<VirtualStorage>(sizeOfStorage);
  m_totalAccelerationCapability = CreateObject<AccelerationCapability>(accelerationCapabilityType, 0);
  m_maxProcess = 10;
  m_mipsCpu = 0;
  m_cpuState = 0;
  m_avgCpuUsage = 0;
  m_avgCpuUsageTemp = 0;
  m_cpuWatchingTime = Now();
  RenewCpuUsage();
}

VirtualizzationInfrastructure::~VirtualizzationInfrastructure()
{
  NS_LOG_FUNCTION (this);
}


void
VirtualizzationInfrastructure::SetTotalCpu (Ptr<VirtualCpu> totalCpu)
{
  NS_LOG_FUNCTION(this << totalCpu);
  m_totalCpu = totalCpu;
}

Ptr<VirtualCpu>
VirtualizzationInfrastructure::GetTotalCpu (void)
{
  NS_LOG_FUNCTION(this);
  return m_totalCpu;
}

void
VirtualizzationInfrastructure::SetMispCpu (double mips)
{
  NS_LOG_FUNCTION(this << mips);
  m_mipsCpu = mips;
}

double
VirtualizzationInfrastructure::GetMipsCpu (void)
{
  NS_LOG_FUNCTION(this);
  return m_mipsCpu;
}

void
VirtualizzationInfrastructure::SetTotalMemory (Ptr<VirtualMemory> totalMemory)
{
  NS_LOG_FUNCTION(this << totalMemory);
  m_totalMemory = totalMemory;
}

Ptr<VirtualMemory>
VirtualizzationInfrastructure::GetTotalMemory (void)
{
  NS_LOG_FUNCTION(this);
  return m_totalMemory;
}

void
VirtualizzationInfrastructure::SetTotalStorage (Ptr<VirtualStorage> totalStorage)
{
  NS_LOG_FUNCTION(this << totalStorage);
  m_totalStorage = totalStorage;
}

Ptr<VirtualStorage>
VirtualizzationInfrastructure::GetTotalStorage (void)
{
  NS_LOG_FUNCTION(this);
  return m_totalStorage;
}


void
VirtualizzationInfrastructure::SetTotalAccelerationCapability (Ptr<AccelerationCapability> totalAccelerationCapability)
{
  NS_LOG_FUNCTION(this << totalAccelerationCapability);
  m_totalAccelerationCapability = totalAccelerationCapability;
}

Ptr<AccelerationCapability>
VirtualizzationInfrastructure::GetTotalAccelerationCapability (void)
{
  NS_LOG_FUNCTION(this);
  return m_totalAccelerationCapability;
}

void
VirtualizzationInfrastructure::AddActiveProcess( Ptr<TaskOffloading> task)
{
  NS_LOG_FUNCTION(this << task);
  Ptr<ActiveProcess> process = CreateObject<ActiveProcess>();
  process->task = task;
  process->remainingIstructions = task->GetIstructionNumber();
  process->lastUpdate = Now();
  process->lastTaskDedicadedMips = 0;

  m_activeProcessList.push_back(process);
  UpdateResourceScheduling();
}

void
VirtualizzationInfrastructure::DeleteActiveProcess( Ptr<TaskOffloading> task)
{
  NS_LOG_FUNCTION(this << task);

  for(Iterator it = m_activeProcessList.begin(); it != m_activeProcessList.end(); it++)
    {
      Ptr<ActiveProcess> process = *it;
      if(process->task == task)
        {
          task->GetMecApp()->SendTaskOffloadingResponse(task);
          m_activeProcessList.erase(it);
          break;
        }
    }
  UpdateResourceScheduling();
}

void
VirtualizzationInfrastructure::UpdateResourceScheduling(void)
{
  NS_LOG_FUNCTION(this);
  UpdateCpuUsage();
  m_cpuState = (m_activeProcessList.empty() == 0);
  int N_process = m_activeProcessList.size();
  double mipsForProcess = GetMipsCpu() / m_maxProcess;
  if(N_process < m_maxProcess)
    {
      mipsForProcess = GetMipsCpu() / N_process;
    }

  int i = 1;
  for(Iterator it = m_activeProcessList.begin(); it != m_activeProcessList.end(); it++)
    {
      Ptr<ActiveProcess> process = *it;
      // Update Remaining Instructions
      process->remainingIstructions = process->remainingIstructions - (Now() - process->lastUpdate).GetSeconds()*process->lastTaskDedicadedMips;
      // Update Process dedicated MIPS
      process->lastUpdate = Now();
      if(i<=m_maxProcess)
        {
        process->lastTaskDedicadedMips = mipsForProcess;
        // Compute remaining computation time and schedule the finish
        Time remainingProcessingTime = Seconds(process->remainingIstructions/process->lastTaskDedicadedMips);
        process->scheduledEnd.Cancel();
        process->scheduledEnd = Simulator::Schedule(remainingProcessingTime, &VirtualizzationInfrastructure::DeleteActiveProcess, this, process->task);
        }
      else
        {
        process->lastTaskDedicadedMips = 0;
        }
     i++;
    }
}
void
VirtualizzationInfrastructure::UpdateCpuUsage(void)
{
  NS_LOG_FUNCTION(this);
  double t = (Now()- m_cpuWatchingTime).GetSeconds();
  m_avgCpuUsageTemp = (m_avgCpuUsageTemp + m_cpuState*t);
  m_cpuWatchingTime = Now();
}

double
VirtualizzationInfrastructure::GetCpuUsage(void)
{
  NS_LOG_FUNCTION(this);
  return m_avgCpuUsage;
}

void
VirtualizzationInfrastructure::RenewCpuUsage(void)
{
  NS_LOG_FUNCTION(this);
  int refreshRate = 10; //seconds
  UpdateCpuUsage();
  m_avgCpuUsage = m_avgCpuUsageTemp/refreshRate;
  m_avgCpuUsageTemp = 0;
  m_cpuWatchingTime = Now();
  Simulator::Schedule(Seconds(refreshRate), &VirtualizzationInfrastructure::RenewCpuUsage, this);

}

TypeId VirtualizzationInfrastructure::ActiveProcess::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ActiveProcess")
    .SetParent<Object> ();
  return tid;
}


VirtualizzationInfrastructure::ActiveProcess::ActiveProcess()
{
  NS_LOG_FUNCTION (this);

}

VirtualizzationInfrastructure::ActiveProcess::~ActiveProcess()
{
  NS_LOG_FUNCTION (this);
}
}
