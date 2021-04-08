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
#include "mec-entity-container.h"

NS_LOG_COMPONENT_DEFINE ("MecEntityContainer");


namespace ns3 {

MecEntityContainer::MecEntityContainer ()
{
}


MecEntityContainer::MecEntityContainer (Ptr<MecEntity> entity)
{
  m_mecEntities.push_back (entity);
}

MecEntityContainer::MecEntityContainer (std::string name)
{
  Ptr<MecEntity> entity = Names::Find<MecEntity> (name);
  m_mecEntities.push_back (entity);
}


MecEntityContainer::Iterator
MecEntityContainer::Begin (void) const
{
  return m_mecEntities.begin ();
}
MecEntityContainer::Iterator
MecEntityContainer::End (void) const
{
  return m_mecEntities.end ();
}

uint32_t
MecEntityContainer::GetN (void) const
{
  return m_mecEntities.size ();
}

Ptr<MecEntity>
MecEntityContainer::Get (uint32_t i) const
{
  return m_mecEntities[i];
}

void
MecEntityContainer::Add (MecEntityContainer other)
{
  for (Iterator i = other.Begin (); i != other.End (); i++)
    {
      m_mecEntities.push_back (*i);
    }
}
void
MecEntityContainer::Add (Ptr<MecEntity> entity)
{
  m_mecEntities.push_back (entity);
}
void
MecEntityContainer::Add (std::string name)
{
  Ptr<MecEntity> entity = Names::Find<MecEntity> (name);
  m_mecEntities.push_back (entity);
}

bool
MecEntityContainer::IsInContainer(Ptr<MecEntity> mecEntity)
{
  for (Iterator i = Begin (); i != End (); i++)
    {
      Ptr<MecEntity> t = *i;
      if(mecEntity->GetId() == t->GetId())
        {
          return 1;
        }
    }
  return 0;
}

}

