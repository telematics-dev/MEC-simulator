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

#ifndef MEC_MESSAGE_TASK_OFFLOADING_H
#define MEC_MESSAGE_TASK_OFFLOADING_H


#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/mec-data.h"
#include "ns3/client-app.h"
#include "ns3/mec-entity-app.h"

namespace ns3 {

class ClientApp;
class MecApp;

class TaskOffloading : public Object
{
public:
  static TypeId GetTypeId (void);


  TaskOffloading ();
  virtual ~TaskOffloading ();

private:
  uint64_t m_istructions; // Mega Istructions (MI)
  Time m_startingTime;
  Time m_processingTime;
  Ptr<ClientApp> m_clientApp;
  Ptr<MecApp> m_mecApp;
  bool m_error;


public:
  uint64_t GetIstructionNumber (void);
  Time GetStartingTime (void);
  Time GetProcessingTime (void);
  Ptr<ClientApp> GetClientApp (void);
  Ptr<MecApp> GetMecApp (void);
  bool GetError (void);
  void SetIstructionNumber (uint64_t istruction);
  void SetStartingTime (Time time);
  void SetProcessingTime (Time time);
  void SetClientApp (Ptr<ClientApp> clientApp);
  void SetMecApp (Ptr<MecApp> mecApp);
  void SetError (bool error);

};

  }
  #endif /* MEC_MESSAGE_TASK_OFFLOADING_H */
