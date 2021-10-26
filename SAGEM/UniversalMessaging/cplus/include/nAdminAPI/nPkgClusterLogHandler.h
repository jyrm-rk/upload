/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nLogListener.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nRealmNode;

class nPkgClusterLogHandler :
    public nLogListener {
  public:
    nPkgClusterLogHandler(nRealmNode *pNode);
    virtual ~nPkgClusterLogHandler(void);

    virtual void report(const std::string& message);

  private:
    nRealmNode *m_pNode;
};

}
}
}
}
