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

#ifndef MEC_MESSAGE_CREATE_APP_CONTEXT_REQUEST_H
#define MEC_MESSAGE_CREATE_APP_CONTEXT_REQUEST_H

#include <ns3/message.h>
#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/mec-data.h"

namespace ns3 {
  class AppContext;

class CreateAppContextRequest : public Message
{
  public:
    static TypeId GetTypeId (void);


    CreateAppContextRequest ();
    virtual ~CreateAppContextRequest ();

  private:
    Ptr<AppContext> m_appContext;

  public:
     Ptr<AppContext> GetAppContext (void);
     void SetAppContext (Ptr<AppContext> m_appContext);
     int Size (void) ;
};

}
#endif /* MEC_MESSAGE_CREATE_APP_CONTEXT_REQUEST_H */

