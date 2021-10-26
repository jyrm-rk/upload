/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "MergeManager.h"
#include "Poco/Runnable.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nRealmNode;

using namespace com::pcbsys::foundation::collections;

class nPkgValidateNamespace :
    public MergeManager, public Poco::Runnable {
  public:
    nPkgValidateNamespace(nRealmNode *pRealm);
    virtual ~nPkgValidateNamespace(void);

    virtual void deleted(Object *pObj);
    virtual void added(Object *pObj);
    virtual void merge(Object *pOriginal, Object *pNewObj);
    virtual void run();

  private:
    nRealmNode *m_pRealm;
};

}
}
}
}
