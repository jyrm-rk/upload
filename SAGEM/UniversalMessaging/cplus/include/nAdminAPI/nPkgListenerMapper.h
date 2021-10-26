/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nConnectionListener.h"

#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fSubject;
}
}
namespace nirvana {
namespace nAdminAPI {

class nRealmNode;
class nAPIConnectionListener;

using namespace com::pcbsys::nirvana::nAdmin;
using namespace com::pcbsys::foundation::security;

class nPkgListenerMapper :
    public nConnectionListener {
  public:
    nPkgListenerMapper(nRealmNode *pRealm);
    virtual ~nPkgListenerMapper(void);

    virtual void newConnection(const std::string& str, fSubject *pSub, const std::string& unused, const std::string& protocol);
    virtual void delConnection(const std::string& str, bool clientClose);
    void addListener(nAPIConnectionListener *pListener);
    int size();
    void delListener(nAPIConnectionListener *pListener);

  protected:
    nRealmNode *m_pRealm;
    std::list<nAPIConnectionListener*> m_listeners;
};

}
}
}
}
