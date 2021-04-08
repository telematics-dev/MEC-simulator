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

#ifndef MEC_DATA_APP_CONTEXT_H
#define MEC_DATA_APP_CONTEXT_H


#include <string>
#include <ns3/core-module.h>
#include <list>
#include "mec-data-app-descriptor.h"
#include "ns3/mec-entity-ue.h"
#include "ns3/mec-entity-app.h"


namespace ns3 {

class MecApp;
class UserEquipment;

class AppContext : public Object
{
public:
  static TypeId GetTypeId (void);

  AppContext ();
  virtual ~AppContext ();

private:
  std::string m_contextId;
  uint64_t    m_appDId;
  std::string m_appName;
  std::string m_appProvider;
  std::string m_appSoftwareVersion;
  std::string m_appDVersion;
  std::string m_appDescription;
  std::string m_appPackageSource;
  Ptr<MecApp> m_referenceUri;
  Ptr<UserEquipment> m_callbackReference;

public:
  std::string GetContextId (void);
  uint64_t GetAppDId (void);
  std::string GetAppName (void);
  std::string GetAppProvider (void);
  std::string GetAppSoftwareVersion (void);
  std::string GetAppDVersion (void);
  std::string GetAppDescription (void);
  std::string GetAppPackageSource (void);
  Ptr<MecApp> GetReferenceUri (void);
  Ptr<UserEquipment> GetCallbackReference(void);

  void SetContextId (std::string contextId);
  void SetAppDId (uint64_t appDId);
  void SetAppName (std::string appName);
  void SetAppProvider (std::string appProvider);
  void SetAppSoftwareVersion (std::string appSoftwareVersion);
  void SetAppDVersion (std::string appDVersion);
  void SetAppDescription (std::string appDescription);
  void SetAppPackageSource (std::string appPackageSource);
  void SetReferenceUri (Ptr<MecApp> referenceUri);
  void SetCallbackReference (Ptr<UserEquipment> callbackReference);
  int Size (void);
};

}

#endif /* MEC_DATA_APP_CONTEXT_H */

