/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fQueueHandler.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {

class fConnection;

using namespace fbase;

class fConnectionWriteHandler :
    public fQueueHandler {
  public:
    fConnectionWriteHandler(fConnection *pConnection);
    virtual ~fConnectionWriteHandler(void);
    virtual int getType();
    virtual void processObject(CountableObject *pObject, long queueSize, bool allowClose) = 0;
    void close();
    virtual void reachedLWM();
    virtual void reachedHWM();
    virtual bool directWriteEnabled();

  protected:
    fConnection *m_pConnection;

  private:
};

}
}
}
}
