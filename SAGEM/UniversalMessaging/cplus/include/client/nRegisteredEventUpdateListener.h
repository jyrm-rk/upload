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

/**
 * This interface should be implemented by any object that wishes to register
 * itself as an asynchronous subscriber and only receive update events only from a registered event
 *
 * @see nConsumeEvent
 * @see nChannel
 *
 * @deprecated As of version 6.0 the updates are delivered to the standard nEventListener
 *
 */
class nRegisteredEventUpdateListener :
    public nEventListener {
  public:
    nRegisteredEventUpdateListener(void);
    virtual ~nRegisteredEventUpdateListener(void);

    virtual int getType ();
};

}
}
}
}
