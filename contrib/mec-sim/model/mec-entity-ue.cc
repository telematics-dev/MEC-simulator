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


#include "mec-entity-ue.h"
#include <ns3/log.h>
#include <ns3/simulator.h>

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("UserEquipment");

/**
 * https://comtech.vsb.cz/qualmob/sinr_lte.html
 */
static const double SinrForCqi[15] = {
  -6.7, -4.7, -2.3, 0.2, 2.4, 4.3,
  5.9, 8.1, 10.3, 11.7,
  14.1, 16.3, 18.7, 21.0, 22.7
};

TypeId UserEquipment::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::UserEquipment")
    .SetParent<Object> ();
  return tid;
}

UserEquipment::UserEquipment ()
{
  m_bs = 0;
  m_txPower=23;
  m_txAntennaGain=0;
  m_cqi = 0;
  m_handoverMargin = 200;
  NS_LOG_FUNCTION (this);
}

UserEquipment::~UserEquipment ()
{
  NS_LOG_FUNCTION (this);
}

void
UserEquipment::SetUalcmp(Ptr<UserApplicationLcmProxy> ualcmp)
{
  NS_LOG_FUNCTION (this << ualcmp);
  m_ualcmp = ualcmp;
}

Ptr<UserApplicationLcmProxy>
UserEquipment::GetUalcmp(void)
{
  NS_LOG_FUNCTION (this);
  return m_ualcmp;
}

void
UserEquipment::AddClientApp (ClientAppInfo clientAppInfo)
{
  NS_LOG_FUNCTION (this << clientAppInfo.contextId << clientAppInfo.context);
  m_clientAppList.push_back(clientAppInfo);
}

void
UserEquipment::DeleteClientApp (std::string contextId)
{
  for(auto it=m_clientAppList.begin(); it != m_clientAppList.end(); it++)
    {
      if((*it).contextId == contextId)
        {
          m_clientAppList.erase(it);
          break;
        }
    }
}

UserEquipment::ClientAppInfo
UserEquipment::FindClientApp(std::string contextId)
{
  NS_LOG_FUNCTION (this << contextId);
  ClientAppInfo app;
  app.contextId = "0";
  for(auto it=m_clientAppList.begin(); it != m_clientAppList.end(); it++)
    {
      if((*it).contextId == contextId)
        {
          app = *it;
        }
    }
  return app;
}


Ptr<AppContext>
UserEquipment::CreateAppContext (Ptr<AppD> appD)
{
  NS_LOG_FUNCTION (this << appD);
  Ptr<AppContext> appContext = CreateObject<AppContext> ();

  appContext->SetContextId(std::to_string(rand() % 99999999));
  appContext->SetAppDId(appD->GetAppDId());
  appContext->SetAppName(appD->GetAppName());
  appContext->SetAppProvider(appD->GetAppProvider());
  appContext->SetAppSoftwareVersion(appD->GetAppSoftwareVersion());
  appContext->SetAppDVersion(appD->GetAppDVersion());
  appContext->SetAppDescription(appD->GetAppDescription());
  appContext->SetCallbackReference(this);

  NS_LOG_FUNCTION (this->GetInstanceTypeId() <<
		   std::string("\n\t\t\t\t ContextId:\t ") + appContext->GetContextId() <<
		   std::string("\n\t\t\t\t AppDId:\t ") << appContext->GetAppDId() <<
		   std::string("\n\t\t\t\t AppName:\t ") + appContext->GetAppName() <<
		   std::string("\n\t\t\t\t AppProvider:\t ") + appContext->GetAppProvider() <<
		   std::string("\n\t\t\t\t AppSoftVersion: ") + appContext->GetAppSoftwareVersion() <<
		   std::string("\n\t\t\t\t AppDVersion:\t ") + appContext->GetAppDVersion() <<
		   std::string("\n\t\t\t\t AppDescription: ") + appContext->GetAppDescription()
		   );
  return appContext;
}

