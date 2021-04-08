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


#include "mec-data-app-package-info.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AppPkgInfo");

TypeId AppPkgInfo::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AppPkgInfo")
    .SetParent<Object> ();
  return tid;
}

AppPkgInfo::AppPkgInfo ()
{
  m_onboardingState=0;
  m_operationalState=0;
  m_usageState=0;
  NS_LOG_FUNCTION (this);
}

AppPkgInfo::~AppPkgInfo ()
{
  NS_LOG_FUNCTION (this);
}

void
AppPkgInfo::SetAppPkgId(uint64_t appPkgId)
{
  NS_LOG_FUNCTION (this << appPkgId);
  m_appPkgId = appPkgId;
}

void
AppPkgInfo::SetAppDId(uint64_t appDId)
{
  NS_LOG_FUNCTION (this << appDId);
  m_appDId = appDId;
}

void
AppPkgInfo::SetAppProvider(std::string appProvider)
{
  NS_LOG_FUNCTION (this << appProvider);
  m_appProvider = appProvider;
}

void
AppPkgInfo::SetAppName(std::string appName)
{
  NS_LOG_FUNCTION (this << appName);
  m_appName = appName;
}

void
AppPkgInfo::SetSoftwareVersion(std::string appSoftwareVersion)
{
  NS_LOG_FUNCTION (this << appSoftwareVersion);
  m_appSoftwareVersion = appSoftwareVersion;
}

void
AppPkgInfo::SetAppDVersion(std::string appDVersion)
{
  NS_LOG_FUNCTION (this << appDVersion);
  m_appDVersion = appDVersion;
}

void
AppPkgInfo::SetChecksum(std::string checksum)
{
  NS_LOG_FUNCTION (this << checksum);
  m_checksum = checksum;
}

void
AppPkgInfo::SetOnboardingState(uint8_t onboardingState)
{
  NS_LOG_FUNCTION (this << onboardingState);
  m_onboardingState = onboardingState;
}

void
AppPkgInfo::SetOperationalState(bool operationalState)
{
  NS_LOG_FUNCTION (this << operationalState);
  m_operationalState = operationalState;
}

void
AppPkgInfo::SetUsageState(bool usageState)
{
  NS_LOG_FUNCTION (this << usageState);
  m_usageState = usageState;
}

void
AppPkgInfo::SetAppD(Ptr<AppD> appD)
{
  NS_LOG_FUNCTION (this << appD);
  m_appD = appD;
}

uint64_t
AppPkgInfo::GetAppPkgId()
{
  return m_appPkgId;
}

uint64_t
AppPkgInfo::GetAppDId()
{
  return m_appDId;
}

std::string
AppPkgInfo::GetAppProvider()
{
  return m_appProvider;
}

std::string
AppPkgInfo::GetAppName()
{
  return m_appName;
}

std::string
AppPkgInfo::GetSoftwareVersion()
{
  return m_appSoftwareVersion;
}

std::string
AppPkgInfo::GetDVersion()
{
  return m_appDVersion;
}

std::string
AppPkgInfo::GetChecksum()
{
  return m_checksum;
}

uint8_t
AppPkgInfo::GetOnboardingState()
{
  return m_onboardingState;
}

bool
AppPkgInfo::GetOperationalState()
{
  return m_operationalState;
}

bool
AppPkgInfo::GetUsageState()
{
  return m_usageState;
}

Ptr<AppD>
AppPkgInfo::GetAppD()
{
  return m_appD;
}

int
AppPkgInfo::Size (void)
{
  int sz =sizeof(m_appPkgId) +
      sizeof(m_appDId) +
      m_appProvider.length() +
      m_appName.length() +
      m_appSoftwareVersion.length() +
      m_appDVersion.length() +
      m_checksum.length() +
      sizeof(m_onboardingState) +
      sizeof(m_operationalState) +
      sizeof(m_usageState) +
      sizeof(m_appD);
  return sz;
}

} // namespace ns3
