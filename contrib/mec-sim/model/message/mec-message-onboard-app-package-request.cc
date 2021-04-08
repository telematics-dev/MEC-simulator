/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014 TELEMATICS LAB, DEI - Politecnico di Bari
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
 *         Simona Massari - s.massari@studenti.poliba.it
 */


#include "mec-message-onboard-app-package-request.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("OnboardAppPkgRequest");

TypeId OnboardAppPkgRequest::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::OnboardAppPkgRequest")
    .SetParent<Object> ();
  return tid;
}

OnboardAppPkgRequest::OnboardAppPkgRequest ()
{
  NS_LOG_FUNCTION (this);
}

OnboardAppPkgRequest::~OnboardAppPkgRequest ()
{
  NS_LOG_FUNCTION (this);
}

void
OnboardAppPkgRequest::SetAppPkgName(std::string appPkgName)
{
  NS_LOG_FUNCTION (this << appPkgName);
  m_appPkgName = appPkgName;
}

void
OnboardAppPkgRequest::SetAppPkgVersion(std::string appPkgVersion)
{
  NS_LOG_FUNCTION (this << appPkgVersion);
  m_appPkgVersion = appPkgVersion;
}

void
OnboardAppPkgRequest::SetAppProvider(std::string appProvider)
{
  NS_LOG_FUNCTION (this << appProvider);
  m_appProvider = appProvider;
}

std::string
OnboardAppPkgRequest::GetAppPkgName()
{
  NS_LOG_FUNCTION (this);
  return m_appPkgName;
}

std::string
OnboardAppPkgRequest::GetAppPkgVersion()
{
  NS_LOG_FUNCTION (this);
  return m_appPkgVersion;
}

std::string
OnboardAppPkgRequest::GetAppProvider()
{
  NS_LOG_FUNCTION (this);
  return m_appProvider;
}

int
OnboardAppPkgRequest::Size(void)
{
  int sz = m_appPkgName.length() + m_appPkgVersion.length() + m_appProvider.length();
  return sz;
}
} // namespace ns3
