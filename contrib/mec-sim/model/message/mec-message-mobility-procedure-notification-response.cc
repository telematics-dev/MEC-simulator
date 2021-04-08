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


#include "mec-message-mobility-procedure-notification-response.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MobilityProcedureNotificationResponse");

TypeId MobilityProcedureNotificationResponse::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MobilityProcedureNotificationResponse")
    .SetParent<Object> ();
  return tid;
}

MobilityProcedureNotificationResponse::MobilityProcedureNotificationResponse ()
{
  m_respCode=0;
  NS_LOG_FUNCTION (this);
}

MobilityProcedureNotificationResponse::~MobilityProcedureNotificationResponse ()
{
  NS_LOG_FUNCTION (this);
}

void
MobilityProcedureNotificationResponse::SetSrcMecApp (Ptr<MecApp> srcMecApp)
{
  NS_LOG_FUNCTION (this << srcMecApp);
  m_srcMecApp = srcMecApp;
}

void
MobilityProcedureNotificationResponse::SetTrgMecApp(Ptr<MecApp> trgMecApp)
{
  NS_LOG_FUNCTION (this << trgMecApp);
  m_trgMecApp = trgMecApp;
}

void
MobilityProcedureNotificationResponse::SetRespCode(uint16_t respCode)
{
  NS_LOG_FUNCTION (this << respCode);
  m_respCode = respCode;
}

void
MobilityProcedureNotificationResponse::SetProblemDetails(std::string problemDetails)
{
  NS_LOG_FUNCTION (this << problemDetails);
  m_problemDetails = problemDetails;
}

Ptr<MecApp>
MobilityProcedureNotificationResponse::GetSrcMecApp (void)
{
  NS_LOG_FUNCTION (this);
  return m_srcMecApp;

}

Ptr<MecApp>
MobilityProcedureNotificationResponse::GetTrgMecApp()
{
  NS_LOG_FUNCTION (this);
  return m_trgMecApp;
}

uint16_t
MobilityProcedureNotificationResponse::GetRespCode()
{
  NS_LOG_FUNCTION (this);
  return m_respCode;
}

std::string
MobilityProcedureNotificationResponse::GetProblemDetails()
{
  NS_LOG_FUNCTION (this);
  return m_problemDetails;
}

int
MobilityProcedureNotificationResponse::Size(void)
{
  int sz = sizeof(m_srcMecApp) +
	sizeof(m_trgMecApp) +
	sizeof(m_respCode) +
	m_problemDetails.length();
  return sz;
}

} // namespace ns3
