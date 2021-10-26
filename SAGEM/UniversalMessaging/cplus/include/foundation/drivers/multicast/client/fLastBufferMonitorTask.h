/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FLASTBUFFERMONITORTASK_H
#define FLASTBUFFERMONITORTASK_H

#include <fScheduledTask.h>
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fScheduledTask;
}
namespace drivers {
namespace configuration {
class fMulticastConfig;
}
namespace multicast {
namespace client {
class fBufferManager;
class fMulticastReceiverManager;
class fMissingPacketTask;
using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::drivers::configuration;
class fLastBufferMonitorTask : public fScheduledTask , public Poco::Mutex {

  private:
    longlong myAck;
    bool isQueued;
    long myTimer;
    long forceAckCount;
    fBufferManager* myBuffers;
    fMulticastReceiverManager* myManager;
    fMissingPacketTask* myMissingPacketTask;
    fMulticastConfig* myConfig;


  public:
    fLastBufferMonitorTask(fMulticastReceiverManager* mgr, fBufferManager* bufMgr, fMissingPacketTask* missingtask, fMulticastConfig* config);

    void close();

    void checkAck();

    bool sendAck();
    bool sendAck(bool flag);

    long reSchedule();

    void execute();
};
}
}
}
}
}
}

#endif