void
UserEquipment::SendCreateAppContextRequest(Ptr<AppContext> appContext)
{
  NS_LOG_FUNCTION (this << appContext);
  Ptr<CreateAppContextRequest> request = CreateObject<CreateAppContextRequest> ();
  request->SetAppContext(appContext);

  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << std::string("(imsi: ") + std::to_string(this->GetId())
  << std::string(")\t\t\t Send\t\t") + request->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") + request->GetAppContext()->GetContextId() <<")");

  Time delay = GetDelayModel()->GetRadioDelay(GetTargetBs()->GetAtiveFlow(2), 2) + GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &UserApplicationLcmProxy::ForwardCreateAppContextRequest, m_ualcmp, request);
}

void
UserEquipment::ProcessCreateAppContextResponse(Ptr<CreateAppContextResponse> response)
{
  if(response->GetRespCode() < 300)
    {
      NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(imsi: " << std::to_string(this->GetId())
      << std::string(")\t\t\t Process \t") << response->GetInstanceTypeId().GetName()
      << std::string("(ContextId: ") << response->GetAppContext()->GetContextId()
      << ", Mec Host ID: " << DynamicCast<MecHostEntity>(response->GetAppContext()->GetReferenceUri()->GetMecPlataform()->GetNode())->GetId()
      << std::string(", RespCode: ") << response->GetRespCode()
      << ", ProblemDetails: " << response->GetProblemDetails() << ")"
      );
      ClientAppInfo clientAppInfo;
      clientAppInfo.contextId = response->GetAppContext()->GetContextId();
      clientAppInfo.context = response->GetAppContext();
      clientAppInfo.clientApp = CreateObject<ClientApp>();
      clientAppInfo.clientApp->SetUe(this);
      clientAppInfo.clientApp->SetMecApp(response->GetAppContext()->GetReferenceUri());
      clientAppInfo.clientApp->SetTaskSize(response->GetAppContext()->GetReferenceUri()->GetAppD()->GetTaskLength());
      clientAppInfo.clientApp->SetInterarrivalTime(response->GetAppContext()->GetReferenceUri()->GetAppD()->GetTaskInterarrival());
      if(clientAppInfo.clientApp->GetMecApp()->GetAppD()->GetAppDId()==3)
        {
          clientAppInfo.clientApp->SetActiveIdle(20,30);
        }
      clientAppInfo.clientApp->SetState(1);
      clientAppInfo.clientApp->SetContextId(clientAppInfo.contextId);

      AddClientApp(clientAppInfo);
      GetTargetBs()->AddActiveFlow(clientAppInfo.clientApp->GetMecApp()->GetAppD()->GetAppDId());

    }
  else
    {
      NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(imsi: " << std::to_string(this->GetId())
      << std::string(")\t\t\t Process \t") << response->GetInstanceTypeId().GetName()
      << std::string("(ContextId: ") << response->GetAppContext()->GetContextId()
      << std::string(", RespCode: ") << response->GetRespCode()
      << ", ProblemDetails: " << response->GetProblemDetails() << ")"
      );
    }

}

void
UserEquipment::SendDeleteAppContextRequest(std::string contextId)
{
  NS_LOG_FUNCTION (this << contextId);
  ClientAppInfo clientAppInfo = FindClientApp(contextId);
  if(clientAppInfo.contextId != "0")
    {
      clientAppInfo.clientApp->SetState(0);
      GetTargetBs()->DeleteActiveFlow(clientAppInfo.clientApp->GetMecApp()->GetAppD()->GetAppDId());
      Ptr<DeleteAppContextRequest> request = CreateObject<DeleteAppContextRequest> ();
      request->SetContextId(contextId);
      request->SetCallbackReference(this);

      NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << std::string("(imsi: ") + std::to_string(this->GetId())
      << std::string(")\t\t\t Send\t\t") + request->GetInstanceTypeId().GetName()
      << std::string("(ContextId: ") + request->GetContextId() <<")");

      Time delay = GetDelayModel()->GetRadioDelay(GetTargetBs()->GetAtiveFlow(2), 2) + GetDelayModel()->GetControlPlaneDelay();
      Simulator::Schedule(delay, &UserApplicationLcmProxy::ForwardDeleteAppContextRequest, m_ualcmp, request);
    }
}

