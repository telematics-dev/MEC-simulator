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

#ifndef MEC_ENTITY_H
#define MEC_ENTITY_H

#include <string.h>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include <map>
#include "mec-delay-model.h"
#include "logging-to-file.h"

namespace ns3 {
class LoggingToFile;

class MecEntity : public Object
{
public:
  static TypeId GetTypeId (void);

  MecEntity ();
  virtual ~MecEntity ();

  Ptr<Object> GetNode (void);
  void SetNode(Ptr<Object> node);
  uint64_t GetId (void);
  void SetId(uint64_t id);
  void SetDelayModel (Ptr<MecDelayModel> delay);
  Ptr<MecDelayModel> GetDelayModel (void);
  void SetLog(Ptr<LoggingToFile> log);
  Ptr<LoggingToFile> GetLog(void);

private:
  Ptr<Object> m_node;
  uint64_t m_id;
  Ptr<MecDelayModel> m_delayModel;
  Ptr<LoggingToFile> m_log;

};

}

#endif /* MEC_ENTITY_H */

