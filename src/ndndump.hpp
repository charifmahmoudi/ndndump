/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2011-2014, Regents of the University of California,
 *
 * This file is part of ndndump, the packet capture and analysis tool for Named Data
 * Networking (NDN).
 *
 * ndndump is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndndump is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndndump, e.g., in COPYING file.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef NDNDUMP_NDNDUMP_HPP
#define NDNDUMP_NDNDUMP_HPP

#include <pcap.h>

#include <ndn-cxx/name.hpp>
#include <boost/regex.hpp>

#include <fstream>      // std::ofstream

namespace ndn {
namespace tools {

class Ndndump : noncopyable
{
public:
  class Error : public std::runtime_error
  {
  public:
    explicit
    Error(const std::string& what)
      : std::runtime_error(what)
    {
    }
  };

  Ndndump()
    : isVerbose(false)
  , isCSV(false)
  , pcapProgram("(ether proto 0x8624) || (tcp port 6363) || (udp port 6363)")
    // , isSuccinct(false)
    // , isMatchInverted(false)
    // , shouldPrintStructure(false)
    // , isTcpOnly(false)
    // , isUdpOnly(false)
  {
  }

  void
  run();
  void
  stop()
  {
	  ofs.close();
  }

private:
  static void
  onCapturedPacket(uint8_t* userData, const struct pcap_pkthdr* header, const uint8_t* packet)
  {
    reinterpret_cast<Ndndump*>(userData)->onCapturedPacket(header, packet);
  }

  void
  onCapturedPacket(const struct pcap_pkthdr* header, const uint8_t* packet);

  void
  printInterceptTime(std::ostream& os, const struct pcap_pkthdr* header);

  int
  skipDataLinkHeaderAndGetFrameType(const uint8_t*& payload, ssize_t& payloadSize);

  int
  skipAndProcessFrameHeader(int frameType,
                            const uint8_t*& payload, ssize_t& payloadSize,
                            std::ostream& os);

  bool
  matchesFilter(const Name& name)
  {
    if (nameFilter.empty())
      return true;

    /// \todo Switch to NDN regular expressions

    return boost::regex_match(name.toUri(), nameFilter);
  }

public:
  bool isVerbose;
  bool isCSV;
  // bool isSuccinct;
  // bool isMatchInverted;
  // bool shouldPrintStructure;
  // bool isTcpOnly;
  // bool isUdpOnly;

  std::string pcapProgram;
  std::string interface;
  boost::regex nameFilter;
  std::string inputFile;
  std::string outputFile;
  std::string separator;

private:
  pcap_t* m_pcap;
  int m_dataLinkType;
  std::ofstream ofs;
};


} // namespace tools
} // namespace ndn

#endif // NDNDUMP_NDNDUMP_HPP
