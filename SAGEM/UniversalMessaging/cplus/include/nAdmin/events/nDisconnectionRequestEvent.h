/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEvent.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace nbase::events;
using namespace foundation::io;

class nDisconnectionRequestEvent :
    public nEvent {
  public:
    nDisconnectionRequestEvent(void);
    nDisconnectionRequestEvent(const std::string& aconnectionID, bool redirect, bool reset);
    virtual ~nDisconnectionRequestEvent(void);

    virtual void performRead(fEventInputStream *pOis);
    virtual void performWrite(fEventOutputStream *pOos);
    virtual const std::string getTypeString();
    virtual nEvent* createInstance();
    virtual int getType();

  private:
    std::string m_connectionID;
    bool m_bSendRedirect;
    bool m_bSendReset;
};

}
}
}
}
}
