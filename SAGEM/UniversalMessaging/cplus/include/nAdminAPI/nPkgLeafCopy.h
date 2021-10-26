/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEventListener.h"
#include "Observer.h"
#include "fBase.h"
#include "Poco/SynchronizedObject.h"
#include "Poco/Mutex.h"

#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nChannel;
class nChannelAttributes;
class nTransaction;
class nTransactionAttributes;
}
namespace nAdminAPI {

class nRealmNode;
class nLeafNode;
class nACL;
class nCommandStatus;

using namespace client;
using namespace foundation::fbase;

class nPkgLeafCopy :
    public nEventListener, public Observer {
  public:
    nPkgLeafCopy(nRealmNode *pToRealm, nLeafNode *pSource, const std::string destChan, bool waitForComplete, nACL *pAcl, nCommandStatus *pCmdStatus);
    nPkgLeafCopy(nRealmNode *pToRealm, nLeafNode *pSource, const std::string& destChan, nChannelAttributes *pAttr, bool bWaitForComplete, nACL *pAcl, nCommandStatus *pCmdStatus);
    virtual ~nPkgLeafCopy(void);

    virtual int getType();
    virtual void go(nConsumeEvent *pEvent);
    virtual void update(Observable *pNode, void *pObject);

  private:
    static nChannelAttributes* setAttributes(nChannelAttributes *pSrc, nChannelAttributes *pDest);
    void waitForComplete();
    void publishEvents(std::list<nConsumeEvent*>& events);
    void publishPurgedEvents(longlong numEvents);
    void purgeEvents(longlong startEid, longlong endEid);

    nRealmNode *m_pToRealm;
    nCommandStatus *m_pCommandStatus;
    nLeafNode *m_pSource;
    nChannel *m_pSrcChannel;
    nChannel *m_pDestChannel;
    nChannelAttributes *m_pAttr;
    nChannelAttributes *m_pNewAttr;
    longlong m_lastKnownChanEid;
    Poco::SynchronizedObject m_waitObject;
    Poco::Mutex m_goMutex;
    std::list<nConsumeEvent*> m_events;
    longlong m_currentEid;
    longlong m_lastEid;
    longlong m_missedEvents;
    int m_totalPublished;
    longlong m_totalHandled;
    bool m_bAbort;
    nTransactionAttributes *m_pTXAttrib;
    nTransaction *m_pTx;
};

}
}
}
}
