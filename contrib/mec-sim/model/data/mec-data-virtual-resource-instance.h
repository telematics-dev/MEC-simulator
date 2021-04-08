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

#ifndef MEC_DATA_VIRTUAL_RESOURCE_INSTANCE_H
#define MEC_DATA_VIRTUAL_RESOURCE_INSTANCE_H


#include <ns3/core-module.h>
#include <list>
#include "mec-data-virtual-resource-descriptor.h"


namespace ns3 {

class VirtualResourceInstance : public Object
{
public:
  static TypeId GetTypeId (void);

  VirtualResourceInstance ();
  virtual ~VirtualResourceInstance ();

private:
  uint64_t m_virResInstId;
  Ptr<VirtualResourceDescriptor> m_virtualResource;
  uint64_t m_hostId;
  class UserData : public Object
  {
  private:
      double m_size;
  public:
      static TypeId GetTypeId (void);

      UserData ();
      virtual ~UserData ();
      void SetSize (double sz);
      double GetSize (void);
  };
  Ptr<UserData> m_userData;
  uint8_t m_allocationType;

public:
  void CreateUserData (double sz);
  uint64_t GetVirResInstId(void);
  Ptr<VirtualResourceDescriptor> GetVirtualResource(void);
  uint64_t GetHostId(void);
  uint8_t GetAllocationType (void);

  void SetVirResInstId(uint64_t virResInstId);
  void SetVirtualResource(Ptr<VirtualResourceDescriptor> virtualResource);
  void SetHostId(uint64_t hostId);
  void SetAllocationType (uint8_t allocationType);

  int Size (void);
};

}

#endif /* MEC_DATA_VIRTUAL_RESOURCE_INSTANCE_H */

