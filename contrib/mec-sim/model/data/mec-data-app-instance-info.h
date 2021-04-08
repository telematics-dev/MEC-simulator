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

#ifndef MEC_DATA_APP_INSTANCE_INFO_H
#define MEC_DATA_APP_INSTANCE_INFO_H


#include <ns3/core-module.h>
#include <list>


namespace ns3 {

class AppInstanceInfo : public Object
{
public:
  static TypeId GetTypeId (void);

  AppInstanceInfo ();
  virtual ~AppInstanceInfo ();

private:
  uint64_t    m_appInstanceId;

  std::string m_appInstanceName;
  std::string m_appInstanceDescription;
  uint64_t    m_appDId;
  std::string m_appProvider;
  std::string m_appName;
  std::string m_appSoftVersion;
  std::string m_appDVersion;
  uint64_t    m_appPkgId;
  std::string m_contextId;
  bool        m_instantiationState;
  uint8_t     m_operationalState;
  uint64_t    m_hostId;


public:
  std::string GetContextId (void);
  uint64_t GetAppInstanceId (void);
  std::string GetAppInstanceName (void);
  std::string GetAppInstanceDescription (void);
  uint64_t GetAppDId (void);
  std::string GetAppProvider (void);
  std::string GetAppName (void);
  std::string GetAppSoftVersion (void);
  std::string GetAppDVersion (void);
  uint64_t GetAppPkgId (void);
  bool GetInstantiationState (void);
  uint8_t GetOperationalState (void);
  uint64_t GetHostId (void);

  void SetAppInstanceId (uint64_t appInstanceId);
  void SetContextId (std::string contextId);
  void SetAppInstanceName (std::string appInstanceName);
  void SetAppInstanceDescription (std::string appInstanceDescription);
  void SetAppDId (uint64_t appDId);
  void SetAppProvider (std::string appProvider);
  void SetAppName (std::string appName);
  void SetAppSoftVersion (std::string appSoftVersion);
  void SetAppDVersion (std::string appDVersion);
  void SetAppPkgId (uint64_t appPkgId);
  void SetInstantiationState (bool instantiationState);
  void SetOperationalState (uint8_t operationalState);
  void SetHostId(uint64_t hostId);

  int Size (void);
};

}

#endif /* MEC_DATA_APP_INSTANCE_INFO_H */

