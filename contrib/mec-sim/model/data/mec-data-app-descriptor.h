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

#ifndef MEC_DATA_APP_DESCRIPTOR_H
#define MEC_DATA_APP_DESCRIPTOR_H


#include <ns3/core-module.h>
#include <list>
#include <ns3/ipv4-address.h>
#include <ns3/random-variable-stream.h>
#include "mec-data-traffic-rule-descriptor.h"
#include "mec-data-dns-rule-descriptor.h"
#include "mec-data-feature-descriptor.h"
#include "mec-data-service-descriptor.h"
#include "mec-data-virtual-cpu.h"
#include "mec-data-virtual-storage.h"
#include "mec-data-virtual-memory.h"
#include "mec-data-acceleration-capability.h"
#include "mec-data-virtual-resource-descriptor.h"
#include "mec-data-software-image-descriptor.h"
#include "mec-data-latency-descriptor.h"
#include "mec-data-terminate-app-instance-operation-configuration.h"
#include "mec-data-change-app-instance-state-operation-configuration.h"

namespace ns3 {

class AppD : public Object
{
public:
  static TypeId GetTypeId (void);

  AppD ();
  virtual ~AppD ();

private:
  uint64_t                            m_appDId;
  std::string                         m_appName;
  std::string                         m_appProvider;
  std::string                         m_appSoftwareVersion;
  std::string                         m_appDVersion;
  std::string                         m_appDescription;
  std::string                         m_mecVersion;
  std::string                         m_appInfoName;
  Ptr<VirtualResourceDescriptor>      m_virtualResourceDescriptor;
  Ptr<SwImageDescriptor>              m_swImageDescriptor;
//  m_appExtCpd
  std::list <Ptr<ServiceDescriptor>>  m_appServiceRequiredList;
  std::list <Ptr<ServiceDescriptor>>  m_appServiceOptionalList;
  std::list <Ptr<ServiceDescriptor>>  m_appServiceProducedList;
  std::list <Ptr<FeatureDescriptor>>  m_appFeatureRequiredList;
  std::list <Ptr<FeatureDescriptor>>  m_appFeatureOptionalList;
//  m_transportDependencies
  Ptr<TrafficRuleDescriptor>          m_appTrafficRule;
  Ptr<DnsRuleDescriptor>              m_appDnsRule;
  Ptr<LatencyDescriptor>              m_appLatency;
  Ptr<TerminateAppInstanceOpConfig>   m_terminateAppInstanceOpConfig;
  Ptr<ChangeAppInstanceStateOpConfig> m_changeAppInstanceStateOpConfig;
//
  double m_bootingTime;
  Ptr<RandomVariableStream> m_taskLength;
  Ptr<RandomVariableStream> m_taskInterarrival;

public:
  void SetAppDId (uint64_t appDId);
  uint64_t GetAppDId (void);
  void SetAppName (std::string appName);
  std::string GetAppName (void);
  void SetAppProvider (std::string appProvider);
  std::string GetAppProvider (void);
  void SetAppSoftwareVersion (std::string appSoftwareVersion);
  std::string GetAppSoftwareVersion (void);
  void SetAppDVersion (std::string appDVersion);
  std::string GetAppDVersion (void);
  void SetAppDescription (std::string appDescription);
  std::string GetAppDescription (void);
  void SetMecVersion (std::string mecVersion);
  std::string GetMecVersion (void);
  void SetAppInfoName (std::string appInfoName);
  std::string GetAppInfoName (void);
  void SetVirtualResourceDescriptor (Ptr<VirtualResourceDescriptor> virtualResourceDescriptor);
  Ptr<VirtualResourceDescriptor> GetVirtualResourceDescriptor (void);
  void SetSwImageDescriptor (Ptr<SwImageDescriptor> swImageDescriptor);
  Ptr<SwImageDescriptor> GetSwImageDescriptor (void);
  void SetAppTrafficRule (Ptr<TrafficRuleDescriptor> appTrafficRule);
  Ptr<TrafficRuleDescriptor> GetAppTrafficRule (void);
  void SetAppDnsRule (Ptr<DnsRuleDescriptor> appDnsRule);
  Ptr<DnsRuleDescriptor> GetAppDnsRule (void);
  void SetAppLatency (Ptr<LatencyDescriptor> appLatency);
  Ptr<LatencyDescriptor> GetAppLatency (void);
  void SetTerminateAppInstanceOpConfig (Ptr<TerminateAppInstanceOpConfig> terminateAppInstanceOpConfig);
  Ptr<TerminateAppInstanceOpConfig>   GetTerminateAppInstanceOpConfig (void);
  void SetChangeAppInstanceStateOpConfig (Ptr<ChangeAppInstanceStateOpConfig> changeAppInstanceStateOpConfig);
  Ptr<ChangeAppInstanceStateOpConfig> GetChangeAppInstanceStateOpConfig (void);
  void AddAppServiceRequired (std::string serName,
			      std::string serCategory,
			      std::string version,
			      std::string transportsSupported);
  std::list <Ptr<ServiceDescriptor>> GetAppServiceRequiredList(void);
  void AddAppServiceOptional (std::string serName,
			      std::string serCategory,
			      std::string version,
			      std::string transportsSupported);
  std::list <Ptr<ServiceDescriptor>> GetAppServiceOptionalList(void);
  void AddAppServiceProduced (std::string serName,
			      std::string serCategory,
			      std::string version,
			      std::string transportsSupported);
  std::list <Ptr<ServiceDescriptor>> GetAppServiceProducedList(void);
  void AddAppFeatureRequired (std::string featureName,
			      std::string version);
  std::list <Ptr<FeatureDescriptor>> GetAppFeatureRequiredList(void);
  void AddAppFeatureOptional (std::string featureName,
			      std::string version);
  std::list <Ptr<FeatureDescriptor>> GetAppFeatureOptionalList(void);

  double GetBootingTime(void);
  Ptr<RandomVariableStream> GetTaskLength(void);
  Ptr<RandomVariableStream> GetTaskInterarrival(void);
  void SetBootingTime(double time);
  void SetTaskLength(Ptr<RandomVariableStream> task);
  void SetTaskInterarrival(Ptr<RandomVariableStream> taskTime);

  int Size (void);
};

}

#endif /* MEC_DATA_APP_DESCRIPTOR_H */

