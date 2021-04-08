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


#include "mec-message-update-app-context-notification.h"

#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("UpdateAppContextNotification");

TypeId UpdateAppContextNotification::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::UpdateAppContextNotification")
    .SetParent<Object> ();
  return tid;
}

UpdateAppContextNotification::UpdateAppContextNotification ()
{
  NS_LOG_FUNCTION (this);
}

UpdateAppContextNotification::~UpdateAppContextNotification ()
{
  NS_LOG_FUNCTION (this);
}

void
UpdateAppContextNotification::SetAppContext(Ptr<AppContext> appContext)
{
  NS_LOG_FUNCTION (this << appContext);
  m_appContext = appContext;
}

Ptr<AppContext>
UpdateAppContextNotification::GetAppContext()
{
  NS_LOG_FUNCTION (this);
  return m_appContext;
}

int
UpdateAppContextNotification::Size (void)
{
  int sz = m_appContext->Size();
  return sz;
}
} // namespace ns3
