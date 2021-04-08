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

#ifndef MEC_SIM_HELPER_H
#define MEC_SIM_HELPER_H

#include <ns3/mec-sim-helper.h>
#include <ns3/core-module.h>
#include "ns3/mobility-module.h"
#include "ns3/config-store.h"
#include <ns3/buildings-helper.h>

#include <string>
#include <ns3/core-module.h>
#include "ns3/ptr.h"
#include "ns3/mec-delay-model.h"
#include "ns3/simulator.h"
#include "ns3/packet.h"
#include "ns3/pointer.h"
#include <string>
#include "ns3/config.h"
#include "ns3/mec-entity-meo.h"
#include "ns3/mec-entity-oss.h"
#include "ns3/mec-entity-mec-plataform.h"
#include "ns3/mec-entity-host.h"
#include "ns3/mec-host-container.h"
#include "ns3/mec-entity-container.h"
#include "ns3/mec-app-container.h"
#include <ns3/load-generator.h>
#include <ns3/three-gpp-propagation-loss-model.h>
#include "ns3/traced-callback.h"
#include "ns3/logging-to-file.h"

//#include

namespace ns3 {

class OperationsSupportSystem;
class MultiaccessEdgeOrchestrator;
class ApplicationMobilityService;
class RadioNetworkInformationService;


class MecSimHelper
{
public:
  MecSimHelper (double ue);
  ~MecSimHelper (void);


  void InstallMecSystem(Ptr<Node> n);
  Ptr<MecHostContainer> InstallMecHostsOneCell(Ptr<MecEntityContainer> bs, Ptr<Node> sys);
  Ptr<MecHostContainer> InstallMecHostsFourCell(Ptr<MecEntityContainer> bs, Ptr<Node> sys);
  Ptr<MecEntityContainer> InstallUeEntity(NodeContainer c, Ptr<MecEntityContainer> enbDevices, int appdId, double interarrivalTime, double serviceTime);
  Ptr<MecEntityContainer> InstallBsEntity(NodeContainer c);
  void EnableAppLogComponents (void);
  void EnableAppLogComponentsDebug (void);
  Ptr<MecDelayModel> DelayModel (void);
  Ptr<AppRepository> GetAppRep(void);
  void Attach (Ptr<MecEntity> ueDevice, Ptr<MecEntity> bsDevice);
  void Attach (Ptr<MecEntityContainer> ueDevices, Ptr<MecEntity> enbDevice);
  void AttachToClosestEnb (Ptr<MecEntityContainer> ueDevices, Ptr<MecEntityContainer> enbDevices);
  void AttachToClosestEnb (Ptr<MecEntity> ueDevice, Ptr<MecEntityContainer> enbDevices);
  void SetHostIntracellDelay(double delay);
  void SetHostIntercellDelay(double delay);
  void SetCpuMips(double value);
  void SetVirtualMemSize(double value);
  void SetSizeOfStorage(double value);
  void SetNue(double ue);

private:
  Ptr<MecHostEntity> InstallSingleMecHost(Ptr<MecEntityContainer> bs, Ptr<MultiaccessEdgeOrchestrator> meo, Ptr<MecEntityContainer> bsContainer);
  Ptr<MecEntity> InstallSingleUeEntity (Ptr<Node> node, Ptr<MecEntityContainer> enbDevices, int appdId, double interarrivalTime, double serviceTime);
  Ptr<MecEntity> InstallSingleBsEntity (Ptr<Node> node);
  Ptr<MecDelayModel> delay;
  Ptr<UserApplicationLcmProxy> ualcmp;
  Ptr<OperationsSupportSystem> oss;
  Ptr<MultiaccessEdgeOrchestrator> meo;
  Ptr<AppRepository> appRep;
  Ptr<MecHostContainer> hosts;
  Ptr<LoggingToFile> m_log;
  double m_hostIntraCellDelay;
  double m_hostInterCellDelay;
  uint64_t m_cellIdCounter;
  uint64_t m_imsiCounter;
  uint64_t m_mecEntityCounter;
  uint64_t m_mecHostCounter;
  uint64_t GetMecEntityId(void);
  uint64_t GetMecHostId(void);
  uint64_t GetMecImsi(void);
  uint64_t GetCellId(void);
  double m_cpuMips;
  double m_virtualMemSize;
  double m_sizeOfStorage;
  double m_nUE;


};

} //namespace ns3

#endif /* MEC_SIM_HELPER_H */

