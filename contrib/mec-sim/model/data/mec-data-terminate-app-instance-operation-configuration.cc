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


#include "mec-data-terminate-app-instance-operation-configuration.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TerminateAppInstanceOpConfig");

TypeId TerminateAppInstanceOpConfig::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TerminateAppInstanceOpConfig")
    .SetParent<Object> ();
  return tid;
}

TerminateAppInstanceOpConfig::TerminateAppInstanceOpConfig ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
  m_maxRecommendedGracefulTerminationTimeout = 5;
  m_minGracefulTerminationTimeout = 5;
}

TerminateAppInstanceOpConfig::~TerminateAppInstanceOpConfig()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
TerminateAppInstanceOpConfig::SetMinGracefulTerminationTimeout (double minGracefulTerminationTimeout)
{
  NS_LOG_FUNCTION (this->GetTypeId() << minGracefulTerminationTimeout);
  m_minGracefulTerminationTimeout = minGracefulTerminationTimeout;
}

double
TerminateAppInstanceOpConfig::GetMinGracefulTerminationTimeout (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_minGracefulTerminationTimeout;
}

void
TerminateAppInstanceOpConfig::SetMaxRecommendedGracefulTerminationTimeout (double maxRecommendedGracefulTerminationTimeout)
{
  NS_LOG_FUNCTION (this->GetTypeId() << maxRecommendedGracefulTerminationTimeout);
  m_maxRecommendedGracefulTerminationTimeout = maxRecommendedGracefulTerminationTimeout;
}

double
TerminateAppInstanceOpConfig::GetMaxRecommendedGracefulTerminationTimeout (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_maxRecommendedGracefulTerminationTimeout;
}
int
TerminateAppInstanceOpConfig::Size (void)
{
  int sz = sizeof(m_minGracefulTerminationTimeout) + sizeof(m_maxRecommendedGracefulTerminationTimeout);
  return sz;
}
} // namespace ns3
