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
#include "mec-entity-virtualizzation-infrastructure-manager.h"
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("VirtualizzationInfrastructureManager");

TypeId VirtualizzationInfrastructureManager::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::VirtualInfraManager")
    .SetParent<Object> ();
  return tid;
}

VirtualizzationInfrastructureManager::VirtualizzationInfrastructureManager ()
{
  m_linkedBaseStation = 0;
  m_virtualResIdCount = 0;
  NS_LOG_FUNCTION (this);
  LogResource();
}

VirtualizzationInfrastructureManager::VirtualizzationInfrastructureManager (Ptr <VirtualizzationInfrastructure> vi, Ptr<BaseStation> gnbId)
{
  NS_LOG_FUNCTION (this << vi << gnbId );
  m_memory.total=vi->GetTotalMemory()->GetVirtualMemSize();
  m_storage.total=vi->GetTotalStorage()->GetSizeOfStorage();
  m_accelerationCapabiliy.total=vi->GetTotalAccelerationCapability()->GetNumberOfAccelerationCapability();

  m_memory.available=m_memory.total;
  m_storage.available=m_storage.total;
  m_accelerationCapabiliy.available=m_accelerationCapabiliy.total;


  m_cpu.used=0;
  m_memory.used=0;
  m_storage.used=0;
  m_accelerationCapabiliy.used=0;
  m_virtualResIdCount = 0;
  m_linkedBaseStation=gnbId;
  Simulator::Schedule(Seconds(2), &VirtualizzationInfrastructureManager::LogResource, this);

}

VirtualizzationInfrastructureManager::~VirtualizzationInfrastructureManager()
{
  NS_LOG_FUNCTION (this);
}


Ptr<MecPlataformManager>
VirtualizzationInfrastructureManager::GetMepm (void)
{
  NS_LOG_FUNCTION (this);
  Ptr<MecHostEntity> host = DynamicCast<MecHostEntity>(GetNode());
  return host->GetObject<MecPlataformManager>();
}

Ptr<MultiaccessEdgeOrchestrator>
VirtualizzationInfrastructureManager::GetMeo (void)
{
  NS_LOG_FUNCTION(this);
  Ptr<MecHostEntity> host = DynamicCast<MecHostEntity>(GetNode());
  return host->GetMeo();
}

Ptr<VirtualizzationInfrastructure>
VirtualizzationInfrastructureManager::GetVi (void)
{
  NS_LOG_FUNCTION(this);
  Ptr<MecHostEntity> host = DynamicCast<MecHostEntity>(GetNode());
  return host->GetObject<VirtualizzationInfrastructure>();
}

void
VirtualizzationInfrastructureManager::SetLinkedBaseStation (Ptr<BaseStation> linkedBaseStation)
{
  NS_LOG_FUNCTION(this << linkedBaseStation);
  m_linkedBaseStation = linkedBaseStation;
}

Ptr<BaseStation>
VirtualizzationInfrastructureManager::GetLinkedBaseStation (void)
{
  NS_LOG_FUNCTION(this);
  return m_linkedBaseStation;
}

resource
VirtualizzationInfrastructureManager::GetCpu(void)
{
  NS_LOG_FUNCTION(this);
  return m_cpu;
}
resource
VirtualizzationInfrastructureManager::GetMemory(void)
{
  NS_LOG_FUNCTION(this);
  return m_memory;
}
resource
VirtualizzationInfrastructureManager::GetStorage(void)
{
  NS_LOG_FUNCTION(this);
  return m_storage;
}
resource
VirtualizzationInfrastructureManager::GetAccelerationCapabiliy(void)
{
  NS_LOG_FUNCTION(this);
  return m_accelerationCapabiliy;
}


int16_t
VirtualizzationInfrastructureManager::AddVirtualResourceInstance (uint64_t virResInstId, Ptr<VirtualResourceInstance> virtualResourceInstance)
{
  NS_LOG_FUNCTION (this << virResInstId << virtualResourceInstance);
  m_virtualResourceInstanceList.insert ( std::pair <uint64_t, Ptr<VirtualResourceInstance>> (virResInstId,virtualResourceInstance) );
  return 201;
}

int16_t
VirtualizzationInfrastructureManager::DeleteVirtualResourceInstance (uint64_t virResInstId)
{
  NS_LOG_FUNCTION (this << virResInstId);
  auto vri_it = m_virtualResourceInstanceList.find (virResInstId);
  if(vri_it != m_virtualResourceInstanceList.end ())
    {
      m_virtualResourceInstanceList.erase(vri_it);
      return 201;
    }
  else
    {
      NS_LOG_FUNCTION ("unknown virResInstId " << virResInstId);
      return 404;
    }
}

