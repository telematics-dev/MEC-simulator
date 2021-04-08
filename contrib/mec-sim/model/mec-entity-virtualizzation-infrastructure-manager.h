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

#ifndef MEC_ENTITY_VIRTUALIZZATION_INFRASTRUCTURE_MANAGER_H
#define MEC_ENTITY_VIRTUALIZZATION_INFRASTRUCTURE_MANAGER_H

#include <string>
#include <map>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-entity-meo.h"
#include "mec-entity-meo.h"
#include "mec-entity-virtualizzation-infrastructure.h"
#include "mec-entity-bs.h"
#include "mec-entity.h"


namespace ns3 {

struct resource {
  double used = 0;
  double available = 0;
  double total = 0;
};


class MultiaccessEdgeOrchestrator;
class VirtualizzationInfrastructure;
class MecPlataformManager;
class BaseStation;
class TerminateVirtualResourceRequest;
class MobilityProcedureNotification;
class AllocateVirtualizedResRequest;




class VirtualizzationInfrastructureManager : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  VirtualizzationInfrastructureManager (Ptr <VirtualizzationInfrastructure> vi, Ptr<BaseStation> bsId);
  VirtualizzationInfrastructureManager ();
  virtual ~VirtualizzationInfrastructureManager ();

  Ptr<MultiaccessEdgeOrchestrator> GetMeo (void);
  Ptr<VirtualizzationInfrastructure> GetVi (void);
  Ptr<MecPlataformManager> GetMepm (void);
  void SetLinkedBaseStation (Ptr<BaseStation> linkedBaseStation);
  Ptr<BaseStation> GetLinkedBaseStation (void);

  resource GetCpu(void);
  resource GetMemory(void);
  resource GetStorage(void);
  resource GetAccelerationCapabiliy(void);

  int16_t AddVirtualResourceInstance(uint64_t virResInstId, Ptr<VirtualResourceInstance> virtualResourceInstance);
  int16_t DeleteVirtualResourceInstance (uint64_t virResInstId);
  std::pair<int16_t, Ptr<VirtualResourceInstance>>  FindVirtualResourceInstance (uint64_t virResInstId);
  int16_t GetVirtualInstanceN (void);

  int16_t PreAllocateResource(Ptr<VirtualResourceInstance> virtualResourceInstance);
  int16_t PreAllocateResource(uint64_t virResInstId);
  int16_t AllocateResource(uint64_t virResInstId);
  void DeAllocateResource(uint64_t virResInstId);
  int16_t UpdateResource (void);
  void LogResource(void);

  void ProcessPreAllocateVirtualizedResourceRequest(Ptr<AllocateVirtualizedResRequest> request, Ptr<AppContext> appContext);
  void SendPreAllocateVirtualizedResourceResponse(Ptr<VirtualResourceInstance> virtualResourceInstance, int16_t respCode, Ptr<AppContext> appContext);
  void ProcessAllocateVirtualizedResourceRequest(Ptr<AllocateVirtualizedResRequest> request);
  void SendAllocateVirtualizedResourceRequest(Ptr<VirtualResourceInstance> virtualResourceInstance, int16_t respCode);
  void ProcessTerminateVirtualResourceRequest(Ptr<TerminateVirtualResourceRequest> request);
  void SendTerminateVirtualResourceResponse(uint64_t virtualResourceInstanceId, int16_t respCode, std::string problemDetails);

private:
  resource m_cpu;
  resource m_memory;
  resource m_storage;
  resource m_accelerationCapabiliy;
  uint64_t m_virtualResIdCount;
  std::map<uint64_t, Ptr<VirtualResourceInstance>> m_virtualResourceInstanceList;
  Ptr<BaseStation> m_linkedBaseStation;
};
}
#endif /* MEC_ENTITY_VIRTUALIZZATION_INFRASTRUCTURE_MANAGER_H */
