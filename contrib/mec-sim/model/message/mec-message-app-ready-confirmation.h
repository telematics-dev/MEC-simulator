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

#ifndef MEC_MESSAGE_APP_READY_CONFIRMATION_H
#define MEC_MESSAGE_APP_READY_CONFIRMATION_H


#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/mec-data.h"


namespace ns3 {

  class AppReadyConfirmation : public Object
  {
  public:
    static TypeId GetTypeId (void);


    AppReadyConfirmation ();
    virtual ~AppReadyConfirmation ();

  private:
    uint64_t m_mecAppId;
    std::string m_indication;


  public:
    uint64_t GetMecAppId (void);
    std::string GetIndication (void);
    void SetMecAppId (uint64_t mecAppId);
    void SetIndication (std::string indication);

    int Size (void);

  };

  }
  #endif /* MEC_MESSAGE_APP_READY_CONFIRMATION_H */