void
UserEquipment::ProcessDeleteAppContextResponse(Ptr<DeleteAppContextResponse> response)
{
  NS_LOG_INFO ("   \t" <<  this->GetInstanceTypeId() << std::string("(imsi: ") + std::to_string(this->GetId())
  << std::string(")\t\t\t Process\t") + response->GetInstanceTypeId().GetName()
  <<std::string("(RespCode: ") << response->GetRespCode()
  <<std::string(", ProblemDetails: ") << response->GetProblemDetails()  << std::string(")") );
  DeleteClientApp(response->GetContext()->GetContextId());

}

void
UserEquipment::ProcessUpdateAppContextNotification(Ptr<UpdateAppContextNotification> notification)
{
  NS_LOG_INFO ("   \t" <<  this->GetInstanceTypeId() << std::string("(imsi: ") + std::to_string(this->GetId())
  << std::string(")\t\t\t Process\t") + notification->GetInstanceTypeId().GetName()
  << std::string("(ContextId: ") << notification->GetAppContext()->GetContextId()
  << ", Mec Host ID: " << DynamicCast<MecHostEntity>(notification->GetAppContext()->GetReferenceUri()->GetMecPlataform()->GetNode())->GetId()
  << ")"
  );
  ClientAppInfo clientAppInfo = FindClientApp(notification->GetAppContext()->GetContextId());
  if(clientAppInfo.contextId != "0")
    {
      clientAppInfo.clientApp->SetMecApp(notification->GetAppContext()->GetReferenceUri());
    }


}


//////////mobility///////

Ptr<MobilityModel>
UserEquipment::GetMob()
{
  NS_LOG_FUNCTION (this);
  if(m_mob == 0)
    {
      Ptr<MobilityModel> mm = this->GetNode()->GetObject<MobilityModel>();
      return mm;
    }
  else
    {
      return m_mob;
    }
}

void
UserEquipment::SetMob(Ptr<MobilityModel> mob)
{
  NS_LOG_FUNCTION (this << mob);
  m_mob=mob;
}

Ptr<MecEntityContainer>
UserEquipment::GetBsList (void)
{
  NS_LOG_FUNCTION (this);
  return m_bsList;
}
void
UserEquipment::SetBsList (Ptr<MecEntityContainer> bsList)
{
  NS_LOG_FUNCTION (this);
  m_bsList=bsList;
}

Ptr<PropagationLossModel>
UserEquipment::GetPropagationLossModel (void)
{
  NS_LOG_FUNCTION (this);
  return m_propagationLossModel;
}

void
UserEquipment::SetPropagationLossModel (Ptr<PropagationLossModel> propLossMod)
{
  NS_LOG_FUNCTION (this << propLossMod);
  m_propagationLossModel = propLossMod;
}

Ptr<BaseStation>
UserEquipment::GetTargetBs()
{
  NS_LOG_FUNCTION (this);
  return m_bs;
}

void
UserEquipment::SetTargetBs(Ptr<BaseStation> bs)
{
  NS_LOG_FUNCTION (this << bs);
  m_bs=bs;
}

double
UserEquipment::GetTxPower()
{
  NS_LOG_FUNCTION (this);
  return m_txPower;
}

void
UserEquipment::SetTxPower(double txPower)
{
  NS_LOG_FUNCTION (this << txPower);
  m_txPower=txPower;
}

double
UserEquipment::GetTxAntennaGain()
{
  NS_LOG_FUNCTION (this);
  return m_txAntennaGain;
}

void
UserEquipment::SetTxAntennaGain(double txAntennaGain)
{
  NS_LOG_FUNCTION (this << txAntennaGain);
  m_txAntennaGain=txAntennaGain;
}

