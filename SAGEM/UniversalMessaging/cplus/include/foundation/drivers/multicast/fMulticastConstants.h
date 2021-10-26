/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FMULTICASTCONSTANTS_H
#define FMULTICASTCONSTANTS_H

#include <fBaseEventFactory.h>
#include <fEventOutputStream.h>
#include <fLogger.h>
#include <string>
//#include "client/fCompressMulticastInputStream.h" todo implement later

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
using namespace com::pcbsys::foundation::io;
class fMulticastConstants {

  private:
    static unsigned char* setupMarker();

  public:
    static const unsigned char* sMyMarker;
    static int sMyMarkerLen;

    static const bool sDebug = false;

    static const unsigned char sReset = 0;
    static const unsigned char sRetransmittedPacket = 1;
    static const unsigned char sMissedPacketRequest = 2;
    static const unsigned char sInSync = 3;
    static const unsigned char sOutSync = 4;
    static const unsigned char sOOBReady = 5;
    static const unsigned char sOOBReset = 6;
    static const unsigned char sChangeEncodingKey = 7;
    static const unsigned char sSessionCookie = 8;
    static const unsigned char sExpectingId = 9;
    static const unsigned char sRecoveryComplete = 10;
    static const unsigned char sAck = 11;

    static longlong sOutputBufferRemovalDelay;   //The timeout of buffers within the output queue

    static void sendOOBPacket(fEventOutputStream* stream, short streamId, unsigned char command, longlong payload);

    static void sendOOBPacket(fEventOutputStream* stream, short streamId, unsigned char command, unsigned char* payload, int payloadLen);

    static void sendOOBPacket(fEventOutputStream* stream, short streamId, unsigned char command, unsigned char* payload, int payloadLen, std::string str);

    static  void sendOOBPacket(fEventOutputStream* stream, short streamId, unsigned char command, longlong id, unsigned char* payload, int payloadLen);

    static void sendOOBPacketNoFlush(fEventOutputStream* stream, short streamId, unsigned char command, unsigned char* payload, int payloadLen);

    static const void log(std::string msg);
};
}
}
}
}
}

#endif

