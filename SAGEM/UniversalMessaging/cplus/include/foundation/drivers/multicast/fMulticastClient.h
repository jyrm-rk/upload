/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FMULTICASTCLIENT_H
#define FMULTICASTCLIENT_H

#include "fMulticastReceiverManager.h"
#include "fBufferSynchronisation.h"
#include "Poco/Net/IPAddress.h"
#include "Stream.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fConnection;
}
namespace drivers {
class fAsyncReadListener;
namespace configuration {
class fMulticastConfig;
}
namespace multicast {
namespace crypto {
class fDigest;
}
namespace client {
class fMulticastReceiver;
}
using namespace com::pcbsys::foundation::drivers::configuration;
using namespace com::pcbsys::foundation::drivers::multicast::client;
using namespace com::pcbsys::foundation::drivers::multicast::crypto;
using namespace com::pcbsys::foundation::drivers;
using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::fbase;

class fMulticastClient : public fMulticastReceiverManager,  public fBufferSynchronisation {
    friend class fMulticastManager;

  private:
    fConnection* myReliableOutput;
    fMulticastReceiver* myMulticastReceiver;
    short myStreamId;
    fAsyncReadListener* myListener;

    unsigned char* myCookie;
    int myCookieLen;

    fDigest* myDigest;

    fMulticastConfig* myConfig;

  protected:
    void close();

    // throws InvalidKeyException, NoSuchAlgorithmException, NoSuchPaddingException, InvalidAlgorithmParameterException, IOException
  public:
    fMulticastClient(short streamId, fMulticastConfig* config, fConnection* reliableOutput, fAsyncReadListener* eventListener);

    std::string getId();

    int getReceived();

    int getMissedPackets();

    int getDuplicatePackets();

    longlong getBytesReceived();

    Stream* getInputStream();

    int getQueueSize();

    void receivedReset();

    void sendAck(longlong packetId);

    void missingPacket(longlong packetId, BitArray* map);

    void bindingToServer(Poco::Net::IPAddress serverAddress);

    void lockedToStream();

    void readOOBMessage(fConnection* connection, short streamId);

    void buffersInSync();

    void buffersOutOfSync();

    void reset();

    // throws IOException
    void expectingMessage(longlong bufferId);

    void removeOOBHandler();

    void sendReady();

};
}
}
}
}
}

#endif
