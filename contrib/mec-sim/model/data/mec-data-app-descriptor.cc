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


#include "mec-data-app-descriptor.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("AppD");

TypeId AppD::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::AppD")
    .SetParent<Object> ();
  return tid;
}

AppD::AppD ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
  m_appDId = 0;
  Ptr<VirtualResourceDescriptor> virtualResourceDescriptor;
  Ptr<VirtualCpu> virtualCpu;
  Ptr<VirtualMemory> virtualMemory;
  Ptr<VirtualStorage> virtualStorage;
  Ptr<AccelerationCapability> accelerationCapability;
  Ptr<SwImageDescriptor> swImageDescriptor;
  Ptr<TrafficRuleDescriptor> appTrafficRule;
  Ptr<DnsRuleDescriptor> appDnsRule;
  Ptr<LatencyDescriptor> appLatency;
  Ptr<TerminateAppInstanceOpConfig> terminateAppInstanceOpConfig;
  Ptr<ChangeAppInstanceStateOpConfig> changeAppInstanceStateOpConfig;

  virtualResourceDescriptor = CreateObject<VirtualResourceDescriptor> ();
  virtualCpu = CreateObject<VirtualCpu> ();
  virtualResourceDescriptor->SetVirtualCpu(virtualCpu);
  virtualMemory = CreateObject<VirtualMemory> ();
  virtualResourceDescriptor->SetVirtualMemory(virtualMemory);
  virtualStorage = CreateObject<VirtualStorage> ();
  virtualResourceDescriptor->SetVirtualStorage(virtualStorage);
  accelerationCapability = CreateObject<AccelerationCapability> ();
  virtualResourceDescriptor->SetAccelerationCapability(accelerationCapability);
  SetVirtualResourceDescriptor(virtualResourceDescriptor);
  swImageDescriptor = CreateObject<SwImageDescriptor> ();
  SetSwImageDescriptor(swImageDescriptor);
  appTrafficRule = CreateObject<TrafficRuleDescriptor> ();
  SetAppTrafficRule(appTrafficRule);
  appDnsRule = CreateObject<DnsRuleDescriptor> ();
  SetAppDnsRule(appDnsRule);
  appLatency = CreateObject<LatencyDescriptor> ();
  SetAppLatency(appLatency);
  terminateAppInstanceOpConfig = CreateObject<TerminateAppInstanceOpConfig> ();
  SetTerminateAppInstanceOpConfig(terminateAppInstanceOpConfig);
  changeAppInstanceStateOpConfig = CreateObject<ChangeAppInstanceStateOpConfig> ();
  SetChangeAppInstanceStateOpConfig(changeAppInstanceStateOpConfig);

}

AppD::~AppD()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
AppD::SetAppDId (uint64_t appDId)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appDId);
  m_appDId = appDId;
}

uint64_t
AppD::GetAppDId (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appDId;
}

void
AppD::SetAppName (std::string appName)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appName);
  m_appName = appName;
}

std::string
AppD::GetAppName (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appName;
}

void
AppD::SetAppProvider (std::string appProvider)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appProvider);
  m_appProvider = appProvider;
}

std::string
AppD::GetAppProvider (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appProvider;
}

void
AppD::SetAppSoftwareVersion (std::string appSoftwareVersion)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appSoftwareVersion);
  m_appSoftwareVersion = appSoftwareVersion;
}

std::string
AppD::GetAppSoftwareVersion (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appSoftwareVersion;
}

void
AppD::SetAppDVersion (std::string appDVersion)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appDVersion);
  m_appDVersion = appDVersion;
}

std::string
AppD::GetAppDVersion (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appDVersion;
}

void
AppD::SetAppDescription (std::string appDescription)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appDescription);
  m_appDescription = appDescription;
}

std::string
AppD::GetAppDescription (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appDescription;
}

void
AppD::SetMecVersion (std::string mecVersion)
{
  NS_LOG_FUNCTION (this->GetTypeId() << mecVersion);
  m_mecVersion = mecVersion;
}

std::string
AppD::GetMecVersion (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_mecVersion;
}

void
AppD::SetAppInfoName (std::string appInfoName)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appInfoName);
  m_appInfoName = appInfoName;
}

std::string
AppD::GetAppInfoName (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appInfoName;
}

