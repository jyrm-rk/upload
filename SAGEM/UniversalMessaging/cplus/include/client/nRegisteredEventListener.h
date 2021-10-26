/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEventListener.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nConsumeEvent;
/**
 * This interface should be implemented by any object that wishes to register
 * itself as an asynchronous subscriber and receive update events and complete merged events from a registered event
 *
 * @see nConsumeEvent
 * @see nChannel
 * @deprecated As of version 6.0 the client merge functionality is depreciated,
 * if you need the full event then this can be done by the nEventProperties merge function.
 *
 */
class nRegisteredEventListener :
    public nEventListener {
  public:
    nRegisteredEventListener(void);
    virtual ~nRegisteredEventListener(void);

    /**
     * This method is asynchronously called by the nirvana client API to deliver
     * an event to a registered subscriber.
     *
     * @param *pEvt The nConsumeEvent object specifying the event being delivered.
     * @deprecated
     */
    virtual void update(nConsumeEvent *pEvt) = 0;
    virtual int getType ();
};

}
}
}
}
