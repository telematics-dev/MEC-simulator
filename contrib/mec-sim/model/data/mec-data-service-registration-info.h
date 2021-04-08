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

#ifndef MEC_DATA_SERVICE_REGISTRATION_INFO_H
#define MEC_DATA_SERVICE_REGISTRATION_INFO_H


#include <ns3/core-module.h>
#include "ns3/mec-entity-app.h"
#include "ns3/mec-entity.h"


namespace ns3 {

class MecApp;

class ServiceRegistrationInfo : public Object
{
public:
  static TypeId GetTypeId (void);

  ServiceRegistrationInfo ();
  virtual ~ServiceRegistrationInfo ();

private:
  std::string m_subscriptionType;
  uint64_t m_appInstanceId;
  uint64_t m_mepId;
  uint64_t m_imsi;
  Ptr<MecApp> m_mecApp;
  Ptr<MecEntity> m_callback;

public:
  std::string GetSubscriptionType (void);
  uint64_t GetAppInstanceId (void);
  uint64_t GetImsi (void);
  uint64_t GetmepId (void);
  Ptr<MecApp> GetMecApp(void);
  Ptr<MecEntity> GetCallback(void);

  void SetCallback(Ptr<MecEntity> callback);
  void SetSubscriptionType (std::string subscriptionType);
  void SetAppInstanceId (uint64_t appInstanceId);
  void SetImsi (uint64_t imsi);
  void SetMepId (uint64_t mepId);
  void SetMecApp (Ptr<MecApp> mecApp);

  int Size (void);
};

}

#endif /* MEC_DATA_AMS_REGISTRATION_INFO_H */

