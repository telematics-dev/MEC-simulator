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

#include "mec-data-service-registration-info.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ServiceRegistrationInfo");

TypeId ServiceRegistrationInfo::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ServiceRegistrationInfo")
    .SetParent<Object> ();
  return tid;
}

ServiceRegistrationInfo::ServiceRegistrationInfo ()
{
   m_appInstanceId=0;
   m_mepId=0;
   m_imsi=0;
  NS_LOG_FUNCTION (this);
}

ServiceRegistrationInfo::~ServiceRegistrationInfo ()
{
  NS_LOG_FUNCTION (this);
}

void
ServiceRegistrationInfo::SetSubscriptionType (std::string subscriptionType)
{
  NS_LOG_FUNCTION (this << subscriptionType);
  m_subscriptionType = subscriptionType;
}

void
ServiceRegistrationInfo::SetAppInstanceId (uint64_t appInstanceId)
{
  NS_LOG_FUNCTION (this << appInstanceId);
  m_appInstanceId = appInstanceId;
}

void
ServiceRegistrationInfo::SetImsi (uint64_t imsi)
{
  NS_LOG_FUNCTION (this << imsi);
  m_imsi = imsi;
}

void
ServiceRegistrationInfo::SetMepId (uint64_t mepId)
{
  NS_LOG_FUNCTION (this << mepId);
  m_mepId = mepId;
}

void
ServiceRegistrationInfo::SetMecApp (Ptr<MecApp> mecApp)
{
  NS_LOG_FUNCTION (this << mecApp);
  m_mecApp = mecApp;
}

void
ServiceRegistrationInfo::SetCallback (Ptr<MecEntity> callback)
{
  NS_LOG_FUNCTION (this << callback);
  m_callback = callback;
}

Ptr<MecEntity>
ServiceRegistrationInfo::GetCallback()
{
  NS_LOG_FUNCTION (this);
  return m_callback;
}
std::string
ServiceRegistrationInfo::GetSubscriptionType()
{
  NS_LOG_FUNCTION (this);
  return m_subscriptionType;
}

uint64_t
ServiceRegistrationInfo::GetAppInstanceId()
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceId;
}

uint64_t
ServiceRegistrationInfo::GetImsi()
{
  NS_LOG_FUNCTION (this);
  return m_imsi;
}

uint64_t
ServiceRegistrationInfo::GetmepId()
{
  NS_LOG_FUNCTION (this);
  return m_mepId;
}

Ptr<MecApp>
ServiceRegistrationInfo::GetMecApp(void)
{
  NS_LOG_FUNCTION (this);
  return m_mecApp;
}

int
ServiceRegistrationInfo::Size (void)
{
  int sz = sizeof(m_subscriptionType) +
      sizeof(m_appInstanceId)+
      sizeof(m_mepId)+
      sizeof(m_imsi);
  return sz;
}
} // namespace ns3
