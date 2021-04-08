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

#ifndef MEC_DATA_SOFTWARE_IMAGE_DESCRIPTOR_H
#define MEC_DATA_SOFTWARE_IMAGE_DESCRIPTOR_H


#include <ns3/core-module.h>


namespace ns3 {

class SwImageDescriptor : public Object
{
public:
  static TypeId GetTypeId (void);
  SwImageDescriptor ();
  virtual ~SwImageDescriptor ();

private:
  std::string m_swImageId;
  std::string m_name;
  std::string m_version;
  std::string m_checksum;
  std::string m_containerFormat;
  std::string m_diskFormat;
  double      m_minDisk;
  double      m_minRam;
  double      m_size;
  std::string m_os;
  std::string m_supportedVirtualEnvironment;

public:
  void SetSwImageId (std::string swImageId);
  std::string GetSwImageId (void);
  void SetName (std::string name);
  std::string GetName (void);
  void SetVersion (std::string version);
  std::string GetVersion(void);
  void SetChecksum (std::string checksum);
  std::string GetChecksum(void);
  void SetContainerFormat (std::string containerFormat);
  std::string GetContainerFormat (void);
  void SetDiskFormat (std::string diskFormat);
  std::string GetDiskFormat (void);
  void SetMinDisk (double minDisk);
  double GetMinDisk (void);
  void SetMinRam (double minRam);
  double GetMinRam(void);
  void SetSize (double size);
  double GetSize (void);
  void SetOs (std::string os);
  std::string GetOs (void);
  void SetSupportedVirtualEnvironment (std::string supportedVirtualEnvironment);
  std::string GetSupportedVirtualEnvironment (void);
  int Size (void);
};


}

#endif /* MEC_DATA_SOFTWARE_IMAGE_DESCRIPTOR_H */

