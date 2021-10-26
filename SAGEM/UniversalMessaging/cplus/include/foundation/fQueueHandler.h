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
namespace fbase {

class fQueueHandler : public CountableObject {
  public:
    fQueueHandler(void);
    virtual ~fQueueHandler(void);

    virtual void processObject(CountableObject *pObject, long queueSize, bool allowClose) = 0;
    virtual int getType() = 0;
    virtual void reachedLWM() = 0;
    virtual void reachedHWM() = 0;

    static const int CONNECTION = 1000;
    static const int CONNECTIONWRITEHANDLER = 1001;
    static const int ADMINQUEUE = 1002;
};

}
}
}
}

