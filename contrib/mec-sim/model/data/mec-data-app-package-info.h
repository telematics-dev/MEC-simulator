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

#ifndef MEC_DATA_APP_PACKAGE_INFO_H
#define MEC_DATA_APP_PACKAGE_INFO_H


#include <ns3/core-module.h>
#include <list>
#include "mec-data-app-descriptor.h"

namespace ns3 {

class AppPkgInfo : public Object
{
public:
  static TypeId GetTypeId (void);

  AppPkgInfo ();
  virtual ~AppPkgInfo ();

private:
  uint64_t m_appPkgId;
  uint64_t m_appDId;
  std::string m_appProvider;
  std::string m_appName;
  std::string m_appSoftwareVersion;
  std::string m_appDVersion;
  std::string m_checksum;
  uint8_t     m_onboardingState;
  bool        m_operationalState;
  bool        m_usageState;
  Ptr<AppD>   m_appD;


public:
  uint64_t GetAppPkgId (void);
  uint64_t GetAppDId (void);
  std::string GetAppProvider (void);
  std::string GetAppName (void);
  std::string GetSoftwareVersion (void);
  std::string GetDVersion (void);
  std::string GetChecksum (void);
  uint8_t GetOnboardingState (void);
  bool GetOperationalState (void);
  bool GetUsageState (void);
  Ptr<AppD> GetAppD (void);

  void SetAppPkgId (uint64_t appPkgId);
  void SetAppDId (uint64_t appDId);
  void SetAppProvider (std::string appProvider);
  void SetAppName (std::string appName);
  void SetSoftwareVersion (std::string appSoftwareVersion);
  void SetAppDVersion (std::string appDVersion);
  void SetChecksum (std::string checksum);
  void SetOnboardingState (uint8_t onboardingState);
  void SetOperationalState (bool operationalState);
  void SetUsageState (bool usageState);

  int Size (void);
  void SetAppD (Ptr<AppD> appD);
};

}

#endif /* MEC_DATA_APP_PACKAGE_INFO_H */

