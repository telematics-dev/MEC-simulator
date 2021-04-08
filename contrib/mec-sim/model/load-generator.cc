
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
#include "load-generator.h"
#include "ns3/log.h"


NS_LOG_COMPONENT_DEFINE ("LoadGenerator");

namespace ns3 {

LoadGenerator::LoadGenerator (void)
{
  m_lambda = 0;
  m_mu = 0;
  m_contextIdCounter = 0;
  m_appRep = 0;
  m_appdId = 0;
  m_interarrivalTime = CreateObject<ExponentialRandomVariable> ();
  m_serviceTime = CreateObject<ExponentialRandomVariable> ();
}

LoadGenerator::~LoadGenerator (void)
{

}

TypeId LoadGenerator::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LoadGenerator")
    .SetParent<Object> ();
  return tid;
}

void
LoadGenerator::SetNode(Ptr<Node> node)
{
  NS_LOG_FUNCTION (this);
  m_node = node;
}

void
LoadGenerator::SetLambda(double lambda)
{
  NS_LOG_FUNCTION (this << lambda);
  m_lambda = lambda;
  m_interarrivalTime->SetAttribute ("Mean", DoubleValue (lambda));
  m_interarrivalTime->SetAttribute ("Bound", DoubleValue (0.0));
}

void
LoadGenerator::SetMu(double mu)
{
  NS_LOG_FUNCTION (this << mu);
  m_mu = mu;
  m_serviceTime->SetAttribute ("Mean", DoubleValue (mu));
  m_serviceTime->SetAttribute ("Bound", DoubleValue (0.0));
}

void
LoadGenerator::Inizialize()
{
  NS_LOG_FUNCTION (this );
  m_appRep = CreateObject<AppRepository>();
  m_appRep->CreateList();
  Ptr<UserEquipment> ue = m_node->GetObject<UserEquipment>();
  DoStart(ue);
}

void
LoadGenerator::DoStart(Ptr<UserEquipment> ue)
{
  NS_LOG_FUNCTION (this);
  Ptr<AppD> appD = m_appRep->FindApp(m_appdId).first;
  Ptr<AppContext> appContext = DoCreateAppContext(appD);
  appContext->SetCallbackReference(ue);

  Time start = Seconds(m_interarrivalTime->GetValue());
  Time duration = Seconds(m_serviceTime->GetValue());

  Simulator::Schedule(start, &UserEquipment::SendCreateAppContextRequest, ue, appContext);
  Simulator::Schedule(start + duration, &LoadGenerator::DoStart, this, ue);
  Simulator::Schedule(start + duration, &UserEquipment::SendDeleteAppContextRequest, ue, appContext->GetContextId());
}

//Ptr<UserEquipment>
//LoadGenerator::DoSelectRndUe (void)
//{
//  uint32_t N = m_ueContainer->GetN();
//  uint32_t ue = rand()%N;
//  Ptr<UserEquipment> UE = DynamicCast<UserEquipment>(m_ueContainer->Get(ue));
//  return UE;
//}

Ptr<AppContext>
LoadGenerator::DoCreateAppContext (Ptr<AppD> appD)
{
  NS_LOG_FUNCTION (this << appD);
  Ptr<AppContext> appContext = CreateObject<AppContext> ();
  m_contextIdCounter++;
  appContext->SetContextId(std::to_string(m_contextIdCounter));
  appContext->SetAppDId(appD->GetAppDId());
  appContext->SetAppName(appD->GetAppName());
  appContext->SetAppProvider(appD->GetAppProvider());
  appContext->SetAppSoftwareVersion(appD->GetAppSoftwareVersion());
  appContext->SetAppDVersion(appD->GetAppDVersion());
  appContext->SetAppDescription(appD->GetAppDescription());

//  NS_LOG_FUNCTION (this->GetInstanceTypeId() <<
//       std::string("\n\t\t\t\t ContextId:\t ") + appContext->GetContextId() <<
//       std::string("\n\t\t\t\t AppDId:\t ") << appContext->GetAppDId() <<
//       std::string("\n\t\t\t\t AppName:\t ") + appContext->GetAppName() <<
//       std::string("\n\t\t\t\t AppProvider:\t ") + appContext->GetAppProvider() <<
//       std::string("\n\t\t\t\t AppSoftVersion: ") + appContext->GetAppSoftwareVersion() <<
//       std::string("\n\t\t\t\t AppDVersion:\t ") + appContext->GetAppDVersion() <<
//       std::string("\n\t\t\t\t AppDescription: ") + appContext->GetAppDescription()
//       );
  return appContext;
}

void
LoadGenerator::SetAppdId(double id)
{
  NS_LOG_FUNCTION (this << id);
  m_appdId = id;
}

}
