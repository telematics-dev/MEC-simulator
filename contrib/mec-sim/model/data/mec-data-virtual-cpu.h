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

#ifndef MEC_DATA_VIRTUAL_CPU_H
#define MEC_DATA_VIRTUAL_CPU_H


#include <ns3/core-module.h>


namespace ns3 {

  class VirtualCpu : public Object
  {
  public:
    static TypeId GetTypeId (void);
    VirtualCpu ();
    VirtualCpu (std::string cpuArchitecture,
		uint8_t numVirtualCpu,
		double cpuClock);
    virtual ~VirtualCpu ();

  private:
    std::string m_cpuArchitecture;
    uint8_t m_numVirtualCpu;
    double m_cpuClock;

  public:
    void SetCpuArchitecture (std::string cpuArchitecture);
    std::string GetCpuArchitecture (void);
    void SetNumVirtualCpu (uint8_t numVirtualCpu);
    uint8_t GetNumVirtualCpu (void);
    void SetCpuClock (double cpuClock);
    double GetCpuClock (void);
    int Size (void);
  };


}

#endif /* MEC_DATA_VIRTUAL_CPU_H */

