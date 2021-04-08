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
#include "mec-host-container.h"



namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MecHostContainer");


TypeId MecHostContainer::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MecHostContainer")
    .SetParent<Object> ();
  return tid;
}

MecHostContainer::MecHostContainer ()
{
}

MecHostContainer::~MecHostContainer ()
{
  NS_LOG_FUNCTION (this);
}

MecHostContainer::MecHostContainer (Ptr<MecHostEntity> entity)
{
  m_mecHosts.push_back (entity);
}

MecHostContainer::MecHostContainer (std::string name)
{
  Ptr<MecHostEntity> entity = Names::Find<MecHostEntity> (name);
  m_mecHosts.push_back (entity);
}


MecHostContainer::Iterator
MecHostContainer::Begin (void) const
{
  return m_mecHosts.begin ();
}
MecHostContainer::Iterator
MecHostContainer::End (void) const
{
  return m_mecHosts.end ();
}

uint64_t
MecHostContainer::GetN (void) const
{
  return m_mecHosts.size ();
}

Ptr<MecHostEntity>
MecHostContainer::Get (uint64_t i) const
{
  return m_mecHosts[i];
}

void
MecHostContainer::Add (MecHostContainer other)
{
  for (Iterator i = other.Begin (); i != other.End (); i++)
    {
      m_mecHosts.push_back (*i);
    }
}
void
MecHostContainer::Add (Ptr<MecHostEntity> entity)
{
  m_mecHosts.push_back (entity);
}
void
MecHostContainer::Add (std::string name)
{
  Ptr<MecHostEntity> entity = Names::Find<MecHostEntity> (name);
  m_mecHosts.push_back (entity);
}

Ptr<MecHostEntity>
MecHostContainer::Find (uint64_t id)
{
  for (Iterator i = Begin (); i != End (); i++)
    {
      if((*i)->GetId() == id)
        {
          return (*i);
        }
    }
  return 0;
}


}

