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

#ifndef LOAD_GENERATOR_H
#define LOAD_GENERATOR_H

#include <ns3/ptr.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include <string>
#include <list>
#include "mec-entity-ue.h"
#include "mec-entity-container.h"
#include "ns3/random-variable-stream.h"

namespace ns3 {

class LoadGenerator : public Object
{
public:
  static TypeId GetTypeId (void);
  LoadGenerator (void);
  ~LoadGenerator (void);

  void SetNode(Ptr<Node> node);
  void SetLambda(double lambda);
  void SetMu(double mu);
  void SetAppdId(double id);
  void Inizialize(void);

  void DoStart (Ptr<UserEquipment> ue);
//  Ptr<UserEquipment> DoSelectRndUe (void);
  Ptr<AppContext> DoCreateAppContext (Ptr<AppD> appD);
private:
  Ptr<Node> m_node;
  Ptr<AppRepository> m_appRep;
  double m_appdId;
  int m_contextIdCounter;
  double m_mu;
  double m_lambda;
  Ptr<ExponentialRandomVariable> m_interarrivalTime;
  Ptr<ExponentialRandomVariable> m_serviceTime;
};

} //namespace ns3

#endif /* LOAD_GENERATOR_H */
