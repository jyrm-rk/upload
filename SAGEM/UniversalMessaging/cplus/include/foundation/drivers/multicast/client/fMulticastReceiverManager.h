/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FMULTICASTRECEIVERMANAGER_H
#define FMULTICASTRECEIVERMANAGER_H

#include "Poco/Net/IPAddress.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace client {
using namespace com::pcbsys::foundation::fbase;

class fMulticastReceiverManager {

  public:
    virtual void receivedReset()=0;

    virtual void missingPacket(longlong packetId, BitArray* map)=0;

    virtual void bindingToServer(Poco::Net::IPAddress serverAddress)=0;

    virtual void sendAck(longlong packetId)=0;

    virtual void lockedToStream()=0;

    // throws IOException
    virtual void expectingMessage(longlong expectedId)=0;
};
}
}
}
}
}
}

#endif
