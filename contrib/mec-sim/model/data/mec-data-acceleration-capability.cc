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


#include "mec-data-acceleration-capability.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AccelerationCapability");

TypeId AccelerationCapability::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AccelerationCapability")
    .SetParent<Object> ();
  return tid;
}

AccelerationCapability::AccelerationCapability ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
  m_isRequired = 0;
  m_numberOfAccelerationCapability = 0;
}

AccelerationCapability::AccelerationCapability (std::string typeOfAccelerationCapability, int n)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  m_typeOfAccelerationCapability = typeOfAccelerationCapability;
  m_numberOfAccelerationCapability = n;
}

AccelerationCapability::~AccelerationCapability()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
AccelerationCapability::SetIsRequired (bool isRequired)
{
  NS_LOG_FUNCTION (this->GetTypeId() << isRequired);
  m_isRequired = isRequired;
}

bool
AccelerationCapability::GetIsRequired (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_isRequired;
}

void
AccelerationCapability::SetTypeOfAccelerationCapability (std::string typeOfAccelerationCapability)
{
  NS_LOG_FUNCTION (this->GetTypeId() << typeOfAccelerationCapability);
  m_typeOfAccelerationCapability = typeOfAccelerationCapability;
}

std::string
AccelerationCapability::GetTypeOfAccelerationCapability (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_typeOfAccelerationCapability;
}

void
AccelerationCapability::SetNumberOfAccelerationCapability (int n)
{
  m_numberOfAccelerationCapability =n;
}
int
AccelerationCapability::GetNumberOfAccelerationCapability (void)
{
  return m_numberOfAccelerationCapability;
}


int
AccelerationCapability::Size (void)
{
  int sz = sizeof(m_isRequired) + sizeof(m_numberOfAccelerationCapability) + m_typeOfAccelerationCapability.length();
  return sz;
}

} // namespace ns3
