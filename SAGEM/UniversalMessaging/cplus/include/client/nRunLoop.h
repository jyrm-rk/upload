/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Thread.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nSession;

class nRunLoop : public Poco::Runnable {
  

  public:
    nRunLoop(nSession *pSession);
    nRunLoop(nSession *pSession, nRunLoop* oldLoop);

    void run();
    int getThreadId ();
    void clearSession ();
    void shutdown();
    bool isRunLoopThread();
    bool shutdown(unsigned long time);
    static unsigned long sShutdownWaitTime;
    
  private:
    virtual ~nRunLoop(void);
    nSession *m_pSession;
    Poco::Thread m_ReadThread;
    volatile int m_threadId;
	volatile bool m_bCont;
    nRunLoop* m_pToBeDeletedRunLoop;
};

}
}
}
}
