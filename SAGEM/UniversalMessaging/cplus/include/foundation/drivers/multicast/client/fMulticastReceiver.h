/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FMULTICASTRECEIVER_H
#define FMULTICASTRECEIVER_H

#include "Poco/Runnable.h"
#include "Poco/Random.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Stream.h"
#include "fDriver.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
class fAsyncReadListener;
namespace configuration {
class fMulticastConfig;
}
namespace multicast {
class fBuffer;
namespace crypto {
class fDigest;
}
namespace client {
using namespace com::pcbsys::foundation::drivers::configuration;
using namespace com::pcbsys::foundation::drivers::multicast::crypto;
class fBufferSynchronisation;
class fMulticastReceiverManager;
class fBufferManager;
class fMulticastInputStream;
class fLastBufferMonitorTask;
class fMissingPacketTask;

class fMulticastReceiver : public Poco::Runnable, public Poco::SynchronizedObject {

  private:
    static Poco::Random sRandom;

    bool isRunning;
    longlong myRejectedPacketCount;
    longlong myAckCounter;

    Poco::Net::MulticastSocket* myMulticast;
    std::string myName;
    short myStreamId;

    fDigest* myDigest;
    longlong bytesReceived;
    bool sendAck;
    bool broadcastMode;


    fMissingPacketTask* myMissingPacketTask;
    fLastBufferMonitorTask* lastBufferIn;

    fMulticastReceiverManager* myManager;
    fMulticastInputStream* myIn;
    fBufferManager* myBuffers;
    fMulticastConfig* myConfig;
    Poco::Net::SocketAddress mySource;

    int myNextAckCount;

    // throws IOException
    void processPacket(fBuffer* buf,Poco::Net::SocketAddress addr);

  public:
    // throws IOException, InvalidKeyException, NoSuchAlgorithmException, NoSuchPaddingException, InvalidAlgorithmParameterException
    fMulticastReceiver(short streamId, fMulticastConfig* config, fMulticastReceiverManager* manager, unsigned char* key, int keyLen, fAsyncReadListener* listener, fBufferSynchronisation* bufferSyncListener, unsigned char* cookie, int cookieLen, fDriver* driver);

    std::string getName();

    void close();

    Net::Stream* getInputStream();

    void changeEncodingKey(longlong applyAt, unsigned char* key, int keyLen, unsigned char* cookie, int cookieLen);

    void setCRCSessionCookie(fDigest* digest);

    longlong getBytesReceived();

    void recoveryComplete();

    longlong getRejectedPacketCount();

    void scanForMissingEvents();

    void pushToBuffer(fBuffer* buffer);

    short getStreamId();

    longlong getLastBroadcastedMessage();

    void setLastBroadcastMessage(longlong id);

    int getReceivedBuffers();

    int getMissedBuffers();

    int getDuplicateBuffers();

    int getQueueSize();

    void run();

};
}
}
}
}
}
}

#endif
