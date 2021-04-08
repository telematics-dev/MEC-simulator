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


#include "mec-entity-bs.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("BaseStation");

TypeId BaseStation::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::BaseStation")
    .SetParent<Object> ();
  return tid;
}

BaseStation::BaseStation ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
  m_hb=20;
  m_cf=1800;
  SetBandwidthUl(20);
  SetBandwidthDl(20);
  m_txPower=46;
  m_txAntennaGain=10;
}

BaseStation::~BaseStation ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

double
BaseStation::GetPosX()
{
  NS_LOG_FUNCTION (this);
  return m_posx;
}

double
BaseStation::GetPosY()
{
  NS_LOG_FUNCTION (this);
  return m_posy;
}

double
BaseStation::GetSizeCell()
{
  NS_LOG_FUNCTION (this);
  return m_sizecell;
}

Ptr<MobilityModel>
BaseStation::GetMob()
{
  NS_LOG_FUNCTION (this);
  if(m_mob == 0)
    {
      Ptr<MobilityModel> mm = this->GetNode()->GetObject<MobilityModel>();
      return mm;
    }
  else
    {
      return m_mob;
    }
}

void
BaseStation::SetMob(Ptr<MobilityModel> mob)
{
  NS_LOG_FUNCTION (this << mob);
  m_mob=mob;
}

int16_t
BaseStation::AddUe (uint64_t imsi ,Ptr<UserEquipment> ue)
{
  NS_LOG_FUNCTION (this << imsi << ue);
  m_ueList[imsi] = ue;
  return 201;
}

//Ptr<RadioNetworkInformationService>
//BaseStation::GetRnis (void)
//{
//  NS_LOG_FUNCTION (this);
//  return m_rnis;
//}
//void
//BaseStation::SetRnis (Ptr<RadioNetworkInformationService> rnis)
//{
//  NS_LOG_FUNCTION (this << rnis);
//  m_rnis=rnis;
//}

int16_t
BaseStation::DeleteUe (uint64_t imsi)
{
  NS_LOG_FUNCTION (this << imsi);
  m_ueList.erase( imsi);
  return 201;
}

std::pair<Ptr<UserEquipment>,int16_t>
BaseStation::FindUe (uint64_t m_imsi)
{
  NS_LOG_FUNCTION (this << m_imsi);
  Ptr<UserEquipment> error = 0;
  std::map<uint64_t, Ptr<UserEquipment>>::iterator it = m_ueList.find (m_imsi);
   if(it != m_ueList.end ())
     {
      return std::make_pair(it->second, 201);
     }
   else
     {
     NS_LOG_FUNCTION ("unknown imsi " << m_imsi);
     return std::make_pair(error, 404);
     }
}

std::map<uint64_t, Ptr<UserEquipment>>
BaseStation::GetUeList()
{
  NS_LOG_FUNCTION (this);
  return m_ueList;
}

void
BaseStation::SetUeList(std::map<uint64_t, Ptr<UserEquipment>> ueList)
{
  NS_LOG_FUNCTION (this);
  m_ueList=ueList;
}

void
BaseStation::AddLinkedHost (uint64_t hostId, double latency, Ptr<MecHostEntity> host)
{
  NS_LOG_FUNCTION (this << hostId << latency);
  LinkedHost linkedHost;
  linkedHost.hostId = hostId;
  linkedHost.host = host;
  linkedHost.latency = latency;
  m_linkedHostList.push_back(linkedHost);
}

BaseStation::LinkedHost
BaseStation::FindLinkedHost(uint64_t bsId)
{
  for (Iterator i = m_linkedHostList.begin (); i != m_linkedHostList.end (); i++)
    {
      if((*i).hostId == bsId)
        {
          return (*i);
        }
    }
  LinkedHost linkedHost;
  linkedHost.hostId = 0;
  linkedHost.host = 0;
  linkedHost.latency = 0;
  return linkedHost;
}

double
BaseStation::GetPosZ()
{
  NS_LOG_FUNCTION (this);
  return m_hb;
}


double
BaseStation::GetCf()
{
  NS_LOG_FUNCTION (this);
  return m_cf;
}

void
BaseStation::SetCf(double cf)
{
  NS_LOG_FUNCTION (this << cf);
  m_cf=cf;
}

double
BaseStation::GetBandwidthUl()
{
  NS_LOG_FUNCTION (this);
  return m_bandwidthUl;
}

