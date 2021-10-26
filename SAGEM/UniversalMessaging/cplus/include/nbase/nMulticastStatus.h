/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NMULTICASTSTATUS_H
#define NMULTICASTSTATUS_H

#include "nBaseInterfaceStatus.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nMulticastStatus : public nBaseInterfaceStatus {

  private:
    static std::string sBytesSent;
    static std::string sMulName;
    static std::string sUnackedEventQueue;
    static std::string sResetsSent;
    static std::string sRetransmittedPackets;
    static std::string sTotalPacketsSent;
    static std::string sCurrentConnections;
    static std::string sResourceName;

  public:
    nMulticastStatus(nBaseInterfaceStatus* istatus);

    int getBytesSent();

    std::string getMulticastName();

    int getResetsSent();

    int getRetransmittedPackets();

    int getTotalPacketsSent();

    int getUnackedPacketQueueSize();

    int getConnectedClients();

    std::string getResourceName();

};

}
}
}
}

#endif
