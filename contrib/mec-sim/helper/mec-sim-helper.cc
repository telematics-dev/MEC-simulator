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

#include "mec-sim-helper.h"
#include "ns3/log.h"

NS_LOG_COMPONENT_DEFINE ("Helper");

namespace ns3 {

MecSimHelper::MecSimHelper (double ue)
  {
   m_nUE = ue;
   m_cellIdCounter = 0;
   m_imsiCounter= 2221034000000000;
   m_mecEntityCounter= 0;
   m_mecHostCounter= 0;
   m_hostIntraCellDelay = 0.001;
   m_hostInterCellDelay = 0.005;
   m_log = CreateObject<LoggingToFile>(m_nUE);
   m_cpuMips = 50000;
   m_virtualMemSize = 8*1024;
   m_sizeOfStorage = 0.5*1024*1024;
  }

MecSimHelper::~MecSimHelper (void)
  {
  m_log->~Object();

  }

void
MecSimHelper::EnableAppLogComponents (void)
{
  LogComponentEnableAll (LOG_PREFIX_TIME);
  LogComponentEnable ("MecDelayModel", LOG_LEVEL_INFO);
//  LogComponentEnable ("MultiaccessEdgeOrchestrator", LOG_LEVEL_INFO);
  LogComponentEnable ("UserEquipment", LOG_LEVEL_INFO);
//  LogComponentEnable ("ClientApp", LOG_LEVEL_DEBUG);
//  LogComponentEnable ("UserApplicationLcmProxy", LOG_LEVEL_INFO);
  LogComponentEnable ("Helper", LOG_LEVEL_INFO);
//  LogComponentEnable("LoadGenerator", LOG_LEVEL_FUNCTION);
//  LogComponentEnable ("MecPlataformManager", LOG_LEVEL_INFO);
//  LogComponentEnable ("VirtualizzationInfrastructureManager", LOG_LEVEL_INFO);
//  LogComponentEnable ("AppRepository", LOG_LEVEL_INFO);
//  LogComponentEnable ("MecApp", LOG_LEVEL_INFO);
//  LogComponentEnable ("MecPlataform", LOG_LEVEL_INFO);
//  LogComponentEnable ("ApplicationMobilityService", LOG_LEVEL_INFO);
//  LogComponentEnable ("RadioNetworkInformationService", LOG_LEVEL_INFO);
//  LogComponentEnable ("BaseStation", LOG_LEVEL_INFO);
}

void
MecSimHelper::EnableAppLogComponentsDebug (void)
{
  LogComponentEnableAll (LOG_PREFIX_TIME);
  LogComponentEnable ("OperationsSupportSystem", LOG_LEVEL_ALL);
  LogComponentEnable ("MultiaccessEdgeOrchestrator", LOG_LEVEL_ALL);
  LogComponentEnable ("UserEquipment", LOG_LEVEL_ALL);
  LogComponentEnable ("UserApplicationLcmProxy", LOG_LEVEL_ALL);
  LogComponentEnable ("Helper", LOG_LEVEL_ALL);
  LogComponentEnable("LoadGenerator", LOG_LEVEL_ALL);
  LogComponentEnable ("MecPlataformManager", LOG_LEVEL_ALL);
  LogComponentEnable ("VirtualizzationInfrastructureManager", LOG_LEVEL_ALL);
  LogComponentEnable ("AppRepository", LOG_LEVEL_ALL);
  LogComponentEnable ("MecApp", LOG_LEVEL_ALL);
  LogComponentEnable ("MecPlataform", LOG_LEVEL_ALL);
  LogComponentEnable ("ApplicationMobilityService", LOG_LEVEL_ALL);
  LogComponentEnable ("RadioNetworkInformationService", LOG_LEVEL_ALL);
  LogComponentEnable ("BaseStation", LOG_LEVEL_ALL);
  LogComponentEnable ("Pointer", LOG_LEVEL_ALL);
  LogComponentEnable ("ClientApp", LOG_LEVEL_ALL);

}

Ptr<MecDelayModel>
MecSimHelper::DelayModel()
{

      delay = CreateObject<MecDelayModel> ();

//      NS_LOG_INFO ("\t- DelayModel\t\t\tCreated");
  return delay;
}

Ptr<MecEntity>
MecSimHelper::InstallSingleBsEntity (Ptr<Node> node)
{
  Ptr<BaseStation> bs = CreateObject<BaseStation> ();
  bs->SetNode(node);
  node->AggregateObject(bs);
  bs->SetId(GetCellId());

  Vector pos = bs->GetMob()->GetPosition();
  pos.z = 150;
  bs->GetMob()->SetPosition(pos);

  NS_LOG_INFO("\t- BaseStation\t\t\tAdded\t\tbsId: " << bs->GetId()
              << " \tPosition: x = "
              << bs->GetMob()->GetPosition().x << ",y = "
              << bs->GetMob()->GetPosition().y << ",z = "
              << bs->GetMob()->GetPosition().z
              );
  return bs;
}

Ptr<MecHostContainer>
MecSimHelper::InstallMecHostsOneCell(Ptr<MecEntityContainer> bs, Ptr<Node> sys)
{
NS_LOG_FUNCTION (this);

hosts = CreateObject<MecHostContainer>();
for (MecEntityContainer::Iterator i = bs->Begin (); i != bs->End (); ++i)
  {
    Ptr<MecEntityContainer> linkedBs = CreateObject<MecEntityContainer>(*i);
    Ptr<MecHostEntity> host = InstallSingleMecHost (linkedBs, sys->GetObject<MultiaccessEdgeOrchestrator>(), bs);
    hosts->Add(host);
  }
sys->AggregateObject(hosts);

return hosts;
}

Ptr<MecHostContainer>
MecSimHelper::InstallMecHostsFourCell(Ptr<MecEntityContainer> bs, Ptr<Node> sys)
{
NS_LOG_FUNCTION (this);

hosts = CreateObject<MecHostContainer>();
for (MecEntityContainer::Iterator i = bs->Begin (); i != bs->End (); ++i)
  {
    Ptr<MecEntityContainer> linkedBs1 = CreateObject<MecEntityContainer>(*i);
    ++i;
    linkedBs1->Add(*i);
    ++i;
    Ptr<MecEntityContainer> linkedBs2 = CreateObject<MecEntityContainer>(*i);
    ++i;
    linkedBs2->Add(*i);
    ++i;
    linkedBs1->Add(*i);
    ++i;
    linkedBs1->Add(*i);
    ++i;
    linkedBs2->Add(*i);
    ++i;
    linkedBs2->Add(*i);
    Ptr<MecHostEntity> host = InstallSingleMecHost (linkedBs1, sys->GetObject<MultiaccessEdgeOrchestrator>(), bs);
    hosts->Add(host);
    host = InstallSingleMecHost (linkedBs2, sys->GetObject<MultiaccessEdgeOrchestrator>(), bs);
    hosts->Add(host);
  }
sys->AggregateObject(hosts);

return hosts;
}

Ptr<MecHostEntity>
MecSimHelper::InstallSingleMecHost(Ptr<MecEntityContainer> bs, Ptr<MultiaccessEdgeOrchestrator> meo, Ptr<MecEntityContainer> bsContainer)
{
  std::string cpuArchitecture = "64bit";
  uint8_t numVirtualCpu = 20;
  double cpuClock = 3.0;
  double virtualMemSize = m_virtualMemSize;
  double sizeOfStorage = m_sizeOfStorage;
  std::string accelerationCapabilityType = "GPU";
  int accelerationCapabilityNumber = 3;
  Ptr<MecHostEntity> host = CreateObject<MecHostEntity>();
  host->SetId(GetMecHostId());
  host->SetMeo(meo);
  host->AggregateObject( DelayModel());
  uint64_t hostEntityId = host->GetId();

  for (MecEntityContainer::Iterator i = bsContainer->Begin (); i != bsContainer->End (); ++i)
    {
      double latency;
      if(bs->IsInContainer(*i))
        {
          latency = m_hostIntraCellDelay;
        }
      else
        {
          latency = m_hostInterCellDelay;
        }
      Ptr<BaseStation> BS = DynamicCast<BaseStation>(*i);
      host->AddLinkedBs(BS->GetId(), latency, BS);
      BS->AddLinkedHost(host->GetId(), latency, host);
    }
  Ptr<BaseStation> intracellBs = DynamicCast<BaseStation>(bs);

  Ptr<VirtualizzationInfrastructure> vi = CreateObject<VirtualizzationInfrastructure> (cpuArchitecture, numVirtualCpu, cpuClock, virtualMemSize, sizeOfStorage, accelerationCapabilityType);
  vi->GetTotalAccelerationCapability()->SetNumberOfAccelerationCapability(accelerationCapabilityNumber);
  hostEntityId++;
  vi->SetId(hostEntityId);
  vi->SetMispCpu(m_cpuMips);
  host->AggregateObject(vi);
  vi->SetNode(host);

  Ptr<VirtualizzationInfrastructureManager> vim = CreateObject<VirtualizzationInfrastructureManager> (vi, intracellBs);
  hostEntityId++;
  vim->SetId(hostEntityId);
  host->AggregateObject(vim);
  vim->SetNode(host);
  vim->SetLog(m_log);

  Ptr<MecPlataformManager> mepm = CreateObject<MecPlataformManager> ();
  hostEntityId++;
  mepm->SetId(hostEntityId);
  host->AggregateObject(mepm);
  mepm->SetNode(host);

  Ptr<MecPlataform> mep = CreateObject<MecPlataform> ();
  hostEntityId++;
  mep->SetId(hostEntityId);
  host->AggregateObject(mep);
  mep->SetNode(host);
  Ptr<ApplicationMobilityService> ams = CreateObject<ApplicationMobilityService> ();
  hostEntityId++;
  ams->SetId(hostEntityId);
  ams->SetNode(mep);
  host->AggregateObject(ams);
  Ptr<RadioNetworkInformationService> rnis = CreateObject<RadioNetworkInformationService> ();
  hostEntityId++;
  rnis->SetId(hostEntityId);
  rnis->SetNode(mep);
  mep->AggregateObject(rnis);


  Ptr<MecAppContainer> mecApps = CreateObject<MecAppContainer> ();
  host->AggregateObject(mecApps);
  mecApps->SetNode(host);

  NS_LOG_INFO("\t- MecHost\t\t\tAdded\t\thostId: " << host->GetId()
        << "\tCPU (" << m_cpuMips << " MIps) "
        << " MEMORY (" << virtualMemSize/1024 << " GB)"
        << " STORAGE (" << sizeOfStorage/1024 << " GB)");

  return host;

}


void
MecSimHelper::InstallMecSystem(Ptr<Node> n)
{
  NS_LOG_INFO ("MEC SYSTEM CREATION");
  appRep = CreateObject<AppRepository> ();
  appRep->CreateList ();
  n->AggregateObject( appRep );
  n->AggregateObject( DelayModel());

  ualcmp = CreateObject<UserApplicationLcmProxy> ();
  n->AggregateObject(ualcmp);
  ualcmp->SetNode(n);
  ualcmp->SetId(GetMecEntityId());
  NS_LOG_INFO ("\t- UserApplicationLcmProxy\tCreated\t\tualcmpID: "
      << ualcmp->GetId());

  oss = CreateObject<OperationsSupportSystem> ();
  n->AggregateObject(oss);
  oss->SetNode(n);
  oss->SetId(GetMecEntityId());
  NS_LOG_INFO ("\t- OperationsSupportSystem\tCreated\t\tossID: "
      << oss->GetId());

  meo = CreateObject<MultiaccessEdgeOrchestrator> ();
  n->AggregateObject(meo);
  meo->SetNode(n);
  meo->SetId(GetMecEntityId());
  NS_LOG_INFO ("\t- MultiaccessEdgeOrchestrator\tCreated\t\tmeoID: "
      << meo->GetId());
}

Ptr<MecEntity>
MecSimHelper::InstallSingleUeEntity(Ptr<Node> node, Ptr<MecEntityContainer> enbDevices, int appdId, double interarrivalTime, double serviceTime)
{
  Ptr<UserEquipment> ue = CreateObject<UserEquipment> ();
  ue->SetLog(m_log);
  node->AggregateObject(ue);
  ue->SetNode(node);
  ue->SetId(GetMecImsi());
  Ptr<ThreeGppRmaPropagationLossModel> lossModel = CreateObject<ThreeGppRmaPropagationLossModel> ();
  ue->SetPropagationLossModel(lossModel);
  ue->SetUalcmp(ualcmp);
  ue->SetBsList(enbDevices);

  std::ostringstream oss;
  oss <<"/NodeList/"
      <<node->GetId()
      <<"/$ns3::MobilityModel/CourseChange";
  Config::ConnectWithoutContext(oss.str(), MakeCallback(&UserEquipment::CourseChange, ue));

  Ptr<LoadGenerator> loadGenerator = CreateObject<LoadGenerator>();
  node->AggregateObject(loadGenerator);
  loadGenerator->SetNode(node);
  loadGenerator->SetLambda(interarrivalTime);
  loadGenerator->SetMu(serviceTime);
  loadGenerator->SetAppdId(appdId);
  loadGenerator->Inizialize();

  NS_LOG_INFO ("\t- UserEquipment\t\t\tAdded\t\timsi: "
      << ue->GetId());
  return ue;
}

Ptr<MecEntityContainer>
MecSimHelper::InstallUeEntity(NodeContainer c, Ptr<MecEntityContainer> enbDevices, int appdId, double interarrivalTime, double serviceTime)
{
  NS_LOG_FUNCTION (this);
  Ptr<MecEntityContainer> mecEntities = CreateObject<MecEntityContainer>();
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      Ptr<Node> node = *i;
      node->AggregateObject(DelayModel());
      Ptr<MecEntity> mecEntity = InstallSingleUeEntity (node, enbDevices, appdId, interarrivalTime, serviceTime);
      mecEntities->Add(mecEntity);
    }
  return mecEntities;
}

