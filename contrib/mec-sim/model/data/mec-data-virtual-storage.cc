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


#include "mec-data-virtual-storage.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("VirtualStorage");

TypeId VirtualStorage::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::VirtualStorage")
    .SetParent<Object> ();
  return tid;
}

VirtualStorage::VirtualStorage ()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

VirtualStorage::VirtualStorage (double sizeOfStorage)
{
  m_sizeOfStorage = sizeOfStorage;
  NS_LOG_FUNCTION (this->GetTypeId());
}

VirtualStorage::~VirtualStorage()
{
  NS_LOG_FUNCTION (this->GetTypeId());
}

void
VirtualStorage::SetTypeOfStorage (std::string typeOfStorage)
{
  NS_LOG_FUNCTION (this->GetTypeId() << typeOfStorage);
  m_typeOfStorage = typeOfStorage;
}

std::string
VirtualStorage::GetTypeOfStorage (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_typeOfStorage;
}

void
VirtualStorage::SetSizeOfStorage (double sizeOfStorage)
{
  NS_LOG_FUNCTION (this->GetTypeId() << sizeOfStorage);
  m_sizeOfStorage = sizeOfStorage;
}

double
VirtualStorage::GetSizeOfStorage (void)
{
  NS_LOG_FUNCTION (this->GetTypeId());
  return m_sizeOfStorage;
}

int
VirtualStorage::Size (void)
{
  int sz = sizeof(m_sizeOfStorage) + m_typeOfStorage.length();
  return sz;
}
} // namespace ns3
