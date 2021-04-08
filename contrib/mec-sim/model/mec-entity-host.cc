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


#include "ns3/log.h"
#include "ns3/simulator.h"
#include "mec-entity-host.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecHostEntity");

TypeId MecHostEntity::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecHostEntity")
    .SetParent<Object> ();
  return tid;
}

MecHostEntity::MecHostEntity ()
{
  m_id = 0;
  NS_LOG_FUNCTION (this);
}

MecHostEntity::~MecHostEntity ()
{
  NS_LOG_FUNCTION (this);
}

uint64_t
MecHostEntity::GetId (void)
{
  NS_LOG_LOGIC (this->GetInstanceTypeId() << "Id:" << m_id);
  return m_id;
}

void
MecHostEntity::SetId(uint64_t id)
{
  NS_LOG_LOGIC (this << id);
  m_id = id;
}

Ptr<MultiaccessEdgeOrchestrator>
MecHostEntity::GetMeo (void)
{
  NS_LOG_FUNCTION (this);
  return m_meo;
}

void
MecHostEntity::SetMeo (Ptr<MultiaccessEdgeOrchestrator> meo)
{
  NS_LOG_FUNCTION (this << meo);
  m_meo = meo;
}

void
MecHostEntity::AddLinkedBs (uint64_t bsId, double latency, Ptr<BaseStation> bs)
{
  NS_LOG_FUNCTION (this << bsId << latency);
  LinkedBs linkedBs;
  linkedBs.bsId = bsId;
  linkedBs.bs = bs;
  linkedBs.latency = latency;
  m_linkedBsList.push_back(linkedBs);
}

MecHostEntity::LinkedBs
MecHostEntity::FindLinkedBs(uint64_t bsId)
{
  for (Iterator i = m_linkedBsList.begin (); i != m_linkedBsList.end (); i++)
    {
      if((*i).bsId == bsId)
        {
          return (*i);
        }
    }
  LinkedBs linkedBs;
  linkedBs.bsId = 0;
  linkedBs.bs = 0;
  linkedBs.latency = 0;
  return linkedBs;
}
}

