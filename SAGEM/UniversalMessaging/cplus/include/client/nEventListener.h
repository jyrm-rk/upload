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
namespace client {

using namespace com::pcbsys::foundation::fbase;

class nConsumeEvent;

/**
 * This interface should be implemented by any object that wishes to register
 * itself as an asynchronous subscriber to a nirvana channel or queue
 *
 * @see nConsumeEvent
 * @see nChannel
 * @see nQueue
 *
 */
class nEventListener : public Object {
  public:
    DLL nEventListener(void);
    virtual DLL ~nEventListener(void);

    /**
     * This method is asynchronously called by the nirvana client API to deliver
     * an event to a registered subscriber.
     *
     * @param *pEvt The nConsumeEvent object specifying the event being delivered.
     */
    virtual DLL void go(nConsumeEvent *pEvt) = 0;

    virtual int getType() {
        return fBase::EVENTLISTENER;
    }
};

}
}
}
}
