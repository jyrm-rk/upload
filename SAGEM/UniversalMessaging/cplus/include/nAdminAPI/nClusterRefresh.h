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
#include "Poco/Thread.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nRealmNode;


class nClusterRefresh :
    public Poco::Runnable {
  public:
    nClusterRefresh(nRealmNode *pRealm);
    virtual ~nClusterRefresh(void);

    virtual void run();

  private:
    nRealmNode *m_pRealm;
    Poco::Thread *m_pThread;
};

}
}
}
}
