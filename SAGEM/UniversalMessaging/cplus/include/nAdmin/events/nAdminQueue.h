/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fQueueHandler.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fProcessThreadedQueue;
}
}
namespace nirvana {
namespace nbase {
namespace events {
class nEvent;
}
}
namespace nAdmin {

using namespace foundation::fbase;
using namespace nbase::events;

class nAdminEventListener;
class nAdminSession;

class nAdminQueue :
    public fQueueHandler {
  public:
    nAdminQueue(nAdminEventListener *pListener, nAdminSession *pAdminSess);
    virtual ~nAdminQueue(void);
    virtual void processObject(CountableObject *pObject, long queueSize, bool allowClose);
    virtual int getType();
    virtual void reachedLWM();
    virtual void reachedHWM();
    virtual void close();
    virtual void push(nEvent *pEvt);

  private:
    nAdminEventListener *m_pListener;
    nAdminSession *m_pAdmin;
    fProcessThreadedQueue *m_pProcessQ;
};

}
}
}
}
