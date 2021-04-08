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

#ifndef MEC_MESSAGE_MOBILITY_PROCEDURE_NOTIFICATION_H
#define MEC_MESSAGE_MOBILITY_PROCEDURE_NOTIFICATION_H


#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/mec-data.h"

namespace ns3 {

class MobilityProcedureNotification : public Object
{
public:
  static TypeId GetTypeId (void);


  MobilityProcedureNotification ();
  virtual ~MobilityProcedureNotification ();

private:
  Ptr<MecApp> m_mecApp;
  uint64_t m_appInstanceId;
  uint64_t m_srcBs;
  uint64_t m_trgBs;
  uint64_t m_imsi;


public:
  uint64_t GetAppInstanceId (void);
  Ptr<MecApp> GetMecApp (void);
  uint64_t GetSrcBs (void);
  uint64_t GetTrgBs (void);
  uint64_t GetImsi (void);
  void SetAppInstanceId (uint64_t appInstanceId);
  void SetMecApp (Ptr<MecApp> mecApp);
  void SetSrcBs (uint64_t srcBs);
  void SetTrgBs (uint64_t trgBs);
  void SetImsi (uint64_t imsi);

  int Size(void);
};

}
#endif /* MEC_MESSAGE_MOBILITY_PROCEDURE_NOTIFICATION_H */
