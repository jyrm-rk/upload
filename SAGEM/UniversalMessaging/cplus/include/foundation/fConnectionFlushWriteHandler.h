/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fConnectionWriteHandler.h"
#include "Poco/Mutex.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {

class fFlusher;

class fConnectionFlushWriteHandler :
    public fConnectionWriteHandler {
  public:
    fConnectionFlushWriteHandler(fConnection *pConnection);
    virtual ~fConnectionFlushWriteHandler(void);

    static long s_maxTimeBetweenFlushes;
    static void shutdown();

    long m_nextFlush;

    virtual void run();
    virtual void processObject(CountableObject *pObj, long queueSize, bool allowClose);
    virtual bool directWriteEnabled();
    virtual void close();

  protected:
    static fFlusher* allocateFlusher();

    fFlusher *m_pFlusher;
    static Poco::Mutex m_mutex;

    static fFlusher** m_pFlushers;
    static int m_nFlusher;
};

}
}
}
}
