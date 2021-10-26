/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fTask.h"

#include "fPocoThreadPool.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace collections {
class Queue;
}
}
namespace nirvana {
namespace nbase {
namespace events {
class nEvent;
}

class nDataGroupCallback;

using namespace nbase::events;
using namespace foundation::fbase;
using namespace foundation::collections;

class nDataGroupEventPump : public fTask, public Poco::Runnable {
  public:
    nDataGroupEventPump(nDataGroupCallback *pCallback);
    virtual ~nDataGroupEventPump(void);

    virtual void run();
    int size();
    void pushEvent(nEvent *pEvt);
    virtual void ThreadPoolCallback(void *pThreadContext);
    bool reQueue();
    void pause();
    bool isPaused();
    void resume();

    void close();

    static int sMaxQueueSize;

  private:
    Queue *m_pQueue;		// In the dotnet version, this uses a system class (as does Queue now)
    bool m_bQueued;
    nDataGroupCallback *m_pCallback;

    com::pcbsys::foundation::threads::fPocoThreadPool *m_pThreadPool;

    bool m_bBlocked;
    bool m_bPaused;
};

}
}
}
}
