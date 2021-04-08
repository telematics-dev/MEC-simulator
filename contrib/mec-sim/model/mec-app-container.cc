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


#include "ns3/names.h"
#include "ns3/log.h"
#include "mec-app-container.h"

NS_LOG_COMPONENT_DEFINE ("MecAppContainer");


namespace ns3 {

TypeId MecAppContainer::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecAppContainer")
    .SetParent<Object> ();
  return tid;
}

MecAppContainer::MecAppContainer ()
{
}

MecAppContainer::~MecAppContainer ()
{
  NS_LOG_FUNCTION (this);
}

MecAppContainer::MecAppContainer (Ptr<MecApp> entity)
{
  m_mecApps.push_back (entity);
}


MecAppContainer::Iterator
MecAppContainer::Begin (void) const
{
  return m_mecApps.begin ();
}
MecAppContainer::Iterator
MecAppContainer::End (void) const
{
  return m_mecApps.end ();
}

uint64_t
MecAppContainer::GetN (void) const
{
  return m_mecApps.size ();
}

Ptr<MecApp>
MecAppContainer::Get (uint64_t i) const
{
  return m_mecApps[i];
}

void
MecAppContainer::Add (MecAppContainer other)
{
  for (Iterator i = other.Begin (); i != other.End (); i++)
    {
      m_mecApps.push_back (*i);
    }
}
void
MecAppContainer::Add (Ptr<MecApp> entity)
{
  m_mecApps.push_back (entity);
}

Ptr<Object>
MecAppContainer::GetNode (void)
{
  NS_LOG_FUNCTION (this );
  return m_node;
}

void
MecAppContainer::SetNode(Ptr<Object> node)
{
  m_node = node;
}
}

