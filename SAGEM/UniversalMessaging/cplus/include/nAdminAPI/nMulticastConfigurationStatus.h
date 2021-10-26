/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NMULTICASTCONFIGURATIONSTATUS_H
#define NMULTICASTCONFIGURATIONSTATUS_H

#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nMulticastStatus;
}
namespace nAdminAPI {
using namespace com::pcbsys::nirvana::nbase;
class nMulticastConfigurationStatus {

  private:
    int myBytesSent;
    std::string myMulticastName;
    int myResetsSent;
    int myRetransmittedPackets;
    int myTotalPacketsSent;
    int myUnAckedPacketQueueSize;
    int myCurrentCount;
    std::string myResourceName;

  public:
    /**
     * Returns the number of bytes sent by this multicast instance
     * @return int bytes sent
     */
    int getBytesSent();

    /**
     * Returns the name of this multicast instance
     * @return std::string name of the multicast instance
     */
    std::string getMulticastName();

    /**
     * Returns the number of connection resets by this multicast instance.
     * @return The number of resets
     */
    int getResetsSent();

    /**
     * Returns the number of retransmitted packets due to loss or delay
     * @return int number of retransmitted packets
     */
    int getRetransmittedPackets();

    /**
     * Returns the total packets sent by this multicast instance
     * @return int total packets sent
     */
    int getTotalPacketsSent();

    /**
     * The size of unacked/outstanding packet queue size on the server
     * @return int outstanding packet queue size
     */
    int getUnAckedPacketQueueSize();

    /**
     * Returns the name of the resource that this status object is associated with.
     *
     * @return String resource name
     */
    std::string getResourceName();

    /**
     * The Count of currently connected clients to this multicast Instance
     * @return int count of current clients
     */
    int getCurrentClientCount();

  protected:
    nMulticastConfigurationStatus(nMulticastStatus* ms);

    void setBytesSent(int myBytesSent);

    void setMulticastName(std::string myMulticastName);

    void setResetsSent(int myResetsSent);

    void setRetransmittedPackets(int myRetransmittedPackets);

    void setTotalPacketsSent(int myTotalPacketsSent);

    void setUnAckedPacketQueueSize(int myUnAckedPacketQueueSize);

    void setCurrentClientCount(int connectedClients);

    friend class nInterfaceManager;
};

}
}
}
}

#endif
