/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nReconnectHandler.h"
#include "nPkgCloseListener.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

using namespace com::pcbsys::nirvana::client;

class nPkgReconnectHandler :
    public nReconnectHandler, nPkgCloseListener {
  public:
    nPkgReconnectHandler(nRealmNode *pRealm);
    virtual ~nPkgReconnectHandler(void);

    virtual void closed(nRealmNode *pNode);
    virtual void disconnected(nSession *pSession);
    virtual void reconnected(nSession *pSession);
    virtual bool tryAgain(nSession *pSession);

  protected:
    nRealmNode *m_pRealm;
};

}
}
}
}
