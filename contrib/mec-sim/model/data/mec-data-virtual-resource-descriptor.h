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

#ifndef MEC_VIRTUAL_RESOURCE_DESCRIPTOR_H
#define MEC_VIRTUAL_RESOURCE_DESCRIPTOR_H


#include <ns3/core-module.h>

#include "mec-data-virtual-cpu.h"
#include "mec-data-virtual-storage.h"
#include "mec-data-virtual-memory.h"
#include "mec-data-acceleration-capability.h"

namespace ns3 {

class VirtualResourceDescriptor : public Object
{
public:
  static TypeId GetTypeId (void);
  VirtualResourceDescriptor ();
  virtual ~VirtualResourceDescriptor ();

private:
  Ptr<VirtualCpu>             m_virtualCpu;
  Ptr<VirtualMemory>          m_virtualMemory;
  Ptr<VirtualStorage>         m_virtualStorage;
  Ptr<AccelerationCapability> m_accelerationCapability;

public:
  void SetVirtualCpu (Ptr<VirtualCpu> virtualCpu);
  Ptr<VirtualCpu> GetVirtualCpu (void);
  void SetVirtualMemory (Ptr<VirtualMemory> virtualMemory);
  Ptr<VirtualMemory> GetVirtualMemory (void);
  void SetVirtualStorage (Ptr<VirtualStorage> virtualStorage);
  Ptr<VirtualStorage> GetVirtualStorage (void);
  void SetAccelerationCapability (Ptr<AccelerationCapability> accelerationCapability);
  Ptr<AccelerationCapability> GetAccelerationCapability (void);
  int Size (void);
};


}

#endif /* MEC_VIRTUAL_RESOURCE_DESCRIPTOR_H */

