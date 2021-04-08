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


#include "mec-message-app-ready-confirmation-response.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AppReadyConfirmationResponse");

TypeId AppReadyConfirmationResponse::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AppReadyConfirmationResponse")
    .SetParent<Object> ();
  return tid;
}

AppReadyConfirmationResponse::AppReadyConfirmationResponse ()
{
  m_respCode=0;
  NS_LOG_FUNCTION (this);
}

AppReadyConfirmationResponse::~AppReadyConfirmationResponse ()
{
  NS_LOG_FUNCTION (this);
}

int16_t
AppReadyConfirmationResponse::GetRespCode()
{
  NS_LOG_FUNCTION (this);
  return m_respCode;
}

void
AppReadyConfirmationResponse::SetRespCode (int16_t respCode)
{
  NS_LOG_FUNCTION (this << respCode);
  m_respCode=respCode;
}

int
AppReadyConfirmationResponse::Size (void)
{
  int sz = sizeof(m_respCode);
  return sz;
}

} //namespace ns3