void
AppD::SetVirtualResourceDescriptor (Ptr<VirtualResourceDescriptor> virtualResourceDescriptor)
{
  NS_LOG_FUNCTION (this->GetTypeId() << virtualResourceDescriptor->GetTypeId());
  m_virtualResourceDescriptor = virtualResourceDescriptor;
}

Ptr<VirtualResourceDescriptor>
AppD::GetVirtualResourceDescriptor (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_virtualResourceDescriptor;
}

void
AppD::SetSwImageDescriptor (Ptr<SwImageDescriptor> swImageDescriptor)
{
  NS_LOG_FUNCTION (this->GetTypeId() << swImageDescriptor->GetTypeId());
  m_swImageDescriptor = swImageDescriptor;
}

Ptr<SwImageDescriptor>
AppD::GetSwImageDescriptor (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_swImageDescriptor;
}

void
AppD::SetAppTrafficRule (Ptr<TrafficRuleDescriptor> appTrafficRule)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appTrafficRule->GetTypeId());
  m_appTrafficRule = appTrafficRule;

}

Ptr<TrafficRuleDescriptor>
AppD::GetAppTrafficRule (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appTrafficRule;
}

void
AppD::SetAppDnsRule (Ptr<DnsRuleDescriptor> appDnsRule)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appDnsRule->GetTypeId());
  m_appDnsRule = appDnsRule;

}

Ptr<DnsRuleDescriptor>
AppD::GetAppDnsRule (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appDnsRule;
}

void
AppD::SetAppLatency (Ptr<LatencyDescriptor> appLatency)
{
  NS_LOG_FUNCTION (this->GetTypeId() << appLatency->GetTypeId());
  m_appLatency = appLatency;

}

Ptr<LatencyDescriptor>
AppD::GetAppLatency (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appLatency;
}

void
AppD::SetTerminateAppInstanceOpConfig (Ptr<TerminateAppInstanceOpConfig> terminateAppInstanceOpConfig)
{
  NS_LOG_FUNCTION (this->GetTypeId() << terminateAppInstanceOpConfig->GetTypeId());
  m_terminateAppInstanceOpConfig = terminateAppInstanceOpConfig;

}

Ptr<TerminateAppInstanceOpConfig>
AppD::GetTerminateAppInstanceOpConfig (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_terminateAppInstanceOpConfig;
}

void
AppD::SetChangeAppInstanceStateOpConfig (Ptr<ChangeAppInstanceStateOpConfig> changeAppInstanceStateOpConfig)
{
  NS_LOG_FUNCTION (this->GetTypeId() << changeAppInstanceStateOpConfig->GetTypeId());
  m_changeAppInstanceStateOpConfig = changeAppInstanceStateOpConfig;

}

Ptr<ChangeAppInstanceStateOpConfig>
AppD::GetChangeAppInstanceStateOpConfig (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_changeAppInstanceStateOpConfig;
}

///////////////////SERVICE-FEATURE///////////////////////////////////////////

void
AppD::AddAppServiceRequired (std::string serName, std::string serCategory, std::string version, std::string transportsSupported)
{
  NS_LOG_FUNCTION (this->GetTypeId() << serName << serCategory << version << transportsSupported);
  Ptr<ServiceDescriptor>service = CreateObject<ServiceDescriptor> ();
  service->SetSerName(serName);
  service->SetSerCategory(serCategory);
  service->SetVersion(version);
  service->SetTransportsSupported(transportsSupported);
  m_appServiceRequiredList.push_back(service);
}

std::list <Ptr<ServiceDescriptor>>
AppD::GetAppServiceRequiredList(void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appServiceRequiredList;
}

void
AppD::AddAppServiceOptional (std::string serName, std::string serCategory, std::string version, std::string transportsSupported)
{
  NS_LOG_FUNCTION (this->GetTypeId() << serName << serCategory << version << transportsSupported);
  Ptr<ServiceDescriptor>service = CreateObject<ServiceDescriptor> ();
  service->SetSerName(serName);
  service->SetSerCategory(serCategory);
  service->SetVersion(version);
  service->SetTransportsSupported(transportsSupported);
  m_appServiceOptionalList.push_back(service);
}

std::list <Ptr<ServiceDescriptor>>
AppD::GetAppServiceOptionalList(void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appServiceOptionalList;
}

