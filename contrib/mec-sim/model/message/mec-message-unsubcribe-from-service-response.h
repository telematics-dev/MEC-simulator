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

#ifndef MEC_MESSAGE_UNSUBSCRIBE_FROM_SERVICE_RESPONSE_H
#define MEC_MESSAGE_UNSUBSCRIBE_FROM_SERVICE_RESPONSE_H


#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/mec-data.h"

namespace ns3 {

class UnsubscribeFromServiceResponse : public Object
{
public:
  static TypeId GetTypeId (void);


  UnsubscribeFromServiceResponse ();
  virtual ~UnsubscribeFromServiceResponse ();

private:
  uint64_t m_appInstanceId;
  uint16_t m_respCode;
  std::string m_problemDetails;


public:
  uint64_t GetAppInstanceId (void);
  uint16_t GetRespCode (void);
  std::string GetProblemDetails (void);
  void SetAppInstanceId (uint64_t appInstanceId);
  void SetRespCode (uint16_t respCode);
  void SetProblemDetails (std::string problemDetails);

  int Size(void);
};

}

#endif /* MEC_MESSAGE_UNSUBSCRIBE_FROM_SERVICE_RESPONSE_H */

