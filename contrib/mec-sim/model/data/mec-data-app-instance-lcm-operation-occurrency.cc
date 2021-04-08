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


#include "mec-data-app-instance-lcm-operation-occurrency.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AppInstanceLcmOpOcc");

TypeId AppInstanceLcmOpOcc::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AppInstanceLcmOpOcc")
    .SetParent<Object> ();
  return tid;
}

AppInstanceLcmOpOcc::AppInstanceLcmOpOcc ()
{
  m_id = rand() % 100000000;
  m_operationState = 0;
  m_lcmOperation = 0;
  NS_LOG_FUNCTION (this);
}

AppInstanceLcmOpOcc::~AppInstanceLcmOpOcc ()
{
  NS_LOG_FUNCTION (this);
}

uint64_t
AppInstanceLcmOpOcc::GetId(void)
{
  NS_LOG_FUNCTION (this);
  return m_id;
}

uint8_t
AppInstanceLcmOpOcc::GetOperationState(void)
{
  NS_LOG_FUNCTION (this);
  return m_operationState;
}

Time
AppInstanceLcmOpOcc::GetStateEnteredTime(void)
{
  NS_LOG_FUNCTION (this);
  return m_stateEnteredTime;
}

Time
AppInstanceLcmOpOcc::GetStartTime(void)
{
  NS_LOG_FUNCTION (this);
  return m_startTime;
}

uint8_t
AppInstanceLcmOpOcc::GetLcmOperation(void)
{
  NS_LOG_FUNCTION (this);
  return m_lcmOperation;
}

Ptr<AppInstanceInfo>
AppInstanceLcmOpOcc::GetAppInstance(void)
{
  NS_LOG_FUNCTION (this);
  return m_appInstance;
}


void
AppInstanceLcmOpOcc::SetId(uint64_t id)
{
  NS_LOG_FUNCTION (this << id);
  m_id = id;
}

void
AppInstanceLcmOpOcc::SetOperationState(uint8_t operationState)
{
  NS_LOG_FUNCTION (this << operationState);
  m_operationState = operationState;
}

void
AppInstanceLcmOpOcc::SetStateEnteredTime(Time stateEnteredTime)
{
  NS_LOG_FUNCTION (this << stateEnteredTime);
  m_stateEnteredTime = stateEnteredTime;
}

void
AppInstanceLcmOpOcc::SetStartTime(Time startTime)
{
  NS_LOG_FUNCTION (this << startTime);
  m_startTime = startTime;
}

void
AppInstanceLcmOpOcc::SetLcmOperation(uint8_t lcmOperation)
{
  NS_LOG_FUNCTION (this << lcmOperation);
  m_lcmOperation = lcmOperation;
}

void
AppInstanceLcmOpOcc::SetAppInstance(Ptr<AppInstanceInfo> appInstance)
{
  NS_LOG_FUNCTION (this << appInstance);
  m_appInstance = appInstance;
}




int
AppInstanceLcmOpOcc::Size (void)
{
  int sz = sizeof(m_id) +
	  sizeof(m_operationState) +
	  sizeof(m_stateEnteredTime) +
	  sizeof(m_startTime) +
	  sizeof(m_lcmOperation) +
	  sizeof(m_appInstance);
  return sz;
}
} // namespace ns3
