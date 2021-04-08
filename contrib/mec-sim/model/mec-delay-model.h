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
 *         Simona Massari - s.massari1@studenti.poliba.it
 */

#ifndef MEC_DELAY_MODEL_H
#define MEC_DELAY_MODEL_H

#include <map>
#include <ns3/core-module.h>
#include "ns3/object.h"
#include "ns3/nstime.h"
#include "ns3/ptr.h"
#include "ns3/random-variable-stream.h"
#include <iostream>
#include <fstream>

namespace ns3 {

class MecDelayModel : public Object
{
public:
  static TypeId GetTypeId (void);

  MecDelayModel ();
  virtual ~MecDelayModel ();

  Time GetRadioDelay(int activeFlow, uint64_t appId);
  Time GetBackhaulDelay(double linkLatency);
  Time GetControlPlaneDelay();
  Time GetBootingTime(double bootNoContention, double cpuUtilizzation);

private:
  double GetRadioDelayExtraction(double data, int i);
  std::map<std::string, double> m_trasmissionDelay;
  std::map<std::string, double> m_computationalDelay;
  Ptr<UniformRandomVariable> m_controlPlaneLatency;
  Ptr<UniformRandomVariable> m_backhaulLatency;
  std::ifstream m_radioLatencyApp1;
  std::ifstream m_radioLatencyApp2;
  std::ifstream m_radioLatencyApp3;
  int m_datasetSize;
  Ptr<UniformRandomVariable> m_datasetLine;
  double m_radioDelay1 [10000][40];
  double m_radioDelay2 [10000][40];
  double m_radioDelay3 [10000][40];

};
}
#endif /* MEC_DELAY_MODEL_H */