std::pair<int16_t, Ptr<VirtualResourceInstance>>
VirtualizzationInfrastructureManager::FindVirtualResourceInstance (uint64_t virResInstId)
{
  NS_LOG_FUNCTION (this << virResInstId);
  std::map<uint64_t, Ptr<VirtualResourceInstance>>::iterator vri_it = m_virtualResourceInstanceList.find (virResInstId);
   if(vri_it != m_virtualResourceInstanceList.end ())
     return ( std::make_pair(201, vri_it->second));

   else
     NS_LOG_FUNCTION ("unknown virResInstId " << virResInstId);
     return ( std::make_pair(404, vri_it->second));
}


int16_t
VirtualizzationInfrastructureManager::AllocateResource(uint64_t virResInstId)
{
  std::pair<int16_t, Ptr<VirtualResourceInstance>> allRes = FindVirtualResourceInstance(virResInstId);
  if (allRes.first==201)
    {
      allRes.second->SetAllocationType(2);
    }
  return UpdateResource();
}

int16_t
VirtualizzationInfrastructureManager::PreAllocateResource(uint64_t virResInstId)
{
  std::pair<int16_t, Ptr<VirtualResourceInstance>> allRes = FindVirtualResourceInstance(virResInstId);
  if (allRes.first==201)
    {
      allRes.second->SetAllocationType(1);
    }
  return UpdateResource();
}

int16_t
VirtualizzationInfrastructureManager::PreAllocateResource(Ptr<VirtualResourceInstance> virtualResourceInstance)
{
  virtualResourceInstance->SetAllocationType(1);
  AddVirtualResourceInstance(virtualResourceInstance->GetVirResInstId(), virtualResourceInstance);
  return UpdateResource();

}

void
VirtualizzationInfrastructureManager::DeAllocateResource(uint64_t virResInstId)
{
  DeleteVirtualResourceInstance (virResInstId);
  UpdateResource();

}

int16_t
VirtualizzationInfrastructureManager::UpdateResource (void)
{
  m_cpu.used=0;
  m_memory.used=0;
  m_storage.used=0;
  m_accelerationCapabiliy.used=0;

  std::map<uint64_t, Ptr<VirtualResourceInstance>>::iterator vri_it;
  for (vri_it=m_virtualResourceInstanceList.begin(); vri_it!=m_virtualResourceInstanceList.end(); vri_it++)
    {
      Ptr<VirtualResourceDescriptor> virtualResource = vri_it->second->GetVirtualResource();
      m_memory.used = m_memory.used + virtualResource->GetVirtualMemory()->GetVirtualMemSize();
      m_storage.used = m_storage.used + virtualResource->GetVirtualStorage()->GetSizeOfStorage();
      m_accelerationCapabiliy.used = m_accelerationCapabiliy.used + virtualResource->GetAccelerationCapability()->GetNumberOfAccelerationCapability();
    }
  m_memory.available = m_memory.total - m_memory.used;
  m_storage.available = m_storage.total - m_storage.used;

  m_cpu.used = GetVi()->GetCpuUsage();
  m_memory.used = m_memory.used/m_memory.total;
  m_storage.used = m_storage.used/m_storage.total;

//  GetLog()->HostResource(DynamicCast<MecHostEntity>(GetNode())->GetId(), m_cpu.used, m_memory.used, m_storage.used, GetVirtualInstanceN());
  if( m_cpu.used > 1 || m_memory.used > 1 || m_storage.used > 1 )
    {
      NS_LOG_ERROR (this << "exceeded the maximum number of resources");
      return 429;
    }
  else
    {
      return 201;
    }
}



void
VirtualizzationInfrastructureManager::ProcessPreAllocateVirtualizedResourceRequest(Ptr<AllocateVirtualizedResRequest> request, Ptr<AppContext> appContext)
{
  Ptr<VirtualResourceInstance> virtualResourceInstance =CreateObject<VirtualResourceInstance>();
  m_virtualResIdCount++;
  virtualResourceInstance->SetVirResInstId(m_virtualResIdCount);
  virtualResourceInstance->SetVirtualResource(request->GetVirtualResourceInstance()->GetVirtualResource());
  virtualResourceInstance->SetHostId(request->GetVirtualResourceInstance()->GetHostId());
  virtualResourceInstance->SetAllocationType(request->GetVirtualResourceInstance()->GetAllocationType());
  int16_t respCode = PreAllocateResource(virtualResourceInstance);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(VimId: " << this->GetId()
  << ")\t\t Process \t" << request->GetInstanceTypeId().GetName()
  << "(VirResInstId: " << virtualResourceInstance->GetVirResInstId()
  << ", AllocationType: PreAllocation"
  << ")");

  SendPreAllocateVirtualizedResourceResponse(virtualResourceInstance, respCode, appContext);
}

