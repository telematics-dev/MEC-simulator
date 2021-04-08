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

#ifndef MEC_ENTITY_CONTAINER_H
#define MEC_ENTITY_CONTAINER_H

#include <ns3/mec-entity.h>
#include <stdint.h>
#include <vector>
#include <string.h>
#include <ns3/ptr.h>

namespace ns3 {

class MecEntity;

class MecEntityContainer : public Object
{
public:
  MecEntityContainer ();

  MecEntityContainer (Ptr<MecEntity> mecEntity);

  MecEntityContainer (std::string name);

  typedef std::vector<Ptr<MecEntity> >::const_iterator Iterator;

  Iterator Begin (void) const;

  Iterator End (void) const;

  uint32_t GetN (void) const;

  Ptr<MecEntity> Get (uint32_t i) const;

  void Add (MecEntityContainer other);

  void Add (Ptr<MecEntity> application);

  void Add (std::string name);

  bool IsInContainer(Ptr<MecEntity> mecEntity);

private:
  std::vector<Ptr<MecEntity> > m_mecEntities;
};

}

#endif /* MEC_ENTITY_CONTAINER_H */

