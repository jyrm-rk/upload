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
#include "Poco/SynchronizedObject.h"
#include "Poco/Thread.h"

#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nQueue;
class nChannelAttributes;
class nConsumeEvent;
class nTransactionAttributes;
class nTransaction;
}
namespace nAdminAPI {

class nLeafNode;
class nACL;
class nCommandStatus;
class nRealmNode;

using namespace client;

class nPkgQLeafCopy : public Poco::Runnable {
  public:
    nPkgQLeafCopy(nLeafNode *pSource, const std::string& destQueue, bool bWaitForComplete, nACL *pAcl, nCommandStatus *pCmdStatus);
    nPkgQLeafCopy(nRealmNode *pToRealm, nLeafNode *pSource, const std::string& destQueue, nChannelAttributes *pAttr, bool bWaitForComplete, nACL *pAcl, nCommandStatus *pCmdStatus);
    virtual ~nPkgQLeafCopy(void);

    virtual void run();
    void go(nConsumeEvent *pEvent);

  private:
    static nChannelAttributes* setAttributes(nChannelAttributes *pSrc, nChannelAttributes *pDest);
    void waitForComplete();
    void publishEvents(std::list<nConsumeEvent*>& events);

    nCommandStatus *m_pCommandStatus;
    nLeafNode *m_pSource;
    nChannelAttributes *m_pAttr;
    nChannelAttributes *m_pNewAttr;
    nQueue *m_pSrcQueue;
    nQueue *m_pDestQueue;
    Poco::SynchronizedObject m_waitObject;
    bool m_bAbort;
    std::list<nConsumeEvent*> m_events;
    long m_totalHandled;
    nTransactionAttributes *m_pTXAttrib;
    nTransaction *m_pTx;
    nRealmNode *m_pToRealm;
    Poco::Thread *m_pThread;
    Poco::Mutex m_goMutex;
};

}
}
}
}
