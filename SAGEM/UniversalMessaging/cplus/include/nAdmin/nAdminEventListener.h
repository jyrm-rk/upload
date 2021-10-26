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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {
class nEvent;
}
}
namespace nAdmin {

using namespace com::pcbsys::nirvana::nbase::events;
using namespace com::pcbsys::foundation::fbase;

class nAdminEventListener : public Countable {
  public:
    nAdminEventListener(void);
    virtual ~nAdminEventListener(void);

    virtual void adminEvent(nEvent *pEvt) = 0;
};

}
}
}
}