void
VirtualizzationInfrastructureManager::SendPreAllocateVirtualizedResourceResponse(Ptr<VirtualResourceInstance> virtualResourceInstance, int16_t respCode, Ptr<AppContext> appContext)
{
  Ptr<AllocateVirtualizedResResponse> response = CreateObject<AllocateVirtualizedResResponse> ();
  response->SetVirtualResourceInstance(virtualResourceInstance);
  response->SetRespCode(respCode);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(VimId: " << this->GetId()
  << ")\t\t Send \t\t" << response->GetInstanceTypeId().GetName()
  << "(VirResInstId: " << response->GetVirtualResourceInstance()->GetVirResInstId()
  << ", RespCode: " << respCode
  << ", CPU " << m_cpu.used
  << ", MEMORY " << m_memory.used
  << ", STORAGE " << m_storage.used
//  << ", ACCEL_CAPAB " << m_accelerationCapabiliy.used <<"/" << m_accelerationCapabiliy.reserved <<"/"<< m_accelerationCapabiliy.total
  << ")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MultiaccessEdgeOrchestrator::ProcessPreAllocateVirtualizedResourceResponse, GetMeo(), response, appContext);
  NS_LOG_INFO (GetMeo()<< response<< appContext);
}

void
VirtualizzationInfrastructureManager::ProcessAllocateVirtualizedResourceRequest(Ptr<AllocateVirtualizedResRequest> request)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(VimId: " << this->GetId()
  << ")\t\t Process \t" << request->GetInstanceTypeId().GetName()
  << "(VirResInstId: " << request->GetVirtualResourceInstance()->GetVirResInstId()
  << ", AllocationType: PreAllocation"
  << ")");

  int16_t respCode = AllocateResource(request->GetVirtualResourceInstance()->GetVirResInstId());
  SendAllocateVirtualizedResourceRequest(request->GetVirtualResourceInstance(), respCode);
  }

void
VirtualizzationInfrastructureManager::SendAllocateVirtualizedResourceRequest(Ptr<VirtualResourceInstance> virtualResourceInstance, int16_t respCode)
{
  Ptr<AllocateVirtualizedResResponse> response = CreateObject<AllocateVirtualizedResResponse> ();
  response->SetVirtualResourceInstance(virtualResourceInstance);
  response->SetRespCode(respCode);
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(VimId: " << this->GetId()
  << ")\t\t Send \t\t" << response->GetInstanceTypeId().GetName()
  << "(VirResInstId: " << response->GetVirtualResourceInstance()->GetVirResInstId()
  << ", RespCode: " << respCode
  << ", CPU " << m_cpu.used
  << ", MEMORY " << m_memory.used
  << ", STORAGE " << m_storage.used
//  << ", ACCEL_CAPAB " << m_accelerationCapabiliy.used <<"/" << m_accelerationCapabiliy.reserved <<"/"<< m_accelerationCapabiliy.total
  << ")");

  MsgList requestList;
  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataformManager::ProcessAllocateVirtualizedResourceResponse, GetMepm(), response, requestList);
}

void
VirtualizzationInfrastructureManager::ProcessTerminateVirtualResourceRequest(Ptr<TerminateVirtualResourceRequest> request)
{
  DeAllocateResource(request->GetVirResInstId());

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Vim: " << this->GetId()
  << std::string(")\t\t\t Process\t") << request->GetInstanceTypeId().GetName()
  << std::string("(VirResInstId: ") << request->GetVirResInstId()
  << ", CPU " << m_cpu.used
  << ", MEMORY " << m_memory.used
  << ", STORAGE " << m_storage.used
//  << ", ACCEL_CAPAB " << m_accelerationCapabiliy.used <<"/" << m_accelerationCapabiliy.reserved <<"/"<< m_accelerationCapabiliy.total
  << ")");

  SendTerminateVirtualResourceResponse(request->GetVirResInstId(), 204, "");
}

void
VirtualizzationInfrastructureManager::SendTerminateVirtualResourceResponse(uint64_t virtualResourceInstanceId, int16_t respCode, std::string problemDetails)
{
  Ptr<TerminateVirtualResourceResponse> response = CreateObject<TerminateVirtualResourceResponse> ();
  response->SetVirResInstId(virtualResourceInstanceId);
  response->SetRespCode(respCode);
  response->SetProblemDetails("");

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(Vim: " << this->GetId()
  << std::string(")\t\t\t Send\t\t") + response->GetInstanceTypeId().GetName()
  << std::string("(VirResInstId: ") << response->GetVirResInstId()
  << std::string(", RespCode: ") << response->GetRespCode()
  << ", ProblemDetails: " << response->GetProblemDetails()
  << ")");

  Time delay = GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &MecPlataformManager::ProcessTerminateVirtualResourceResponse, GetMepm(), response);
}

int16_t
VirtualizzationInfrastructureManager::GetVirtualInstanceN (void)
{
  NS_LOG_FUNCTION(this);
  int16_t n = m_virtualResourceInstanceList.size();
  return n;
}

void
VirtualizzationInfrastructureManager::LogResource(void)
{
  UpdateResource();
  GetLog()->HostResource(DynamicCast<MecHostEntity>(GetNode())->GetId(), m_cpu.used, m_memory.used, m_storage.used, GetVirtualInstanceN());
  Simulator::Schedule(Seconds(2), &VirtualizzationInfrastructureManager::LogResource, this);

}



}
