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
namespace foundation {
namespace io {

class fBaseEvent;
class fEventOutputStream;
class fConnection;
class fOutOfBandEventHandler;

class fBaseEventFactory {
  public:
    DLL fBaseEventFactory(void);
    virtual DLL ~fBaseEventFactory(void);

    virtual fBaseEvent* getEvent(int id) = 0;
    virtual int getEventId(fBaseEvent *pEvent) = 0;
    virtual int getVersion() = 0;

    virtual int getType() = 0;

    int write(fBaseEvent *pEvent, fEventOutputStream *pStream);
    virtual fBaseEvent* getKeepAlive();
    virtual fBaseEvent* getKeepAlive(fConnection *pCon);

    static const int OOB_MULTIPLEX_REQUEST = 120;
    static const int OOB_MULTICAST_REQUEST = 121;
    static const int OOB_MULTICAST_MARKER  = 8;

    static const int NEVENTFACTORY  = 0;
    static const int NADMINEVENTFACTORY  = 1;

    fBaseEvent* read(fConnection* con, fOutOfBandEventHandler** myOOBHandlers, int myOOBHandlersLen);
};

}
}
}
}

