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

#ifndef MEC_ENTITY_VIRTUALIZZATION_INFRASTRUCTURE_H
#define MEC_ENTITY_VIRTUALIZZATION_INFRASTRUCTURE_H

#include <string.h>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-entity-virtualizzation-infrastructure-manager.h"
#include "mec-entity.h"


namespace ns3 {

class TaskOffloading;

class VirtualizzationInfrastructure : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  VirtualizzationInfrastructure (
          std::string cpuArchitecture,
					uint8_t numVirtualCpu,
					double cpuClock,
					double virtualMemSize,
					double sizeOfStorage,
					std::string accelerationCapabilityType);
  virtual ~VirtualizzationInfrastructure ();

  uint64_t GetViId (void);
  uint64_t GetHostId (void);

  class ActiveProcess : public Object
  {
  public:
    static TypeId GetTypeId (void);
    ActiveProcess ();
    virtual ~ActiveProcess ();

    double remainingIstructions;
    Ptr<TaskOffloading> task;
    EventId scheduledEnd;
    Time lastUpdate;
    double lastTaskDedicadedMips;
  };

  void SetTotalCpu (Ptr<VirtualCpu> totalCpu);
  Ptr<VirtualCpu> GetTotalCpu (void);
  void SetMispCpu (double mips);
  double GetMipsCpu (void);
  void SetTotalMemory (Ptr<VirtualMemory> totalMemory);
  Ptr<VirtualMemory> GetTotalMemory (void);
  void SetTotalStorage (Ptr<VirtualStorage> totalStorage);
  Ptr<VirtualStorage> GetTotalStorage (void);
  void SetTotalAccelerationCapability (Ptr<AccelerationCapability> totalAccelerationCapability);
  Ptr<AccelerationCapability> GetTotalAccelerationCapability (void);

  // CPU process scheduling
  typedef std::list<Ptr<ActiveProcess>>::const_iterator Iterator;

  void AddActiveProcess( Ptr<TaskOffloading> task);
  void DeleteActiveProcess( Ptr<TaskOffloading> task);
  void UpdateResourceScheduling(void);
  void UpdateCpuUsage(void);
  void RenewCpuUsage(void);
  double GetCpuUsage(void);

private:
  std::list<Ptr<ActiveProcess>> m_activeProcessList;
  int m_maxProcess;
  double m_mipsCpu;
  bool m_cpuState;

  double m_avgCpuUsage;
  double m_avgCpuUsageTemp;
  Time m_cpuWatchingTime;

  Ptr<VirtualCpu> m_totalCpu;
  Ptr<VirtualMemory> m_totalMemory;
  Ptr<VirtualStorage> m_totalStorage;
  Ptr<AccelerationCapability> m_totalAccelerationCapability;
};

}
#endif /* MEC_ENTITY_VIRTUALIZZATION_INFRASTRUCTURE_H */
