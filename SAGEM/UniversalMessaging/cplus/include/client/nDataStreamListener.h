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

class nConsumeEvent;

/**
 * Interface used to receive events asynchronously from a data group
 * @since 6.0
 */
class DLL nDataStreamListener {
  public:
    nDataStreamListener(void);
    virtual ~nDataStreamListener(void);
    /**
     * Called when an event has been published to a data group that the client is a member of
     * @param *pEvt an event published for this stream
     */
    virtual void onMessage(nConsumeEvent *pEvt) = 0;
};

}
}
}
}
