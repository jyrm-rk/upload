/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {

class fConnectionQueueListener {
  public:
    DLL fConnectionQueueListener(void);
    virtual DLL ~fConnectionQueueListener(void);

    virtual void reachedLWM(long lwm, int queueSize) = 0;
    virtual void reachedHWM(long hwm, int queueSize) = 0;
    virtual void reachedQueueBlockLimit(long waitTime, int queueSize, long eventsTx, long eventsRx) = 0;
    virtual void reachedAccessWaitLimit(long waitTime, int queueSize, long eventsTx, long eventsRx) = 0;
    virtual void reachedPushWaitLimit(long waitTime, int queueSize, long eventsTx, long eventsRx) = 0;
    virtual void queueUnBlocked(long waitTime, long queueSize, longlong eventsTx, longlong eventsRx) = 0;
};

}
}
}
}
