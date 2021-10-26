/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"

#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {

class fConnectionFlushWriteHandler;

class fFlusher : Poco::Runnable {
  public:
    fFlusher(void);
    virtual ~fFlusher(void);

    void shutdown();
    virtual void run ();
    void put(fConnectionFlushWriteHandler *pObj);
    void remove(fConnectionFlushWriteHandler *pObj);
    void closeWhenEmpty();
    int size();

  private:
    std::list<fConnectionFlushWriteHandler*> m_connections;
    Poco::Mutex m_connectionsMutex;
    bool m_bClose;
    bool m_runFlag;
    Poco::Thread *m_pFlushThread;
};

}
}
}
}
