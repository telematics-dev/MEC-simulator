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

#ifndef MEC_DATA_APP_INSTANCE_LCM_OPERATION_OCCURRENCY_H
#define MEC_DATA_APP_INSTANCE_LCM_OPERATION_OCCURRENCY_H


#include <string>
#include <ns3/core-module.h>
#include <list>
#include "mec-data-app-instance-info.h"


namespace ns3 {

class AppInstanceLcmOpOcc : public Object
{
public:
  static TypeId GetTypeId (void);

  AppInstanceLcmOpOcc ();
  virtual ~AppInstanceLcmOpOcc ();

private:
  uint64_t m_id;
  uint8_t m_operationState;
  Time m_stateEnteredTime;
  Time m_startTime;
  uint8_t m_lcmOperation;
  Ptr<AppInstanceInfo> m_appInstance;

public:
  uint64_t GetId(void);
  uint8_t GetOperationState(void);
  Time GetStateEnteredTime(void);
  Time GetStartTime(void);
  uint8_t GetLcmOperation(void);
  Ptr<AppInstanceInfo> GetAppInstance(void);

  void SetId(uint64_t id);
  void SetOperationState(uint8_t operationState);
  void SetStateEnteredTime(Time stateEnteredTime);
  void SetStartTime(Time startTime);
  void SetLcmOperation(uint8_t lcmOperation);
  void SetAppInstance(Ptr<AppInstanceInfo> appInstance);

  int Size (void);
};

}

#endif /* MEC_DATA_APP_INSTANCE_LCM_OPERATION_OCCURRENCY_H */

