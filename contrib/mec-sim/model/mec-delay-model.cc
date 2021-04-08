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


#include "mec-delay-model.h"
#include "ns3/log.h"


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecDelayModel");

TypeId MecDelayModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecDelayModel")
    .SetParent<Object> ();
  return tid;
}

MecDelayModel::MecDelayModel ()
{
  NS_LOG_FUNCTION (this);

  m_datasetSize = 10000;
  m_controlPlaneLatency = CreateObject<UniformRandomVariable>();
  m_controlPlaneLatency->SetAttribute("Min", DoubleValue(0.001*3.26));
  m_controlPlaneLatency->SetAttribute("Max", DoubleValue(0.001*3.31));

  m_backhaulLatency = CreateObject<UniformRandomVariable>();
  m_backhaulLatency->SetAttribute("Min", DoubleValue(0));


  m_datasetLine = CreateObject<UniformRandomVariable>();
  m_datasetLine->SetAttribute("Min", DoubleValue(0));
  m_datasetLine->SetAttribute("Max", DoubleValue(m_datasetSize));

  std::string folder;
  folder = "contrib/mec-sim/model/radio_delay/App1.txt";
  m_radioLatencyApp1.open(folder);
  std::string s;
  double temp;
  for(int i=0; i<m_datasetSize; i++)
    {
      getline(m_radioLatencyApp1,s);
      std::istringstream iss(s);
      for(int j =1;j<=i&&i<40; j++)
        {
          iss >> temp;
          m_radioDelay1[i][j] = temp;
        }
    }
  folder = "contrib/mec-sim/model/radio_delay/App2.txt";
  m_radioLatencyApp2.open(folder);
  for(int i=0; i<m_datasetSize; i++)
    {
      getline(m_radioLatencyApp2,s);
      std::istringstream iss(s);
      for(int j =1;j<=i&&i<40; j++)
        {
          iss >> temp;
          m_radioDelay2[i][j] = temp;        }
    }
  folder = "contrib/mec-sim/model/radio_delay/App3.txt";
  m_radioLatencyApp3.open(folder);
  for(int i=0; i<m_datasetSize; i++)
    {
      getline(m_radioLatencyApp3,s);
      std::istringstream iss(s);
      for(int j =1;j<=i&&i<40; j++)
        {
          iss >> temp;
          m_radioDelay3[i][j] = temp;        }
    }

}

MecDelayModel::~MecDelayModel ()
{
  NS_LOG_FUNCTION (this);
  m_radioLatencyApp1.close();
  m_radioLatencyApp2.close();
  m_radioLatencyApp3.close();

}

double
MecDelayModel::GetRadioDelayExtraction(double data, int i)
{
  double t;
//  int j = m_datasetLine->GetInteger();
  //t = data[i][i];
  t=1;
  return t;
}

Time
MecDelayModel::GetRadioDelay(int activeFlow, uint64_t appid)
{
  if(activeFlow<1)
    {
      activeFlow=1;
    }
  double t;
  int j = m_datasetLine->GetInteger();
  switch (appid) {
    case 1: t = m_radioDelay1[j][activeFlow];
    break;
    case 2: t = m_radioDelay2[j][activeFlow];
    break;
    case 3: t = m_radioDelay3[j][activeFlow];
    break;
    default: t = m_radioDelay2[j][activeFlow];
  }
  return Seconds(t);
}

Time
MecDelayModel::GetBackhaulDelay(double linkLatency)
{
  m_backhaulLatency->SetAttribute("Max", DoubleValue(linkLatency));
  double t = m_backhaulLatency->GetValue();
  return Seconds(t);
}

Time
MecDelayModel::GetControlPlaneDelay()
{
  double t = m_controlPlaneLatency->GetValue();
  return Seconds(t);
}

Time
MecDelayModel::GetBootingTime(double bootNoContention, double cpuUtilizzation)
{
  double t;
  if(cpuUtilizzation<0.95)
    t = bootNoContention/(1-cpuUtilizzation);
  else
    t = bootNoContention/(1-0.95);
  return Seconds(t);
}


} // namespace ns3
