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

#ifndef LOGGING_TO_FILE_H
#define LOGGING_TO_FILE_H

#include <string>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include <ns3/mobility-model.h>
#include <iostream>
#include <fstream>

namespace ns3 {


class LoggingToFile : public Object
{
public:
  static TypeId GetTypeId (void);

  LoggingToFile (double ue);
  virtual ~LoggingToFile ();

  void PositionChange(uint64_t imsi, Vector pos);
  void TaskDelay(uint64_t imsi, std::string ContextId, uint64_t appDiD, uint64_t hostId, double e2e, double processing);
  void HostResource(uint64_t hostId, double cpu, double memory, double storage, int16_t n);


private:
  std::ofstream position_file;
  std::ofstream task_file;
  std::ofstream host_file;


};
}
#endif /* LOGGING_TO_FILE_H */
