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

#ifndef MEC_MESSAGE_MEC_APP_INSTANCE_CONFIGURATION_REQUEST_H
#define MEC_MESSAGE_MEC_APP_INSTANCE_CONFIGURATION_REQUEST_H

#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/mec-data.h"
#include "ns3/mec-entity-app.h"

namespace ns3 {

class MecApp;

class MecAppInstanceConfigurationRequest : public Object
{
public:
  static TypeId GetTypeId (void);

  MecAppInstanceConfigurationRequest ();
  virtual ~MecAppInstanceConfigurationRequest ();

private:
  Ptr<AppD> m_appD;
  Ptr<MecApp> m_mecApp;
  uint64_t m_instanceId;

public:
  Ptr<AppD> GetAppD (void);
  void SetAppD (Ptr<AppD> appD);
  Ptr<MecApp> GetMecApp (void);
  void SetMecApp (Ptr<MecApp> mecApp);
  uint64_t GetInstanceId (void);
  void SetInstanceId (uint64_t instanceId);

  int Size (void);

};

}
#endif /* MEC_MESSAGE_MEC_APP_INSTANCE_CONFIGURATION_REQUEST_H */

