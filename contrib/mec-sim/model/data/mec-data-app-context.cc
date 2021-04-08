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


#include "mec-data-app-context.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AppContext");

TypeId AppContext::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AppContext")
    .SetParent<Object> ();
  return tid;
}

AppContext::AppContext ()
{
  m_appDId=0;
  NS_LOG_FUNCTION (this);
}

AppContext::~AppContext ()
{
  NS_LOG_FUNCTION (this);
}

void
AppContext::SetContextId (std::string contextId)
{
  NS_LOG_FUNCTION (this << contextId);
  m_contextId = contextId;
}

void
AppContext::SetAppDId (uint64_t appDId)
{
  NS_LOG_FUNCTION (this << appDId);
  m_appDId = appDId;
}

void
AppContext::SetAppName (std::string appName)
{
  NS_LOG_FUNCTION (this << appName);
  m_appName = appName;
}

void
AppContext::SetAppProvider(std::string appProvider)
{
  NS_LOG_FUNCTION (this << appProvider);
  m_appProvider = appProvider;
}

void
AppContext::SetAppSoftwareVersion (std::string appSoftwareVersion)
{
  NS_LOG_FUNCTION (this << appSoftwareVersion);
  m_appSoftwareVersion = appSoftwareVersion;
}

void
AppContext::SetAppDVersion (std::string appDVersion)
{
  NS_LOG_FUNCTION (this << appDVersion);
  m_appDVersion = appDVersion;
}

void
AppContext::SetAppDescription (std::string appDescription)
{
  NS_LOG_FUNCTION (this << appDescription);
  m_appDescription = appDescription;
}

void
AppContext::SetAppPackageSource(std::string appPackageSource)
{
  NS_LOG_FUNCTION (this);
  m_appPackageSource = appPackageSource;
}

void
AppContext::SetReferenceUri(Ptr<MecApp> referenceUri)
{
  NS_LOG_FUNCTION (this << referenceUri);
  m_referenceUri = referenceUri;
}

void
AppContext::SetCallbackReference(Ptr<UserEquipment> callbackReference)
{
  NS_LOG_FUNCTION (this << callbackReference);
  m_callbackReference = callbackReference;
}

std::string
AppContext::GetContextId()
{
  NS_LOG_FUNCTION (this);
  return m_contextId;
}

uint64_t
AppContext::GetAppDId()
{
  NS_LOG_FUNCTION (this);
  return m_appDId;
}

std::string
AppContext::GetAppName()
{
  NS_LOG_FUNCTION (this);

  return m_appName;
}

std::string
AppContext::GetAppProvider()
{
  NS_LOG_FUNCTION (this);
  return m_appProvider;
}

std::string
AppContext::GetAppSoftwareVersion()
{
  NS_LOG_FUNCTION (this);
  return m_appSoftwareVersion;
}
std::string
AppContext::GetAppDVersion()
{
  NS_LOG_FUNCTION (this);
  return m_appDVersion;
}
std::string
AppContext::GetAppDescription()
{
  NS_LOG_FUNCTION (this);
  return m_appDescription;
}

std::string
AppContext::GetAppPackageSource()
{
  NS_LOG_FUNCTION (this);

  return m_appPackageSource;
}

Ptr<UserEquipment>
AppContext::GetCallbackReference (void)
{
  NS_LOG_FUNCTION (this);
  return m_callbackReference;
}

Ptr<MecApp>
AppContext::GetReferenceUri (void)
{
  NS_LOG_FUNCTION (this);
  return m_referenceUri;
}

int
AppContext::Size (void)
{
  int sz =m_contextId.length() +
      sizeof(m_appDId) +
      m_appName.length() +
      m_appProvider.length() +
      m_appSoftwareVersion.length() +
      m_appDVersion.length() +
      m_appDescription.length() +
      m_appPackageSource.length()+
      sizeof(m_referenceUri) +
      sizeof(m_callbackReference);
  return sz;
}
} // namespace ns3