void
AppD::AddAppServiceProduced (std::string serName, std::string serCategory, std::string version, std::string transportsSupported)
{
  NS_LOG_FUNCTION (this->GetTypeId() << serName << serCategory << version << transportsSupported);
  Ptr<ServiceDescriptor>service = CreateObject<ServiceDescriptor> ();
  service->SetSerName(serName);
  service->SetSerCategory(serCategory);
  service->SetVersion(version);
  service->SetTransportsSupported(transportsSupported);
  m_appServiceProducedList.push_back(service);
}

std::list <Ptr<ServiceDescriptor>>
AppD::GetAppServiceProducedList(void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appServiceProducedList;
}

void
AppD::AddAppFeatureRequired (std::string featureName, std::string version)
{
  NS_LOG_FUNCTION (this->GetTypeId() << featureName<< version);
  Ptr<FeatureDescriptor>feature = CreateObject<FeatureDescriptor> ();
  feature->SetFeatureName(featureName);
  feature->SetVersion(version);
  m_appFeatureRequiredList.push_back(feature);
}

std::list <Ptr<FeatureDescriptor>>
AppD::GetAppFeatureRequiredList(void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appFeatureRequiredList;
}

void
AppD::AddAppFeatureOptional (std::string featureName, std::string version)
{
  NS_LOG_FUNCTION (this->GetTypeId() << featureName<< version);
  Ptr<FeatureDescriptor>feature = CreateObject<FeatureDescriptor> ();
  feature->SetFeatureName(featureName);
  feature->SetVersion(version);
  m_appFeatureOptionalList.push_back(feature);
}

std::list <Ptr<FeatureDescriptor>>
AppD::GetAppFeatureOptionalList(void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_appFeatureOptionalList;
}

double
AppD::GetBootingTime(void)
{
  NS_LOG_FUNCTION (this);
  return m_bootingTime;
}
Ptr<RandomVariableStream>
AppD::GetTaskLength(void)
{
  NS_LOG_FUNCTION (this);
  return m_taskLength;
}
Ptr<RandomVariableStream>
AppD::GetTaskInterarrival(void)
{
  NS_LOG_FUNCTION (this);
  return m_taskInterarrival;
}
void
AppD::SetBootingTime(double time)
{
  NS_LOG_FUNCTION (this);
  m_bootingTime = time;
}
void
AppD::SetTaskLength(Ptr<RandomVariableStream> task)
{
  NS_LOG_FUNCTION (this);
  m_taskLength = task;
}
void
AppD::SetTaskInterarrival(Ptr<RandomVariableStream> taskTime)
{
  NS_LOG_FUNCTION (this);
  m_taskInterarrival = taskTime;
}

int
AppD::Size (void)
{
  int sz = sizeof(m_appDId) +
      m_appName.length() +
      m_appProvider.length() +
      m_appSoftwareVersion.length() +
      m_appDVersion.length() +
      m_appDescription.length() +
      m_mecVersion.length()+
      m_appInfoName.length()+
      m_virtualResourceDescriptor->Size()+
      m_swImageDescriptor->Size()+
      m_appTrafficRule->Size()+
      m_appDnsRule->Size()+
      m_appLatency->Size()+
      m_terminateAppInstanceOpConfig->Size()+
      m_changeAppInstanceStateOpConfig->Size();
  std::list <Ptr<ServiceDescriptor>> :: iterator it_service;
  Ptr<ServiceDescriptor> service;
  for(it_service = m_appServiceRequiredList.begin(); it_service != m_appServiceRequiredList.end(); ++it_service)
  {
      service = *it_service;
    sz = sz + service->Size();
  }
  for(it_service = m_appServiceOptionalList.begin(); it_service != m_appServiceOptionalList.end(); ++it_service)
  {
      service = *it_service;
    sz = sz + service->Size();
  }
  for(it_service = m_appServiceProducedList.begin(); it_service != m_appServiceProducedList.end(); ++it_service)
  {
      service = *it_service;
    sz = sz + service->Size();
  }
  std::list <Ptr<FeatureDescriptor>> :: iterator it_feature;
  Ptr<FeatureDescriptor> feature;
  for(it_feature = m_appFeatureRequiredList.begin(); it_feature != m_appFeatureRequiredList.end(); ++it_feature)
  {
      feature = *it_feature;
    sz = sz + service->Size();
  }
  for(it_feature = m_appFeatureOptionalList.begin(); it_feature != m_appFeatureOptionalList.end(); ++it_feature)
  {
      feature = *it_feature;
    sz = sz + service->Size();
  }


  return sz;
}

} // namespace ns3
