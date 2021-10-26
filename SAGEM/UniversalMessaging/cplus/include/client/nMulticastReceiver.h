/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NMULTICASTRECEIVER_H
#define NMULTICASTRECEIVER_H

#include "fTask.h"
#include "fAsyncReadListener.h"
#include "Poco/Runnable.h"
#include "nDataGroupStreamTransitionManager.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
}
namespace drivers {
namespace multicast {
class fMulticastClient;
}
}
}
namespace nirvana {
namespace nbase {
namespace events {
class nMulticastDetails;
}
}
namespace client {
using namespace com::pcbsys::foundation::drivers;
using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::drivers::multicast;
using namespace com::pcbsys::nirvana::nbase::events;
class nSession;

class nMulticastReceiver : public fTask, public fAsyncReadListener , public Poco::Runnable {

  public:
    nMulticastReceiver(nMulticastDetails* evt, nSession* sess, nDataGroupStreamTransitionManager* manager);

    void dataReady();

    void ThreadPoolCallback(void *threadContext);

    bool reQueue();

    void close();

    short getStreamId();

    void run();

    virtual ~nMulticastReceiver(void);

    /*virtual bool isSynchronous();
    int getRequestId();
    void setRequestId(int id);
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual bool isTypeSynchronous();
    void setSynchronous (bool flag);*/

  private:
    fMulticastClient* myMulticastClient;
    fEventInputStream* myMulticastReceiver;
    short myMulticastStreamId;
    bool queued;
    nSession* mySession;
    nDataGroupStreamTransitionManager* myTransitionManager;
    Poco::Mutex m_lock;


};
}
}
}
}
#endif
