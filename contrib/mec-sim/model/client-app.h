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

#ifndef CLIENT_APP_H
#define CLIENT_APP_H

#include <string>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-delay-model.h"
#include "mec-entity.h"
#include "ns3/random-variable-stream.h"



namespace ns3 {

class MecPlataform;
class ApplicationMobilityService;
class CreateAppMobilityServiceResponse;
class AppReadyConfirmationResponse;
class TaskOffloading;

class ClientApp : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  ClientApp ();
  virtual ~ClientApp ();

  Ptr<MecDelayModel> GetDelayModel(void);
  void SetState(bool state);
  void SetUe(Ptr<UserEquipment> ue);
  void SetMecApp(Ptr<MecApp> mecApp);
  void SetContextId(std::string contextId);
  bool GetState(void);
  Ptr<UserEquipment> GetUe(void);
  Ptr<MecApp> GetMecApp(void);
  void SetTaskSize(Ptr<RandomVariableStream> taskSize);
  void SetInterarrivalTime(Ptr<RandomVariableStream> taskInterarrivalTime);

  void SetActiveIdle(double active, double idle);
  void DoActive(void);
  void DoIdle(void);
  void Start(void);
  void SendTaskOffloadingRequest(void);
  void ProcessTaskOffloadingResponse(Ptr<TaskOffloading> task);

private:
  Ptr<UserEquipment> m_ue;
  std::string m_contextId;
  Ptr<MecApp> m_mecApp;
  bool m_state;
  Ptr<RandomVariableStream> m_taskSize;
  Ptr<RandomVariableStream> m_taskInterarrivalTime;
  double m_activeTime;
  double m_idleTime;
  double sum_e2e;
  double sum_processing;
  double n_e2e;
  double n_processing;
  Time m_startTime;
  Time m_endTime;
  uint64_t m_appDiD;

};
}
#endif /* CLIENT_APP_H */
