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

#ifndef MEC_HOST_CONTAINER_H
#define MEC_HOST_CONTAINER_H

#include <ns3/mec-entity-host.h>
#include <stdint.h>
#include <vector>
#include <string.h>
#include <ns3/ptr.h>

namespace ns3 {

class MecHostEntity;

class MecHostContainer : public Object
{
public:
  static TypeId GetTypeId (void);

  MecHostContainer ();
  virtual ~MecHostContainer ();


  MecHostContainer (Ptr<MecHostEntity> mecEntity);

  MecHostContainer (std::string name);

  typedef std::vector<Ptr<MecHostEntity> >::const_iterator Iterator;

  Iterator Begin (void) const;

  Iterator End (void) const;

  uint64_t GetN (void) const;

  Ptr<MecHostEntity> Get (uint64_t i) const;

  void Add (MecHostContainer other);

  void Add (Ptr<MecHostEntity> application);

  void Add (std::string name);

  Ptr<MecHostEntity> Find (uint64_t id);


private:
  std::vector<Ptr<MecHostEntity> > m_mecHosts;
};

}

#endif /* MEC_ENTITY_CONTAINER_H */

