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


#include "mec-message-mobility-procedure-notification.h"
#include "ns3/log.h"

namespace ns3 {

 NS_LOG_COMPONENT_DEFINE ("MobilityProcedureNotification");

  TypeId MobilityProcedureNotification::GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::MobilityProcedureNotification")
      .SetParent<Object> ();
    return tid;
  }

  MobilityProcedureNotification::MobilityProcedureNotification ()
  {
    m_srcBs = 0;
    m_trgBs = 0;
    m_imsi = 0;
    m_appInstanceId=0;
    NS_LOG_FUNCTION (this);
  }

  MobilityProcedureNotification::~MobilityProcedureNotification ()
  {
    NS_LOG_FUNCTION (this);
  }

  uint64_t
  MobilityProcedureNotification::GetAppInstanceId (void)
  {
    NS_LOG_FUNCTION (this);
    return m_appInstanceId;
  }

  Ptr<MecApp>
  MobilityProcedureNotification::GetMecApp (void)
  {
    NS_LOG_FUNCTION (this);
    return m_mecApp;

  }


  uint64_t
  MobilityProcedureNotification::GetSrcBs (void)
  {
    NS_LOG_FUNCTION (this);
    return m_srcBs;

  }

  uint64_t
  MobilityProcedureNotification::GetTrgBs (void)
  {
    NS_LOG_FUNCTION (this);
    return m_trgBs;

  }

  uint64_t
  MobilityProcedureNotification::GetImsi (void)
  {
    NS_LOG_FUNCTION (this);
    return m_imsi;

  }

  void
  MobilityProcedureNotification::SetAppInstanceId (uint64_t appInstanceId)
  {
    NS_LOG_FUNCTION (this << appInstanceId);
    m_appInstanceId = appInstanceId;
  }

  void
  MobilityProcedureNotification::SetMecApp (Ptr<MecApp> mecApp)
  {
    NS_LOG_FUNCTION (this << mecApp);
    m_mecApp = mecApp;
  }


  void
  MobilityProcedureNotification::SetSrcBs (uint64_t srcBs)
  {
    NS_LOG_FUNCTION (this << srcBs);
    m_srcBs = srcBs;
  }

  void
  MobilityProcedureNotification::SetTrgBs (uint64_t trgBs)
  {
    NS_LOG_FUNCTION (this << trgBs);
    m_trgBs = trgBs;
  }

  void
  MobilityProcedureNotification::SetImsi (uint64_t imsi)
  {
    NS_LOG_FUNCTION (this << imsi);
    m_imsi = imsi;
  }

  int
  MobilityProcedureNotification::Size(void)
  {
    int sz = sizeof(m_srcBs) +
	sizeof(m_trgBs) +
	sizeof(m_imsi) +
	sizeof(m_appInstanceId);
    return sz;
  }
} //namespace ns3
