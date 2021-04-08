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

#ifndef APP_REPOSITORY_H
#define APP_REPOSITORY_H

#include <ns3/ptr.h>
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include <string>
#include <list>
#include "mec-entity-ue.h"

namespace ns3 {

class UserEquipment;

class AppRepository : public Object
{
public:
  static TypeId GetTypeId (void);
  AppRepository (void);
  ~AppRepository (void);

  std::list <Ptr<AppD>> CreateList(void);
  Ptr<AppD> NewApp (void);
  Ptr<AppD> FindApp (std::string appPkgName, std::string appPkgVersion);
  std::pair<Ptr<AppD>, int16_t> FindApp (uint64_t appDId);
  void TraceReader(std::string filename, Ptr<UserEquipment> ue);
private:
  std::list <Ptr<AppD>> m_appRepository;
};

} //namespace ns3

#endif /* APP_REPOSITORY_H */
