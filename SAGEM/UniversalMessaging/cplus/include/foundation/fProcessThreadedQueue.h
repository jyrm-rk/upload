/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fProcessQueue.h"
#include "fBase.h"
#include "Poco/Thread.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace collections {
class fQueue;
}
namespace fbase {

using namespace com::pcbsys::foundation::collections;

class fQueueHandler;
class fPump;
class CountableObject;

class fProcessThreadedQueue :
    public fProcessQueue {
  public:
    fProcessThreadedQueue(fQueueHandler *pHandler, fQueue *pQueue, int lowWaterMark, int highWaterMark,
                          const std::string& name = "fProcessThreadedQueue");
    virtual ~fProcessThreadedQueue(void);

    virtual long size();
    virtual void close();
    virtual void push(fBaseEvent *pObject);
    virtual void push(fBaseEvent *pObject, bool notifyImmediatly);
    virtual int length();
    virtual bool isSuspended();

    void run();

  protected:
    void sendEvent(CountableObject *pObject);

  private:
    CountableObject* pop();

    fQueue *m_pQueue;
    fQueueHandler *m_pHandler;
    fPump *m_pPump;
    bool m_bIsOpen;
    bool m_bHasNotified;
    bool m_bSuspended;
	NotifyableCountableObject m_mutex;
    Poco::Thread *m_pThread;
    bool m_bWriteDirect;
};

}
}
}
}
