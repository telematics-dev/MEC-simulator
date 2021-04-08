

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

#ifndef MEC_MESSAGE_INSTANTIATE_APP_REQUEST_H
#define MEC_MESSAGE_INSTANTIATE_APP_REQUEST_H


#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/mec-data.h"

namespace ns3 {

  class InstantiateAppRequest : public Object
  {
  public:
    static TypeId GetTypeId (void);


    InstantiateAppRequest ();
    virtual ~InstantiateAppRequest ();

  private:
    uint64_t m_appInstanceId;
    Ptr<VirtualResourceDescriptor> m_virtualResourceDescriptor;
    uint64_t m_selectedMECHostInfo;
    std::string m_locationConstraints;

  public:
    uint64_t GetAppInstanceId (void);
    void SetAppInstanceId (uint64_t appInstanceId);
    void SetVirtualResourceDescriptor (Ptr<VirtualResourceDescriptor> virtualResourceDescriptor);
    Ptr<VirtualResourceDescriptor> GetVirtualResourceDescriptor (void);
    void SetSelectedMECHostInfo (uint64_t hostId);
    uint64_t GetSelectedMECHostInfo(void);
    void SetLocationConstraints (std::string locationConstraints);
    std::string GetLocationConstraints(void);
    int Size(void);

  };

  }
  #endif /* MEC_MESSAGE_INSTANTIATE_APP_REQUEST_H */
