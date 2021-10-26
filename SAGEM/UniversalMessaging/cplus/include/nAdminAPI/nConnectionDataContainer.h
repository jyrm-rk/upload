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
#include "Observable.h"
#include "nPkgCloseListener.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nConnectionStatus;
}
namespace nAdminAPI {

class nRealmNode;
class nNode;

using namespace foundation::fbase;
using namespace nbase;


/*
 * This class contains the details about an individual connection. It is observable
 * to allow a user program to be informed about changes to the statistics of the connection.
 *
 */
class nConnectionDataContainer :
    public Observable, public nPkgCloseListener {
  public:
    nConnectionDataContainer(std::string id, std::string* subject, int nSubject, std::string protocol, nRealmNode *pRealm);
    virtual ~nConnectionDataContainer(void);

    /**
     * Called when the nRealmNode is closed, for internal use only.
     *
     * @param node The nRealmNode which has been closed.
     */
    virtual void closed(nRealmNode *pNode);

  protected:
    virtual void update(nConnectionStatus *pCs);

    std::string m_id;
    std::string* m_pSubjects;
    int m_nSubject;
    std::string m_protocol;
    nRealmNode *m_pRealm;
    std::map<std::string, nNode*> m_users;
    bool m_bWasClosedByClient;
    longlong m_eventTx;
    longlong m_eventRx;
    longlong m_byteTx;
    longlong m_byteRx;
    longlong m_lastTxTime;
    longlong m_lastRxTime;
    int m_queueSize;
    longlong m_upTime;
    int m_latency;
    std::string m_lastTxEvent;
    std::string m_lastRxEvent;

    friend class nConnectionDetails;
    friend class nPkgReconnectHandler;
    friend class nPkgStatusListener;
    friend class nServiceNode;
    friend class nChannelListener;
    friend class nPkgListenerMapper;
    friend class ClusterNodeConnectionListener;
    friend class ConnectionStatusHandler;
};

}
}
}
}
