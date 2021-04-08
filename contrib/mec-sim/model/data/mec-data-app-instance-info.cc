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


#include "mec-data-app-instance-info.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AppInstanceInfo");

TypeId AppInstanceInfo::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AppInstanceInfo")
    .SetParent<Object> ();
  return tid;
}

AppInstanceInfo::AppInstanceInfo ()
{
  m_hostId=0;
  m_operationalState=0;
  m_instantiationState=0;
  m_appPkgId=0;
  m_appDId=0;
  NS_LOG_FUNCTION (this);
}

AppInstanceInfo::~AppInstanceInfo ()
{
  NS_LOG_FUNCTION (this);
}

void
AppInstanceInfo::SetAppInstanceId (uint64_t appInstanceId)
{
  NS_LOG_FUNCTION (this << appInstanceId);
  m_appInstanceId = appInstanceId;
}
void
AppInstanceInfo::SetContextId (std::string contextId)
{
  NS_LOG_FUNCTION (this << contextId);
  m_contextId = contextId;
}
void
AppInstanceInfo::SetAppInstanceName (std::string appInstanceName)
{
  NS_LOG_FUNCTION (this << appInstanceName);
  m_appInstanceName = appInstanceName;
}
void
AppInstanceInfo::SetAppInstanceDescription (std::string appInstanceDescription)
{
  NS_LOG_FUNCTION (this << appInstanceDescription);
  m_appInstanceDescription = appInstanceDescription;
}
void
AppInstanceInfo::SetAppDId (uint64_t appDId)
{
  NS_LOG_FUNCTION (this << appDId);
  m_appDId = appDId;
}
void
AppInstanceInfo::SetAppProvider (std::string appProvider)
{
  NS_LOG_FUNCTION (this << appProvider);
  m_appProvider = appProvider;
}
void
AppInstanceInfo::SetAppName (std::string appName)
{
  NS_LOG_FUNCTION (this << appName);
  m_appName = appName;
}
void
AppInstanceInfo::SetAppSoftVersion (std::string appSoftVersion)
{
  NS_LOG_FUNCTION (this << appSoftVersion);
  m_appSoftVersion = appSoftVersion;
}
void
AppInstanceInfo::SetAppDVersion (std::string appDVersion)
{
  NS_LOG_FUNCTION (this << appDVersion);
  m_appDVersion = appDVersion;
}
void
AppInstanceInfo::SetAppPkgId (uint64_t appPkgId)
{
  NS_LOG_FUNCTION (this << appPkgId);
  m_appPkgId = appPkgId;
}
void
AppInstanceInfo::SetInstantiationState (bool instantiationState)
{
  NS_LOG_FUNCTION (this << instantiationState);
  m_instantiationState = instantiationState;
}
void
AppInstanceInfo::SetOperationalState (uint8_t operationalState)
{
  NS_LOG_FUNCTION (this << operationalState);
  m_operationalState = operationalState;
}
void
AppInstanceInfo::SetHostId(uint64_t hostId)
{
  NS_LOG_FUNCTION (this << hostId);
  m_hostId = hostId;

}


std::string
AppInstanceInfo::GetContextId (void)
{
  NS_LOG_FUNCTION (this);
  return m_contextId;
}

uint64_t
AppInstanceInfo::GetAppInstanceId (void)
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceId;
}

std::string
AppInstanceInfo::GetAppInstanceName (void)
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceName;
}

std::string
AppInstanceInfo::GetAppInstanceDescription (void)
{
  NS_LOG_FUNCTION (this);
  return m_appInstanceDescription;
}

uint64_t
AppInstanceInfo::GetAppDId (void)
{
  NS_LOG_FUNCTION (this);
  return m_appDId;
}

std::string
AppInstanceInfo::GetAppProvider (void)
{
  NS_LOG_FUNCTION (this);
  return m_appProvider;
}

std::string
AppInstanceInfo::GetAppName (void)
{
  NS_LOG_FUNCTION (this);
  return m_appName;
}

std::string
AppInstanceInfo::GetAppSoftVersion (void)
{
  NS_LOG_FUNCTION (this);
  return m_appSoftVersion;
}

std::string
AppInstanceInfo::GetAppDVersion (void)
{
  NS_LOG_FUNCTION (this);
  return m_appDVersion;
}

uint64_t
AppInstanceInfo::GetAppPkgId (void)
{
  NS_LOG_FUNCTION (this);
  return m_appPkgId;
}

bool
AppInstanceInfo::GetInstantiationState (void)
{
  NS_LOG_FUNCTION (this);
  return m_instantiationState;
}

uint8_t
AppInstanceInfo::GetOperationalState (void)
{
  NS_LOG_FUNCTION (this);
  return m_operationalState;
}

uint64_t
AppInstanceInfo::GetHostId (void)
{
  NS_LOG_FUNCTION (this);
  return m_hostId;
}


int
AppInstanceInfo::Size (void)
{
  int sz = sizeof(m_appInstanceId) +
      m_appInstanceName.length() +
      m_appInstanceDescription.length() +
      sizeof(m_appDId) +
      m_appProvider.length() +
      m_appName.length() +
      m_appSoftVersion.length() +
      m_appDVersion.length()+
      sizeof(m_appPkgId)+
      m_contextId.length()+
      sizeof(m_instantiationState)+
      sizeof(m_operationalState);
  NS_LOG_FUNCTION (this << sz);
  return sz;
}
} // namespace ns3
