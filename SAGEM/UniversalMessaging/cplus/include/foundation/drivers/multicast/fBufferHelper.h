/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FBUFFERHELPER_H
#define FBUFFERHELPER_H

#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
using namespace com::pcbsys::foundation::drivers::multicast;
class fBufferHelper {

  public:
    static unsigned char unpackByte(unsigned char* buf, int offset);

    static short unpackShort(unsigned char* buf, int offset);

    static int unpackInt(unsigned char* buf, int offset);

    static longlong unpackLong(unsigned char* buf, int offset);

    static longlong readNative(int size, unsigned char* buf, int off);

    static void packByte(unsigned char val, unsigned char* buff, int offset);

    static void packShort(short val, unsigned char* buff, int offset);

    static void packInt(int val, unsigned char* buff, int offset);

    static void packLong(longlong val, unsigned char* buff, int offset);

    static void writeNative( longlong val, int size , unsigned char* buff, int offset);
};
}
}
}
}
}

#endif
