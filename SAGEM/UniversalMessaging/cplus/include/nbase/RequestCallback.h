/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nRequestCallback.h"

namespace Poco {

class Timer;

}

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {
class nEvent;
}

using namespace events;

class Reconnect;

class RequestCallback :
    public nRequestCallback {
  public:
    RequestCallback(Reconnect *pRecon);
    virtual ~RequestCallback(void);

    void response(nEvent *pRequest, nEvent *pResponse);

  private:
    void onTimer (Poco::Timer &timer);

    Reconnect *m_pRecon;
    Poco::Timer *m_pTimer;
};

}
}
}
}
