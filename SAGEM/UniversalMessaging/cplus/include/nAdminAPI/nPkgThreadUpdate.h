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
#include "nPkgCloseListener.h"

#include "Poco/Mutex.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadPool.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nSecureRealm;
}
namespace client {
class nRealm;
}
namespace nAdminAPI {

class nRealmNode;

using namespace foundation::fbase;
using namespace nbase;
using namespace client;

class nPkgThreadUpdate :
    public fTask, public nPkgCloseListener, public Poco::Runnable {
  public:
    nPkgThreadUpdate(nRealmNode *pRealmNode, nSecureRealm *pRealm);
    virtual ~nPkgThreadUpdate(void);

    virtual void run();
    virtual bool reQueue();
    virtual void closed(nRealmNode *pNode);

    static bool haveAllCompleted();

  private:
    virtual void ThreadPoolCallback(void *pThreadContext);
    void process();
    void close();
    std::string* constructSessionURL(nSecureRealm* pRealm, int &length);

    nRealm *m_pBRealm;
    nRealmNode *m_pRealm;
    nRealmNode *m_pWorkingRealm;

    bool bConnected;

    static Poco::Mutex m_lock;
    static int m_activeCount;
    static Poco::ThreadPool *m_pThreadPool;
	static Poco::Mutex m_ThreadPoollock;
};

}
}
}
}
