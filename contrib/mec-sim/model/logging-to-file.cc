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

#include <ns3/simulator.h>
#include "logging-to-file.h"
#include <ns3/log.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LoggingToFile");

TypeId LoggingToFile::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LoggingToFile")
    .SetParent<Object> ();
  return tid;
}

LoggingToFile::LoggingToFile (double ue)
{
  position_file.open("mec-sim_UE_"+ std::to_string(int(ue)) +"_position.csv");
  position_file << "Time; IMSI; X; Y; Z\n";

  task_file.open("mec-sim_UE_"+ std::to_string(int(ue)) +"_task.csv");
  task_file << "Time; IMSI; ContextId; HostId; E2E; Processing\n";

  host_file.open("mec-sim_UE_"+ std::to_string(int(ue)) +"_host.csv");
  host_file << "Time; HostId; CPU; Memory; Storage; N_VM\n";
}

LoggingToFile::~LoggingToFile ()
{
  NS_LOG_FUNCTION (this);
  position_file.close();
  task_file.close();
  host_file.close();
}

void
LoggingToFile::PositionChange(uint64_t imsi, Vector pos)
{
  position_file << Now().GetSeconds() << "; " << imsi << "; " << pos.x << "; " << pos.y <<"; " << pos.z <<"\n";
}

void
LoggingToFile::TaskDelay(uint64_t imsi, std::string ContextId, uint64_t appDiD, uint64_t hostId, double e2e, double processing)
{
  task_file << Now().GetSeconds() << "; " << imsi << "; " << appDiD << "; "<< ContextId << "; " << hostId <<"; " << e2e <<"; "<< processing <<"\n";}

void
LoggingToFile::HostResource(uint64_t hostId, double cpu, double memory, double storage, int16_t n)
{
  host_file << Now().GetSeconds() << "; " << hostId << "; " << cpu*100 << "; " << memory*100 <<"; " << storage*100 <<"; " << n<<"\n";

}

}
