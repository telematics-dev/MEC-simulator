
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
#include "app-repository.h"
#include "ns3/log.h"


NS_LOG_COMPONENT_DEFINE ("AppRepository");

namespace ns3 {

AppRepository::AppRepository (void)
{
  CreateList();
}

AppRepository::~AppRepository (void)
{

}

TypeId AppRepository::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AppRepository")
    .SetParent<Object> ();
  return tid;
}

Ptr<AppD>
AppRepository::NewApp (void)
{
  Ptr<AppD> app = m_appRepository.front();
  return app;
}

std::pair<Ptr<AppD>, int16_t>
AppRepository::FindApp (uint64_t appDId)
{
  std::list <Ptr<AppD>> :: iterator it;
  Ptr<AppD> no_app = 0;
  for(it = m_appRepository.begin(); it != m_appRepository.end(); ++it)
  {
    if(((*it)->GetAppDId()) == appDId)
    {
      NS_LOG_FUNCTION ("appD found");
      return std::make_pair((*it), 200);
    }
  }

  NS_LOG_FUNCTION ("appD not found");
  return std::make_pair(no_app, 404);
}

Ptr<AppD>
AppRepository::FindApp (std::string appPkgName, std::string appPkgVersion)
{
  std::list <Ptr<AppD>> :: iterator it;
  Ptr<AppD> app;
  for(it = m_appRepository.begin(); it != m_appRepository.end(); ++it)
  {
    app = *it;
    if((app->GetAppName() == appPkgName) && (app->GetAppSoftwareVersion() == appPkgVersion ))
    {
      NS_LOG_FUNCTION ("appD found");
      return app;
    }
  }

  NS_LOG_FUNCTION ("appD not found");
  return app;
}