Ptr<MecEntityContainer>
MecSimHelper::InstallBsEntity(NodeContainer c)
{
  NS_LOG_FUNCTION (this);
  Ptr<MecEntityContainer> mecEntities = CreateObject<MecEntityContainer>();
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      Ptr<Node> node = *i;
      node->AggregateObject(DelayModel());
      Ptr<MecEntity> mecEntity = InstallSingleBsEntity (node);
      mecEntities->Add(mecEntity);
    }
  return mecEntities;
}

Ptr<AppRepository>
MecSimHelper::GetAppRep(void)
{
  return appRep;
}

uint64_t
MecSimHelper::GetMecEntityId(void)
{
  m_mecEntityCounter++;
  return m_mecEntityCounter;
}

uint64_t
MecSimHelper::GetMecHostId(void)
{
  m_mecHostCounter = m_mecHostCounter+100000;
  return m_mecHostCounter;
}

uint64_t
MecSimHelper::GetMecImsi(void)
{
  m_imsiCounter++;
  return m_imsiCounter;
}

uint64_t
MecSimHelper::GetCellId(void)
{
  m_cellIdCounter++;
  return m_cellIdCounter;
}


void
MecSimHelper::Attach (Ptr<MecEntity> ueDevice, Ptr<MecEntity> bsDevice)
{
  NS_LOG_FUNCTION (this << ueDevice << bsDevice);

  Ptr<UserEquipment> ue = DynamicCast<UserEquipment>(ueDevice);
  Ptr<BaseStation> bs = DynamicCast<BaseStation>(bsDevice);

  ue->SetTargetBs(bs);
  bs->AddUe(ue->GetId(), ue);
}

