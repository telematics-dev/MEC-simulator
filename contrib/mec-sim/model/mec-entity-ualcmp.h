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

#ifndef MEC_ENTITY_UALCMP_H
#define MEC_ENTITY_UALCMP_H

#include <string.h>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include <map>
#include "mec-entity.h"
#include "mec-new-types.h"
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-entity-ue.h"
#include "mec-entity-oss.h"
#include "mec-delay-model.h"


namespace ns3 {

class UserEquipment;
class OperationsSupportSystem;
class DeleteAppContextResponse;
class CreateAppContextRequest;
class DeleteAppContextRequest;
class CreateAppContextResponse;
class UpdateAppContextNotification;

class UserApplicationLcmProxy : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  UserApplicationLcmProxy ();
  virtual ~UserApplicationLcmProxy ();

  Ptr<OperationsSupportSystem> GetOss (void);
  void SetOss (Ptr<OperationsSupportSystem> ue);

  void ForwardCreateAppContextRequest(Ptr<CreateAppContextRequest> request);
  void ForwardCreateAppContextResponse(Ptr<CreateAppContextResponse> response);

  void ForwardDeleteAppContextRequest(Ptr<DeleteAppContextRequest> request);
  void ForwardDeleteAppContextResponse(Ptr<DeleteAppContextResponse> response);

  void ForwardUpdateAppContextNotification(Ptr<UpdateAppContextNotification> notification);


private:
  Ptr<OperationsSupportSystem> m_oss;
};

}

#endif /* MEC_ENTITY_UALCMP_H */

