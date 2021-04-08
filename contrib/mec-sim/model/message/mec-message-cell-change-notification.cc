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


#include "mec-message-cell-change-notification.h"
#include "ns3/log.h"

namespace ns3 {

 NS_LOG_COMPONENT_DEFINE ("CellChangeNotification");

  TypeId CellChangeNotification::GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::CellChangeNotification")
      .SetParent<Object> ();
    return tid;
  }

  CellChangeNotification::CellChangeNotification ()
  {
    m_srcBs = 0;
    m_trgBs = 0;
    m_imsi = 0;
    NS_LOG_FUNCTION (this);
  }

  CellChangeNotification::~CellChangeNotification ()
  {
    NS_LOG_FUNCTION (this);
  }


  std::string
  CellChangeNotification::GetNotificationType (void)
  {
    NS_LOG_FUNCTION (this);
    return m_notificationType;
  }

  Time
  CellChangeNotification::GetTimeStamp (void)
  {
    NS_LOG_FUNCTION (this);
    return m_timeStamp;

  }

  Ptr<BaseStation>
  CellChangeNotification::GetSrcBs (void)
  {
    NS_LOG_FUNCTION (this);
    return m_srcBs;

  }

  Ptr<BaseStation>
  CellChangeNotification::GetTrgBs (void)
  {
    NS_LOG_FUNCTION (this);
    return m_trgBs;

  }

  uint64_t
  CellChangeNotification::GetImsi (void)
  {
    NS_LOG_FUNCTION (this);
    return m_imsi;

  }

  void
  CellChangeNotification::SetNotificationType (std::string notificationType)
  {
    NS_LOG_FUNCTION (this << notificationType);
    m_notificationType = notificationType;
  }

  void
  CellChangeNotification::SetTimeStamp (Time timeStamp)
  {
    NS_LOG_FUNCTION (this << timeStamp);
    m_timeStamp = timeStamp;
  }

  void
  CellChangeNotification::SetSrcBs (Ptr<BaseStation> srcBs)
  {
    NS_LOG_FUNCTION (this << srcBs);
    m_srcBs = srcBs;
  }

  void
  CellChangeNotification::SetTrgBs (Ptr<BaseStation> trgBs)
  {
    NS_LOG_FUNCTION (this << trgBs);
    m_trgBs = trgBs;
  }

  void
  CellChangeNotification::SetImsi (uint64_t imsi)
  {
    NS_LOG_FUNCTION (this << imsi);
    m_imsi = imsi;
  }

  int
  CellChangeNotification::Size(void)
  {
    int sz = 	sizeof(m_imsi) +
	sizeof(m_timeStamp)+
	m_notificationType.length();
    return sz;
  }
} //namespace ns3
