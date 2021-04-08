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
#include "mec-entity.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecEntity");

TypeId MecEntity::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecEntity")
    .SetParent<Object> ();
  return tid;
}

MecEntity::MecEntity ()
{
  m_node = 0;
  m_id = 0;
  NS_LOG_FUNCTION (this);
}

MecEntity::~MecEntity ()
{
  NS_LOG_FUNCTION (this);
}

Ptr<Object>
MecEntity::GetNode (void)
{
  NS_LOG_FUNCTION (this );
  return m_node;
}

void
MecEntity::SetNode(Ptr<Object> node)
{
  m_node = node;
}

uint64_t
MecEntity::GetId (void)
{
  NS_LOG_LOGIC (this->GetInstanceTypeId() << "Id:" << m_id);
  return m_id;
}

void
MecEntity::SetId(uint64_t id)
{
  NS_LOG_LOGIC (this << id);
  m_id = id;
}

void
MecEntity::SetDelayModel (Ptr<MecDelayModel> delay)
{
  NS_LOG_FUNCTION (this << delay);
  m_delayModel = delay;
}

Ptr<MecDelayModel>
MecEntity::GetDelayModel()
{
  NS_LOG_FUNCTION (this);
  if(m_delayModel == 0)
    {
      Ptr<MecDelayModel> delayModel = this->GetNode()->GetObject<MecDelayModel>();
      if(delayModel==0)
        {
          NS_LOG_ERROR (this << "set DelayModel pointer");
          return delayModel;
        }
      else
        {
          return delayModel;
        }
    }
  else
    {
      return m_delayModel;
    };
}

void
MecEntity::SetLog(Ptr<LoggingToFile> log)
{
  NS_LOG_FUNCTION (this << log);
  m_log = log;
}

Ptr<LoggingToFile>
MecEntity::GetLog(void)
{
  NS_LOG_FUNCTION (this);
  return m_log;
}

}

