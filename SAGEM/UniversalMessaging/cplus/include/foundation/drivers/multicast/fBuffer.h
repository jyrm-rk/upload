/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FBUFFER_H
#define FBUFFER_H

#include "fDigest.h"
#include "fBase.h"
#include <string.h>
namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {
class fDigest;
}
using namespace com::pcbsys::foundation::drivers::multicast;
using namespace com::pcbsys::foundation::drivers::multicast::crypto;

class fBuffer {

  private:
    longlong myId;
    unsigned char* myData;
    int myDataLen;
    int myOffset;

    longlong myLastReTransmitTime;
    longlong myRemovalTime;

  public:
    DLL static int headerSize;

    DLL static unsigned char* getKeepAliveBuffer(longlong expectedId, fDigest* digest, int retLen);

    DLL static unsigned char* getResetBuffer(fDigest* digest, int retLen);

    DLL fBuffer(longlong bid, unsigned char* buffer, int bufferLen);

    DLL fBuffer(longlong bid, unsigned char* buffer, int bufferLen, int offset);

    //throws IOException
    DLL fBuffer(unsigned char* buf, int bufferLen, fDigest* digest);

    //throws IOException
    DLL fBuffer(unsigned char* buffer, int bufferLen);

    DLL ~fBuffer();

    DLL unsigned char* packBuffer(fDigest* digest);

    DLL longlong getId();

    DLL unsigned char* getData(int &len);

    DLL void setData(unsigned char* data, int dataLen);

    DLL longlong getLastTransmitTime();

    DLL void setLastTransmitTime(longlong time);

    DLL longlong getRemovalTime();

    DLL void setRemovalTime(longlong time);

    DLL longlong getKeepAliveId();

    fBuffer* clone();
};

}
}
}
}
}

#endif
