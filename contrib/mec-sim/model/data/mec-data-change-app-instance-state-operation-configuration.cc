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


#include "mec-data-change-app-instance-state-operation-configuration.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ChangeAppInstanceStateOpConfig");

TypeId ChangeAppInstanceStateOpConfig::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ChangeAppInstanceStateOpConfig")
    .SetParent<Object> ();
  return tid;
}

ChangeAppInstanceStateOpConfig::ChangeAppInstanceStateOpConfig ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
  SetMinGracefulStopTimeout(5);
  SetMaxRecommendedGracefulStopTimeout(5);
}

ChangeAppInstanceStateOpConfig::~ChangeAppInstanceStateOpConfig()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
ChangeAppInstanceStateOpConfig::SetMinGracefulStopTimeout (double minGracefulStopTimeout)
{
  NS_LOG_FUNCTION (this->GetTypeId() << minGracefulStopTimeout);
  m_minGracefulStopTimeout = minGracefulStopTimeout;
}

double
ChangeAppInstanceStateOpConfig::GetMinGracefulStopTimeout (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_minGracefulStopTimeout;
}

void
ChangeAppInstanceStateOpConfig::SetMaxRecommendedGracefulStopTimeout (double maxRecommendedGracefulStopTimeout)
{
  NS_LOG_FUNCTION (this->GetTypeId() << maxRecommendedGracefulStopTimeout);
  m_maxRecommendedGracefulStopTimeout = maxRecommendedGracefulStopTimeout;
}

double
ChangeAppInstanceStateOpConfig::GetMaxRecommendedGracefulStopTimeout (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_maxRecommendedGracefulStopTimeout;
}

int
ChangeAppInstanceStateOpConfig::Size (void)
{
  int sz = sizeof(m_minGracefulStopTimeout) + sizeof(m_maxRecommendedGracefulStopTimeout);
  return sz;
}
} // namespace ns3
