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


#include "mec-data-software-image-descriptor.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SwImageDescriptor");

TypeId SwImageDescriptor::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SwImageDescriptor")
    .SetParent<Object> ();
  return tid;
}

SwImageDescriptor::SwImageDescriptor ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
  m_minDisk = 0;
  m_minRam = 0;
  m_size = 0;
}

SwImageDescriptor::~SwImageDescriptor()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
SwImageDescriptor::SetSwImageId (std::string swImageId)
{
  NS_LOG_FUNCTION (this->GetTypeId() << swImageId);
  m_swImageId = swImageId;
}

std::string
SwImageDescriptor::GetSwImageId (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_swImageId;
}

void
SwImageDescriptor::SetName (std::string name)
{
  NS_LOG_FUNCTION (this->GetTypeId() << name);
  m_name = name;
}


std::string
SwImageDescriptor::GetName (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_name;
}

void
SwImageDescriptor::SetVersion (std::string version)
{
  NS_LOG_FUNCTION (this->GetTypeId() << version);
  m_version = version;
}


std::string
SwImageDescriptor::GetVersion(void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_swImageId;
}

void
SwImageDescriptor::SetChecksum (std::string checksum)
{
  NS_LOG_FUNCTION (this->GetTypeId() << checksum);
  m_checksum = checksum;
}


std::string
SwImageDescriptor::GetChecksum(void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_checksum;
}

void
SwImageDescriptor::SetContainerFormat (std::string containerFormat)
{
  NS_LOG_FUNCTION (this->GetTypeId() << containerFormat);
  m_containerFormat = containerFormat;
}


std::string
SwImageDescriptor::GetContainerFormat (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_containerFormat;
}

void
SwImageDescriptor::SetDiskFormat (std::string diskFormat)
{
  NS_LOG_FUNCTION (this->GetTypeId() << diskFormat);
  m_diskFormat = diskFormat;
}


std::string
SwImageDescriptor::GetDiskFormat (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_diskFormat;
}

void
SwImageDescriptor::SetMinDisk (double minDisk)
{
  NS_LOG_FUNCTION (this->GetTypeId() << minDisk);
  m_minDisk = minDisk;
}


double
SwImageDescriptor::GetMinDisk (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_minDisk;
}

void
SwImageDescriptor::SetMinRam (double minRam)
{
  NS_LOG_FUNCTION (this->GetTypeId() << minRam);
  m_minRam = minRam;
}


double
SwImageDescriptor::GetMinRam(void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_minRam;
}

void
SwImageDescriptor::SetSize (double size)
{
  NS_LOG_FUNCTION (this->GetTypeId() << size);
  m_size = size;
}


double
SwImageDescriptor::GetSize (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_size;
}

void
SwImageDescriptor::SetOs (std::string os)
{
  NS_LOG_FUNCTION (this->GetTypeId() << os);
  m_os = os;
}


std::string
SwImageDescriptor::GetOs (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_os;
}

void
SwImageDescriptor::SetSupportedVirtualEnvironment (std::string supportedVirtualEnvironment)
{
  NS_LOG_FUNCTION (this->GetTypeId() << supportedVirtualEnvironment);
  m_supportedVirtualEnvironment = supportedVirtualEnvironment;
}


std::string
SwImageDescriptor::GetSupportedVirtualEnvironment (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_supportedVirtualEnvironment;
}

int
SwImageDescriptor::Size (void)
{
  int sz = m_swImageId.length() +
      m_name.length() +
      m_checksum.length() +
      m_containerFormat.length() +
      m_diskFormat.length() +
      sizeof(m_minDisk) +
      sizeof(m_minRam) +
      sizeof(m_size) +
      m_os.length() +
      m_supportedVirtualEnvironment.length();
  return sz;
}
} // namespace ns3
