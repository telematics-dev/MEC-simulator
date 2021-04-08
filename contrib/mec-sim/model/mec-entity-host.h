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

#ifndef MEC_ENTITY_HOST_H
#define MEC_ENTITY_HOST_H

#include <string.h>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include <map>
#include "mec-entity-meo.h"
#include "mec-entity-bs.h"


namespace ns3 {
class BaseStation;
class MultiaccessEdgeOrchestrator;

class MecHostEntity : public Object
{
public:
  static TypeId GetTypeId (void);

  MecHostEntity ();
  virtual ~MecHostEntity ();

  struct LinkedBs {
    uint64_t bsId;
    double latency;
    Ptr<BaseStation> bs;
  };
  typedef std::vector<LinkedBs>::const_iterator Iterator;

  uint64_t GetId (void);
  void SetId(uint64_t id);
  Ptr<MultiaccessEdgeOrchestrator> GetMeo (void);
  void SetMeo (Ptr<MultiaccessEdgeOrchestrator> meo);
  void AddLinkedBs (uint64_t bsId, double latency, Ptr<BaseStation> bs);
  LinkedBs FindLinkedBs(uint64_t bsId);

private:
  uint64_t m_id;
  Ptr<MultiaccessEdgeOrchestrator> m_meo;
  std::vector<LinkedBs> m_linkedBsList;


};

}

#endif /* MEC_ENTITY_H */