void
MecSimHelper::Attach (Ptr<MecEntityContainer> ueDevices, Ptr<MecEntity> enbDevice)
{
  NS_LOG_FUNCTION (this);
  for (MecEntityContainer::Iterator i = ueDevices->Begin (); i != ueDevices->End (); ++i)
    {
      Attach (*i, enbDevice);
    }
}

void
MecSimHelper::AttachToClosestEnb (Ptr<MecEntityContainer> ueDevices, Ptr<MecEntityContainer> enbDevices)
{
  NS_LOG_FUNCTION (this);
  for (MecEntityContainer::Iterator i = ueDevices->Begin (); i != ueDevices->End (); ++i)
    {
      AttachToClosestEnb (*i, enbDevices);
    }
}

void
MecSimHelper::AttachToClosestEnb (Ptr<MecEntity> ueDevice, Ptr<MecEntityContainer> enbDevices)
{
  NS_LOG_FUNCTION (this);
  NS_ASSERT_MSG (enbDevices->GetN () > 0, "empty enb device container");
  Vector uepos = ueDevice->GetNode ()->GetObject<MobilityModel> ()->GetPosition ();
  double minDistance = std::numeric_limits<double>::infinity ();
  Ptr<MecEntity> closestEnbDevice;
  for (MecEntityContainer::Iterator i = enbDevices->Begin (); i != enbDevices->End (); ++i)
    {
      Vector enbpos = (*i)->GetNode ()->GetObject<MobilityModel> ()->GetPosition ();
      double distance = CalculateDistance (uepos, enbpos);
      if (distance < minDistance)
        {
          minDistance = distance;
          closestEnbDevice = *i;
        }
    }
  NS_ASSERT (closestEnbDevice != 0);
  Attach (ueDevice, closestEnbDevice);
}

void
MecSimHelper::SetHostIntracellDelay(double delay)
{
  m_hostIntraCellDelay = delay;
}

void
MecSimHelper::SetHostIntercellDelay(double delay)
{
  m_hostInterCellDelay = delay;
}

void
MecSimHelper::SetCpuMips(double value)
{
  m_cpuMips=value;
}
void
MecSimHelper::SetVirtualMemSize(double value)
{
  m_virtualMemSize=value;

}
void
MecSimHelper::SetSizeOfStorage(double value)
{
  m_sizeOfStorage=value;

}
} //namespace ns3

