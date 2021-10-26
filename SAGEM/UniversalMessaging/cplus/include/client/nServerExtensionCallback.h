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
#include "nEventProperties.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

using namespace com::pcbsys::foundation::fbase;

class nServerExtensionCallback;

/**
 *
 */
class nServerExtensionCallback : public Object {
  public:
    DLL nServerExtensionCallback(void);
    virtual DLL ~nServerExtensionCallback(void);

    /**
     * This method is asynchronously called by the nirvana client API to deliver
     * an event to a registered subscriber.
     *
     * @param *pEvt The nConsumeEvent object specifying the event being delivered.
     */
    virtual DLL void handleEvent(ulonglong  id, unsigned char* data, int length, nEventProperties* props) = 0;

    virtual int getType() {
        return fBase::SERVEREXTENSIONCALLBACK;
    }
};

}
}
}
}