std::list <Ptr<AppD>>
AppRepository::CreateList(void)
{
  Ptr<AppD> app;

  /////////////////////////////////////////////////
  ///         APP_1:                            ///
  /////////////////////////////////////////////////
  app = CreateObject<AppD> ();
  m_appRepository.push_back(app);

  app->SetAppDId (1);
  app->SetAppName ("MR");
  app->SetAppDescription ("This is a test application designed to evaluate the performance of the MEC simulator.");
  app->GetVirtualResourceDescriptor()->GetVirtualCpu()->SetNumVirtualCpu(2);
  app->GetVirtualResourceDescriptor()->GetVirtualCpu()->SetCpuClock(2.00);
  app->GetVirtualResourceDescriptor()->GetVirtualMemory()->SetVirtualMemSize(1.3*1024);
  app->GetVirtualResourceDescriptor()->GetVirtualStorage()->SetSizeOfStorage(5*1024);
  app->GetSwImageDescriptor()->SetSize(340*1024*1024);
  app->GetAppTrafficRule()->SetQosGbrDl(20.00);
  app->GetAppTrafficRule()->SetQosGbrUl(10.00);
  app->GetAppLatency()->SetMaxLatency(0.010);
  app->SetBootingTime(2.5);
  Ptr<UniformRandomVariable> L1 = CreateObject<UniformRandomVariable> ();
  L1->SetAttribute ("Min", DoubleValue (250));
  L1->SetAttribute ("Max", DoubleValue (400));
  app->SetTaskLength(L1);
  Ptr<ConstantRandomVariable> T1 = CreateObject<ConstantRandomVariable> ();
  T1->SetAttribute ("Constant", DoubleValue (0.033));
  app->SetTaskInterarrival(T1);

  /////////////////////////////////////////////////
  ///         APP_2:                            ///
  /////////////////////////////////////////////////
  app = CreateObject<AppD> ();
  m_appRepository.push_back(app);

  app->SetAppDId (2);
  app->SetAppName ("AGV");
  app->SetAppDescription ("This is a test application designed to evaluate the performance of the MEC simulator.");
  app->GetVirtualResourceDescriptor()->GetVirtualCpu()->SetNumVirtualCpu(2);
  app->GetVirtualResourceDescriptor()->GetVirtualCpu()->SetCpuClock(2.00);
  app->GetVirtualResourceDescriptor()->GetVirtualMemory()->SetVirtualMemSize(1*1024);
  app->GetVirtualResourceDescriptor()->GetVirtualStorage()->SetSizeOfStorage(3*1024);
  app->GetSwImageDescriptor()->SetSize(340*1024*1024);
  app->GetAppTrafficRule()->SetQosGbrDl(20.00);
  app->GetAppTrafficRule()->SetQosGbrUl(10.00);
  app->GetAppLatency()->SetMaxLatency(0.010);
  app->SetBootingTime(1);
  Ptr<UniformRandomVariable> L2 = CreateObject<UniformRandomVariable> ();
  L2->SetAttribute ("Min", DoubleValue (50));
  L2->SetAttribute ("Max", DoubleValue (300));
  app->SetTaskLength(L2);
  Ptr<UniformRandomVariable> T2 = CreateObject<UniformRandomVariable> ();
  T2->SetAttribute ("Min", DoubleValue (50));
  T2->SetAttribute ("Max", DoubleValue (300));
  app->SetTaskInterarrival(T2);

  /////////////////////////////////////////////////
  ///         APP_3:                            ///
  /////////////////////////////////////////////////
  app = CreateObject<AppD> ();
  m_appRepository.push_back(app);

  app->SetAppDId (3);
  app->SetAppName ("IIoT");
  app->SetAppDescription ("This is a test application designed to evaluate the performance of the MEC simulator.");
  app->GetVirtualResourceDescriptor()->GetVirtualCpu()->SetNumVirtualCpu(2);
  app->GetVirtualResourceDescriptor()->GetVirtualCpu()->SetCpuClock(2.00);
  app->GetVirtualResourceDescriptor()->GetVirtualMemory()->SetVirtualMemSize(0.256*1024);
  app->GetVirtualResourceDescriptor()->GetVirtualStorage()->SetSizeOfStorage(5*1024);
  app->GetSwImageDescriptor()->SetSize(340*1024*1024);
  app->GetAppTrafficRule()->SetQosGbrDl(20.00);
  app->GetAppTrafficRule()->SetQosGbrUl(10.00);
  app->GetAppLatency()->SetMaxLatency(0.010);
  app->SetBootingTime(0.5);
  Ptr<UniformRandomVariable> L3 = CreateObject<UniformRandomVariable> ();
  L3->SetAttribute ("Min", DoubleValue (20));
  L3->SetAttribute ("Max", DoubleValue (50));
  app->SetTaskLength(L3);
  Ptr<ConstantRandomVariable> T3 = CreateObject<ConstantRandomVariable> ();
  T3->SetAttribute ("Constant", DoubleValue (0.002));
  app->SetTaskInterarrival(T3);

  NS_LOG_INFO ("\t- AppRepository\t\t\tCreated");

  return m_appRepository;
}

void
AppRepository::TraceReader(std::string filename, Ptr<UserEquipment> ue)
{
  std::ifstream iFile(filename);
  std::string s;

  double t;
  uint64_t appDId;
  double duration;

  if (!iFile)
    {
	      NS_LOG_FUNCTION("Il file non esiste!");

    }
  getline(iFile, s); //legge tutta la riga dal file e la mette nella variabile s
  while(iFile.good())
    {
      getline(iFile, s); //legge tutta la riga dal file e la mette nella variabile s
      NS_LOG_FUNCTION(this << s);

      std::istringstream iss(s);
      iss >> t;
      iss >> appDId;
      iss >> duration;

      std::pair<Ptr<AppD>, int16_t> appD = FindApp(appDId);
      if (appD.second < 300)
	{
	  Ptr<AppContext> req_app = ue->CreateAppContext(appD.first);
	  Simulator::Schedule(Seconds(t), &UserEquipment::SendCreateAppContextRequest, ue,req_app);
	  Simulator::Schedule(Seconds(t+duration), &UserEquipment::SendDeleteAppContextRequest, ue,req_app->GetContextId());
	 }
      t=0;
      appDId=0;
      duration=0;
    }
  iFile.close();
}


}
