/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FMULTICASTINPUTSTREAM_H
#define FMULTICASTINPUTSTREAM_H

#include <fTask.h>
#include "fBufferStreamHandler.h"
#include "Poco/Runnable.h"
#include <Stream.h>
#include <string.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fByteArrayQueueInputStream;
}
namespace drivers {
class fAsyncReadListener;
namespace multicast {
class changeKeyInfo;
namespace crypto {
class fBufferDecoder;
}
namespace client {
class fMulticastReceiverManager;
using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::drivers;
using namespace com::pcbsys::foundation::drivers::multicast::client;
using namespace com::pcbsys::foundation::drivers::multicast::crypto;
using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::Net;

class fMulticastInputStream : public Poco::Runnable, public fTask, public fBufferStreamHandler, public Poco::Mutex {

  private:
    fByteArrayQueueInputStream* myIn;
    bool isQueued;
    bool isLocked;
    bool isClosed;
    fMulticastReceiverManager* myManager;
    fBufferDecoder* myDecoder;
    ulonglong myLastId;
    fAsyncReadListener* myListener;

    std::list<changeKeyInfo*>* rollingCodes;

  protected:
    std::list<unsigned char*>* myProcessQueue;

  public:
    // throws IOException
    fMulticastInputStream(fMulticastReceiverManager* manager, fBufferDecoder* decoder, fAsyncReadListener* listener);

    void push(fBuffer* buffer);

    void handleCompleteMessage(fBuffer*& buf);

    int getBufferSize();

    void bufferOverRun();

    void reset();

    Stream* getInputStream();

    bool reQueue();

    void changeEncodingKey(longlong applyAt, unsigned char* key, int keyLen, unsigned char* cookie, int cookieLen);

    void changeEncodingKey();

    void close();

    void ThreadPoolCallback(void *pThreadContext);

    void run();

};
}
}
}
}
}
}

#endif
