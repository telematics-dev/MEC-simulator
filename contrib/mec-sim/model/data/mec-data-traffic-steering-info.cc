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


#include "mec-data-traffic-steering-info.h"
#include "ns3/log.h"
#include <ns3/math.h>
#include <array>
#include <ns3/double.h>


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TrafficSteeringInfo");

TypeId TrafficSteeringInfo::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TrafficSteeringInfo")
    .SetParent<Object> ();
  return tid;
}

TrafficSteeringInfo::TrafficSteeringInfo ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

TrafficSteeringInfo::~TrafficSteeringInfo ()
{
  NS_LOG_FUNCTION (this);
}

Ptr<UserEquipment>
TrafficSteeringInfo::GetUe()
{
  NS_LOG_FUNCTION (this);
  return m_ue;
}

void
TrafficSteeringInfo::SetUe(Ptr<UserEquipment> ue)
{
  NS_LOG_FUNCTION (this << ue);
  m_ue=ue;
}

uint64_t
TrafficSteeringInfo::GetAppInstanceId()
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceId;
}

void
TrafficSteeringInfo::SetAppInstanceId(uint64_t appInstanceId)
{
  NS_LOG_FUNCTION (this << appInstanceId);
  m_appInstanceId=appInstanceId;
}

double
TrafficSteeringInfo::GetGuaranteedUplink()
{
  NS_LOG_FUNCTION (this);
  return m_guaranteedUplink;
}

void
TrafficSteeringInfo::SetGuaranteedUplink(double guaranteedUplink)
{
  NS_LOG_FUNCTION (this << guaranteedUplink);
  m_guaranteedUplink=guaranteedUplink;
}

double
TrafficSteeringInfo::GetGuaranteedDownlink()
{
  NS_LOG_FUNCTION (this);
  return m_guaranteedDownlink;
}

void
TrafficSteeringInfo::SetGuaranteedDownlink(double guaranteedDownlink)
{
  NS_LOG_FUNCTION (this << guaranteedDownlink);
  m_guaranteedDownlink=guaranteedDownlink;
}

bool
TrafficSteeringInfo::GetState()
{
  NS_LOG_FUNCTION (this);
  return m_state;
}

void
TrafficSteeringInfo::SetState(bool state)
{
  NS_LOG_FUNCTION (this << state);
  m_state=state;
}

} //end namespace ns3

