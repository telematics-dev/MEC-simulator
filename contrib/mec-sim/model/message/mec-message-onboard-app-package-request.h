/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014 TELEMATICS LAB, DEI - Politecnico di Bari
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
 *         Simona Massari - s.massari@studenti.poliba.it
 */

#ifndef MEC_MESSAGE_ONBOARD_APP_PACKAGE_REQUEST_H
#define MEC_MESSAGE_ONBOARD_APP_PACKAGE_REQUEST_H

#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/mec-data.h"


namespace ns3 {

class OnboardAppPkgRequest : public Object
{
public:
  static TypeId GetTypeId (void);


  OnboardAppPkgRequest ();
  virtual ~OnboardAppPkgRequest ();

private:
  std::string m_appPkgName;
  std::string m_appPkgVersion;
  std::string m_appProvider;

public:
   std::string GetAppPkgName (void);
   std::string GetAppPkgVersion (void);
   std::string GetAppProvider (void);
   void SetAppPkgName (std::string appPkgName);
   void SetAppPkgVersion (std::string appPkgVersion);
   void SetAppProvider (std::string appProvider);
   int Size (void);
};

}

#endif /* MEC_MESSAGE_ONBOARD_APP_PACKAGE_REQUEST_H */

