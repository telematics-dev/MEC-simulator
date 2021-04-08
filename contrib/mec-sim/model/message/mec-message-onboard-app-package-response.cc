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


#include "mec-message-onboard-app-package-response.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("OnboardAppPkgResponse");

TypeId OnboardAppPkgResponse::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::OnboardAppPkgResponse")
    .SetParent<Object> ();
  return tid;
}

OnboardAppPkgResponse::OnboardAppPkgResponse ()
{
  m_respCode=0;
  NS_LOG_FUNCTION (this);
}

OnboardAppPkgResponse::~OnboardAppPkgResponse ()
{
  NS_LOG_FUNCTION (this);
}

void
OnboardAppPkgResponse::SetAppPkgInfo(Ptr<AppPkgInfo> appPkgInfo)
{
  NS_LOG_FUNCTION (this << appPkgInfo);
  m_appPkgInfo = appPkgInfo;
}

void
OnboardAppPkgResponse::SetRespCode(uint16_t respCode)
{
  NS_LOG_FUNCTION (this << respCode);
  m_respCode = respCode;
}

void
OnboardAppPkgResponse::SetProblemDetails(std::string problemDetails)
{
  NS_LOG_FUNCTION (this << problemDetails);
  m_problemDetails = problemDetails;
}


/*
 *
 *   Ptr<AppPkgInfo> GetAppPkgInfo (void);
  uint16_t GetRespCode (void);
  std::string GetProblemDetails (void);
  void SetAppPkgName (Ptr<AppPkgInfo> appPkgInfo);
  void SetAppPkgVersion (uint16_t respCode);
  void SetAppProvider (std::string problemDetails);
 */

Ptr<AppPkgInfo>
OnboardAppPkgResponse::GetAppPkgInfo()
{
  NS_LOG_FUNCTION (this);
  return m_appPkgInfo;
}

uint16_t
OnboardAppPkgResponse::GetRespCode()
{
  NS_LOG_FUNCTION (this);
  return m_respCode;
}

std::string
OnboardAppPkgResponse::GetProblemDetails()
{
  NS_LOG_FUNCTION (this);
  return m_problemDetails;
}

} // namespace ns3
