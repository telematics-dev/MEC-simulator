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

#ifndef MEC_DATA_SERVICE_DESCRIPTOR_H
#define MEC_DATA_SERVICE_DESCRIPTOR_H


#include <ns3/core-module.h>


namespace ns3 {

class ServiceDescriptor : public Object
{
public:
  static TypeId GetTypeId (void);
  ServiceDescriptor ();
  virtual ~ServiceDescriptor ();

private:
  std::string m_serName;
  std::string m_serCategory;
  std::string m_version;
  std::string m_transportsSupported;

public:
  void SetSerName (std::string serName);
  std::string GetSerName (void);
  void SetSerCategory (std::string serCategory);
  std::string GetSerCategory (void);
  void SetVersion (std::string version);
  std::string GetVersion (void);
  void SetTransportsSupported (std::string transportsSupported);
  std::string GetTransportsSupported (void);
  int Size (void);
};

}

#endif /* MEC_DATA_SERVICE_DESCRIPTOR_H */