void
BaseStation::SetBandwidthUl(double bandwidthUl)
{
  NS_LOG_FUNCTION (this << bandwidthUl);
  m_bandwidthUl=bandwidthUl;
}

double
BaseStation::GetBandwidthDl()
{
  NS_LOG_FUNCTION (this);
  return m_bandwidthDl;
}

void
BaseStation::SetBandwidthDl(double bandwidthDl)
{
  NS_LOG_FUNCTION (this << bandwidthDl);
  m_bandwidthDl=bandwidthDl;
}

double
BaseStation::GetTxPower()
{
  NS_LOG_FUNCTION (this);
  return m_txPower;
}

void
BaseStation::SetTxPower(double txPower)
{
  NS_LOG_FUNCTION (this << txPower);
  m_txPower=txPower;
}

double
BaseStation::GetTxAntennaGain()
{
  NS_LOG_FUNCTION (this);
  return m_txAntennaGain;
}

void
BaseStation::SetTxAntennaGain(double txAntennaGain)
{
  NS_LOG_FUNCTION (this << txAntennaGain);
  m_txAntennaGain=txAntennaGain;
}

void
BaseStation::ForwardRnisUpdate(Ptr<CellChangeNotification> notification)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(imsi: " << this->GetId()
  << std::string(")\t\t Send \t\t") <<  notification->GetInstanceTypeId().GetName()
  << "(Time: " << notification->GetTimeStamp()
  << ", srcBsId: " << notification->GetSrcBs()->GetId()
  << ", trgBsId: " << notification->GetTrgBs()->GetId()
  << ")"
  );

  for(Iterator it = m_linkedHostList.begin(); it!=m_linkedHostList.end(); it++)
    {
      Ptr<MecHostEntity> host = it->host;
      Ptr<RadioNetworkInformationService> rnis = host->GetObject<MecPlataform>()->GetObject<RadioNetworkInformationService>();
      if(rnis != 0)
        {
          Time delay = GetDelayModel()->GetControlPlaneDelay();
          Simulator::Schedule(delay, &RadioNetworkInformationService::CallBackRnisCellChange, rnis , notification);
        }
      else
        {
          NS_LOG_ERROR("RNIS not found");
        }
    }
}

void
BaseStation::ForwardTaskOffloadingRequest(Ptr<TaskOffloading> task)
{

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(id: " << this->GetId()
  << ")\t\t\t\t Forward \t\t" << task->GetInstanceTypeId().GetName()
  << "(Task size: "<< task->GetIstructionNumber() << " MI"
  << ")");
  uint64_t hostId = DynamicCast<MecHostEntity>(task->GetMecApp()->GetMecPlataform()->GetNode())->GetId();

  LinkedHost host = FindLinkedHost(hostId);
  Time delay;
  if (host.hostId != 0)
    {
      delay = GetDelayModel()->GetBackhaulDelay(host.latency);
      Simulator::Schedule(delay, &MecApp::ProcessTaskOffloadingRequest, task->GetMecApp(), task);
    }
  else
    {
      task->SetError(1);
      delay = GetDelayModel()->GetRadioDelay(GetAtiveFlow(task->GetMecApp()->GetAppD()->GetAppDId()), task->GetMecApp()->GetAppD()->GetAppDId());
      Simulator::Schedule(delay, &ClientApp::ProcessTaskOffloadingResponse, task->GetClientApp(), task);
    }
}

void
BaseStation::ForwardTaskOffloadingResponse(Ptr<TaskOffloading> task)
{
  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(id: " << this->GetId()
    << ")\t\t\t\t Forward \t\t" << task->GetInstanceTypeId().GetName()
    << "(Task size: "<< task->GetIstructionNumber() << " MI"
    << ")");

  Time delay = GetDelayModel()->GetRadioDelay(GetAtiveFlow(task->GetMecApp()->GetAppD()->GetAppDId()), task->GetMecApp()->GetAppD()->GetAppDId());
  Simulator::Schedule(delay, &ClientApp::ProcessTaskOffloadingResponse, task->GetClientApp(), task);
}

void
BaseStation::AddActiveFlow(int appDiD)
{
  m_activeFlow[appDiD] = m_activeFlow[appDiD]+1;
}
void
BaseStation::DeleteActiveFlow(int appDiD)
{
  m_activeFlow[appDiD]  = m_activeFlow[appDiD]-1;
}

int
BaseStation::GetAtiveFlow(int appDiD)
{
return m_activeFlow[appDiD];
}


} //namespace ns3

