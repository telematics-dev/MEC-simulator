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

#ifndef MEC_ENTITY_OSS_H
#define MEC_ENTITY_OSS_H

#include <string.h>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include <list>
#include "mec-entity.h"
#include "mec-new-types.h"
#include "ns3/mec-data.h"
#include "ns3/mec-message.h"
#include "mec-entity-ualcmp.h"
#include "mec-entity-meo.h"
#include "mec-delay-model.h"


namespace ns3 {

class UserEquipment;
class UserApplicationLcmProxy;
class MultiaccessEdgeOrchestrator;
class DeleteAppContextResponse;
class CreateAppContextRequest;
class DeleteAppContextRequest;
class CreateAppContextResponse;
class CreateAppInstanceIdentifierResponse;
class OnboardAppPkgResponse;
class CreateAppInstanceIdentifierRequest;
class UpdateAppContextNotification;


class OperationsSupportSystem : public MecEntity
{
public:
  static TypeId GetTypeId (void);

  OperationsSupportSystem ();
  virtual ~OperationsSupportSystem ();

  Ptr<MultiaccessEdgeOrchestrator> GetMeo (void);
  void SetMeo (Ptr<MultiaccessEdgeOrchestrator> meo);
  Ptr<UserApplicationLcmProxy> GetUalcmp (void);
  void SetUalcmp (Ptr<UserApplicationLcmProxy> ualcmp);


// UALCMP Messages
  void ForwardCreateAppContextRequest(Ptr<CreateAppContextRequest> request);
  void ForwardCreateAppContextResponse(Ptr<CreateAppContextResponse> response);

  void ForwardDeleteAppContextRequest(Ptr<DeleteAppContextRequest> request);
  void ForwardDeleteAppContextResponse(Ptr<DeleteAppContextResponse> response);

  void ForwardUpdateAppContextNotification(Ptr<UpdateAppContextNotification> notification);

private:
  Ptr<MultiaccessEdgeOrchestrator> m_meo;
  Ptr<UserApplicationLcmProxy> m_ualcmp;
};

}

#endif /* MEC_ENTITY_OSS_H */

