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

#ifndef MESSAGE_H
#define MESSAGE_H


#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/mec-entity.h"

namespace ns3 {

  class Message : public Object
  {
  public:
    static TypeId GetTypeId (void);

    Message ();
    virtual ~Message ();

     Ptr<MecEntity> GetSource (void);
     void SetSource (Ptr<MecEntity> source);
     Ptr<MecEntity> GetDestination (void);
     void SetDestinantion (Ptr<MecEntity> destination);
     int Size(void);
  private:
    Ptr<MecEntity> m_source;
    Ptr<MecEntity> m_destination;

  };

  }
  #endif /* MESSAGE_H */

