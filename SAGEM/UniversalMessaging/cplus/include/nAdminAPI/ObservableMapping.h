/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Observer.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

using namespace com::pcbsys::foundation::fbase;

class nConnectionDetails;

class ObservableMapping :
    public Observer {
  public:
    ObservableMapping(nConnectionDetails *pDet);
    virtual ~ObservableMapping(void);

    virtual void update(Observable *pObs, void *pObj);

  private:
    nConnectionDetails *m_pDetails;
};

}
}
}
}