void
UserEquipment::UpdateCqi(void)
{
  NS_LOG_FUNCTION (this);
  double signal = m_propagationLossModel->CalcRxPower(m_txPower, this->GetMob(),  this->GetTargetBs()->GetMob());
  NS_LOG_FUNCTION (this);

  double noise=10*log10(pow(10,(-118/10)));
  double distance = this->GetMob()->GetDistanceFrom(this->GetTargetBs()->GetMob());
  double snr = signal - noise;

  int bestCqi=0;
  double minError=10000;
  double tempError;
  for (int i=1; i<16; i++)
    {
      tempError=(std::abs(SinrForCqi[i-1]-snr));
      if (tempError<minError)
        {
      bestCqi=i;
      minError=tempError;
        }
    }

  m_cqi = bestCqi;
  NS_LOG_FUNCTION ("BsDistance = " << distance <<"; rxPower = " << signal <<"; sinr = "<< snr << "; cqi = " << m_cqi);

}
void
UserEquipment::CourseChange (Ptr<const MobilityModel> mobility)
{
  Handover();
  UpdateCqi();
  GetLog()->PositionChange(GetId(), mobility->GetPosition());
}

bool
UserEquipment::Handover(void)
{
  Ptr<MecEntity> closestEnbDevice;
  double targetBsDistance = this->GetMob()->GetDistanceFrom(this->GetTargetBs()->GetMob());
  double minDistance = std::numeric_limits<double>::infinity ();
  for (MecEntityContainer::Iterator i = m_bsList->Begin (); i != m_bsList->End (); ++i)
     {
       double distance = this->GetMob()->GetDistanceFrom((*i)->GetNode ()->GetObject<MobilityModel>());
       if (distance < minDistance)
         {
           minDistance = distance;
           closestEnbDevice = *i;
         }
     }
  if(minDistance + m_handoverMargin < targetBsDistance)
    {
      Ptr<BaseStation> newBs = DynamicCast<BaseStation>(closestEnbDevice);
      SendRnisUpdate(GetTargetBs(), newBs);
      if(m_clientAppList.size()!=0)
        {
          GetTargetBs()->DeleteActiveFlow(m_clientAppList.begin()->clientApp->GetMecApp()->GetAppD()->GetAppDId());
          newBs->AddActiveFlow(m_clientAppList.begin()->clientApp->GetMecApp()->GetAppD()->GetAppDId());
        }
      GetTargetBs()->DeleteUe(GetId());
      SetTargetBs(newBs);
//      NS_LOG_INFO ("UE best base station ID: "<< newBs->GetId() <<"\t Handover");
      return 1;
    }

  else
    {
      return 0;
    }
}

void
UserEquipment::SendRnisUpdate(Ptr<BaseStation> srcBs, Ptr<BaseStation> trgBs)
{
  Ptr<CellChangeNotification> notification = CreateObject<CellChangeNotification>();
  notification->SetNotificationType("CellChangeNotification");
  notification->SetTimeStamp(Simulator::Now());
  notification->SetSrcBs(srcBs);
  notification->SetTrgBs(trgBs);
  notification->SetImsi(GetId());

//  NS_LOG_INFO ("   \t" << this->GetInstanceTypeId() << "(imsi: " << this->GetId()
//  << std::string(")\t\t Send \t\t") <<  notification->GetInstanceTypeId().GetName()
//  << "(Time: " << notification->GetTimeStamp()
//  << ", srcBsId: " << notification->GetSrcBs()->GetId()
//  << ", trgBsId: " << notification->GetTrgBs()->GetId()
//  << ")"
//  );
  Time delay = GetDelayModel()->GetRadioDelay(GetTargetBs()->GetAtiveFlow(2),2) + GetDelayModel()->GetControlPlaneDelay();
  Simulator::Schedule(delay, &BaseStation::ForwardRnisUpdate, srcBs, notification);

}

int
UserEquipment::GetCqi()
{
  return m_cqi;
}

} //namespace ns3

