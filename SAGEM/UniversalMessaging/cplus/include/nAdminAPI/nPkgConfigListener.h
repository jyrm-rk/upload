/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nConfigListener.h"
#include "Observer.h"
#include "nPkgCloseListener.h"
#include "fBase.h"
#include <stdlib.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace configuration {
class fConfigObject;
}
}
namespace nirvana {
namespace nAdminAPI {

class nRealmNode;

using namespace com::pcbsys::nirvana::nAdmin;
using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::configuration;

class nPkgConfigListener :
    public nConfigListener, public Observer, public nPkgCloseListener {
  public:
    nPkgConfigListener(nRealmNode *pRealm);
    virtual ~nPkgConfigListener(void);

    virtual void go(const std::list<fConfigObject*>& newConfig);
    virtual void closed(nRealmNode *pClose);
    virtual void update(Observable *pObs, void *pArg);
    virtual int getType();

  private:
    void configUpdate(const std::list<fConfigObject*>& newConfig);

    nRealmNode *m_pRealm;
};

}
}
}
}
