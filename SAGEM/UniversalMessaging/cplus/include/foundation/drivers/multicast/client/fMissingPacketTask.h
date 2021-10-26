/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#include <fTask.h>
#include "fBase.h"
#include "Poco/Runnable.h"
#include "fPocoThreadPool.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fTask;
}
namespace drivers {
namespace multicast {
namespace client {
class fBufferManager;
class fMulticastReceiverManager;
using namespace com::pcbsys::foundation::fbase;
class fMissingPacketTask : public fTask, public Poco::Mutex, public Poco::Runnable {

  private:
    fMulticastReceiverManager* myManager;
    fBufferManager* myBuffers;

    bool _isQueued;
    bool isClosed;
    bool _completed;

    ulonglong myMissingOffset;
    BitArray* myMap;

    com::pcbsys::foundation::threads::fPocoThreadPool* myThreadPool;

  public:
    fMissingPacketTask(fMulticastReceiverManager* mgr, fBufferManager* bufMgr);

    bool isQueued();

    void close();

    void completed();

    bool queue();

    bool reQueue();

    void run();

    void ThreadPoolCallback(void *pThreadContext);

};
}
}
}
}
}
}
