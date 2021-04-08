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

#ifndef MEC_APP_CONTAINER_H
#define MEC_APP_CONTAINER_H

#include <stdint.h>
#include <vector>
#include <string.h>
#include <ns3/ptr.h>
#include <ns3/mec-entity-app.h>

namespace ns3 {

class MecApp;

class MecAppContainer : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  MecAppContainer ();

  virtual ~MecAppContainer ();

  MecAppContainer (Ptr<MecApp> mecApp);

  MecAppContainer (std::string name);

  typedef std::vector<Ptr<MecApp> >::const_iterator Iterator;

  Iterator Begin (void) const;

  Iterator End (void) const;

  uint64_t GetN (void) const;

  Ptr<MecApp> Get (uint64_t i) const;

  void Add (MecAppContainer other);

  void Add (Ptr<MecApp> application);

  void Add (std::string name);

  Ptr<Object> GetNode (void);

  void SetNode(Ptr<Object> node);

private:
  std::vector<Ptr<MecApp> > m_mecApps;
  Ptr<Object> m_node;
};

}

#endif /* MEC_ENTITY_CONTAINER_H */

