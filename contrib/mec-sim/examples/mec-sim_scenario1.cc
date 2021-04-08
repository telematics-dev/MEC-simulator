/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <ns3/core-module.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include <ns3/mec-entity-meo.h>
#include <ns3/mec-entity-oss.h>
#include <ns3/simulator.h>
#include <list>
#include <ns3/mec-sim-helper.h>
#include <ns3/app-repository.h>
#include <ns3/mec-entity-ue.h>
#include <ns3/mec-entity-container.h>
#include <ns3/mec-host-container.h>
#include <ns3/load-generator.h>

using namespace ns3;

int 
main (int argc, char *argv[])
{

  double nUE = 10;
  CommandLine cmd;
  cmd.AddValue("nUE", "Number of packets to echo", nUE);
  cmd.Parse (argc, argv);

  MecSimHelper h = MecSimHelper(nUE);

  h.EnableAppLogComponents();
//  h.EnableAppLogComponentsDebug();

// Create MEC System
  Ptr<Node> sys = CreateObject<Node>();
  h.InstallMecSystem (sys);

// Create BSs
  NodeContainer bs;
  bs.Create(16);
  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (100),
                                 "MinY", DoubleValue (100),
                                 "DeltaX", DoubleValue (200),
                                 "DeltaY", DoubleValue (200),
                                 "GridWidth", UintegerValue (4),
                                 "LayoutType", StringValue ("RowFirst"));
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (bs);
  Ptr<MecEntityContainer> bsContainer = h.InstallBsEntity(bs);

// Create MEC Hosts
  h.SetHostIntracellDelay(0.00);
  h.SetHostIntercellDelay(0.001);
  h.SetCpuMips(300000);
  h.SetVirtualMemSize(16*1024);
  h.SetSizeOfStorage(240*1024);
  Ptr<MecHostContainer> hostContainer = h.InstallMecHostsOneCell(bsContainer, sys);

// Create UEs
  NodeContainer ue1;
  NodeContainer ue2;
  NodeContainer ue3;
  NodeContainer ue4;

  ue1.Create(round(nUE/100*12));
  ue2.Create(round(nUE/100*6));
  ue3.Create(round(nUE/100*6));
  ue4.Create(round(nUE/100*76));
  mobility.SetPositionAllocator ("ns3::RandomBoxPositionAllocator",
                                 "X", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=800.0]"),
                                 "Y", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=800.0]"),
                                 "Z", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=10.0]"));
  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Mode", StringValue ("Time"),
                             "Time", StringValue ("2s"),
                             "Speed", StringValue ("ns3::ConstantRandomVariable[Constant=8.33]"),
                             "Bounds", StringValue ("0|800|0|800"));
  mobility.Install (ue1);

  mobility.SetPositionAllocator ("ns3::RandomBoxPositionAllocator",
                                 "X", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=800.0]"),
                                 "Y", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=800.0]"),
                                 "Z", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=10.0]"));

  RandomBoxPositionAllocator posAllocator;
  Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
  x->SetAttribute ("Min", DoubleValue (0));
  x->SetAttribute ("Max", DoubleValue (800));
  Ptr<UniformRandomVariable> z = CreateObject<UniformRandomVariable> ();
  z->SetAttribute ("Min", DoubleValue (0));
  z->SetAttribute ("Max", DoubleValue (10));
  posAllocator.SetX(x);
  posAllocator.SetY(x);
  posAllocator.SetZ(z);


  mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel",
                             "Pause", StringValue ("ns3::UniformRandomVariable[Min=2|Max=60]"),
                             "Speed", StringValue ("ns3::UniformRandomVariable[Min=1|Max=4]"),
                             "PositionAllocator", PointerValue(&posAllocator)
                             );
  mobility.Install (ue2);
  mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel",
                             "Pause", StringValue ("ns3::UniformRandomVariable[Min=2|Max=30]"),
                             "Speed", StringValue ("ns3::UniformRandomVariable[Min=0.3|Max=0.7]"),
                             "PositionAllocator", PointerValue(&posAllocator)
                             );
  mobility.Install (ue3);
  mobility.SetPositionAllocator ("ns3::RandomBoxPositionAllocator",
                                 "X", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=800.0]"),
                                 "Y", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=800.0]"),
                                 "Z", StringValue ("ns3::UniformRandomVariable[Min=0.0|Max=10.0]"));
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (ue4);

  Ptr<MecEntityContainer> ueContainer1 = h.InstallUeEntity(ue1, bsContainer, 1, 10*60, 10*60);
  Ptr<MecEntityContainer> ueContainer2 = h.InstallUeEntity(ue2, bsContainer, 2, 60*60, 60*60);
  Ptr<MecEntityContainer> ueContainer3 = h.InstallUeEntity(ue3, bsContainer, 2, 15*60, 30*60);
  Ptr<MecEntityContainer> ueContainer4 = h.InstallUeEntity(ue4, bsContainer, 3, 1, 80000);

  h.AttachToClosestEnb(ueContainer1, bsContainer);
  h.AttachToClosestEnb(ueContainer2, bsContainer);
  h.AttachToClosestEnb(ueContainer3, bsContainer);
  h.AttachToClosestEnb(ueContainer4, bsContainer);



  Simulator::Stop (Seconds (3600*8));
  Simulator::Run ();

  Simulator::Destroy ();
  return 0;
}


