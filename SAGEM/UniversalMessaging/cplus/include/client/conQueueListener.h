/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fConnectionQueueListener.h"
#include "nConnectionQueueListener.h"
#include "nSession.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

using namespace com::pcbsys::foundation::io;

class conQueueListener :
    public fConnectionQueueListener {
  public:
    conQueueListener(nSession *pSession, nConnectionQueueListener *pQlistener);
    virtual ~conQueueListener(void);

    virtual void reachedLWM(long lwm, int queueSize);
    virtual void reachedHWM(long hwm, int queueSize);
    virtual void reachedAccessWaitLimit(long waitTime, int queueSize, long eventsTx, long eventsRx);
    virtual void reachedPushWaitLimit(long waitTime, int queueSize, long eventsTx, long eventsRx);
    virtual void reachedQueueBlockLimit(long waitTime, int queueSize, long eventsTx, long eventsRx);
    virtual void queueUnBlocked(long waitTime, long queueSize, longlong eventsTx, longlong eventsRx);

    nConnectionQueueListener *m_pQueueListener;
    nSession *m_pSession;
};

}
}
}
}

