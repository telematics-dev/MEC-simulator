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


#include "message.h"
#include "ns3/log.h"

namespace ns3 {

 NS_LOG_COMPONENT_DEFINE ("Message");

  TypeId Message::GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::Message")
      .SetParent<Object> ();
    return tid;
  }

  Message::Message ()
  {
    NS_LOG_FUNCTION (this);
  }

  Message::~Message ()
  {
    NS_LOG_FUNCTION (this);
  }

  Ptr<MecEntity>
  Message::GetSource (void)
  {
    NS_LOG_FUNCTION (this);
    return m_source;
  }

  void
  Message::SetSource (Ptr<MecEntity> source)
  {
    NS_LOG_FUNCTION (this << source);
    m_source = source;
  }


  Ptr<MecEntity>
  Message::GetDestination (void)
  {
    NS_LOG_FUNCTION (this);
    return m_destination;
  }

  void
  Message::SetDestinantion (Ptr<MecEntity> destination)
  {
    NS_LOG_FUNCTION (this << destination);
    m_destination = destination;
  }

} //namespace ns3
