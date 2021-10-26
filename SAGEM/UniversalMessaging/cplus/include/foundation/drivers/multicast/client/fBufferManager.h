/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FBUFFERMANAGER_H
#define FBUFFERMANAGER_H
#include "fBase.h"
#include <string.h>

namespace cppunittests {
class fBufferManagerTest;
}

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
class fBuffer;
namespace client {
class fBufferSynchronisation;
class fBufferStreamHandler;

using namespace com::pcbsys::foundation::drivers::multicast;
using namespace com::pcbsys::foundation::fbase;

class fBufferManager : public Poco::Mutex {
    friend class fMissingPacketTask;
    friend class fLastBufferMonitorTask;
    friend class fMulticastReceiver;
    friend class cppunittests::fBufferManagerTest;

  private:

    bool inSync;
    bool isClosed;

    unsigned long myBufSize;
    unsigned long myMissedBuffers;
    unsigned long myDuplicateBuffers;
    unsigned long myReceivedBuffers;
    unsigned long myBacklogSize;

    longlong myMaxId;
    longlong myLatestMulticastedId;
    longlong myExpectedId;
    longlong myBufferIdx;

    fBufferStreamHandler* myStream;
    fBuffer** myArray;
    fBufferSynchronisation* myListener;

    fBuffer* lookup(longlong bufNo);
    void store(fBuffer* buf);

  protected:
    DLL void reset();

    DLL longlong getExpectedId();

    DLL longlong getMissingOffset();

    DLL BitArray* getMissing();

    DLL bool isMissingPacket();

    DLL void push(fBuffer* buf);

  public:
    DLL fBufferManager(fBufferStreamHandler* mis, fBufferSynchronisation* listener, int backlogSize);

    DLL long getQueueSize();

    DLL longlong getLatestBufferId();

    DLL void setLatestBufferId(longlong id);

    DLL long getMissedBuffers();

    DLL long getDuplicateBuffers();

    DLL long getReceivedBuffers();

    DLL void close();
};
}
}
}
}
}
}
#endif
