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


#include "mec-message-disable-app-package-request.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DisableAppPkgRequest");

TypeId DisableAppPkgRequest::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DisableAppPkgRequest")
    .SetParent<Object> ();
  return tid;
}

DisableAppPkgRequest::DisableAppPkgRequest ()
{
  NS_LOG_FUNCTION (this);
}

DisableAppPkgRequest::~DisableAppPkgRequest ()
{
  NS_LOG_FUNCTION (this);
}

void
DisableAppPkgRequest::SetAppPkgId(uint64_t appPkgId)
{
  NS_LOG_FUNCTION (this << appPkgId);
  m_appPkgId = appPkgId;
}

uint64_t
DisableAppPkgRequest::GetAppPkgId()
{
  NS_LOG_FUNCTION (this);
  return m_appPkgId;
}

} //namespace ns3
