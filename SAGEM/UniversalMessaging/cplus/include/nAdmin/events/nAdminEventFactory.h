/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEventFactory.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace com::pcbsys::nirvana::nbase::events;

class nAdminEventFactory :
    public nEventFactory {
  public:
    nAdminEventFactory(void);
    virtual ~nAdminEventFactory(void);

    virtual const std::string getName(int id);
    virtual fBaseEvent* getEvent(int id);

    static bool m_sDebug;

    virtual int getType();

  protected:
    virtual nEvent* getObject(int id);
};

}
}
}
}
}
