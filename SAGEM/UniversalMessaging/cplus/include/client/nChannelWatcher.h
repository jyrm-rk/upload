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
#include "nEventListener.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

using namespace com::pcbsys::foundation::fbase;

class nConsumeEvent;
class nEventListener;

/**
 * This interface extends the nEventListener interface and also provides the ability to receive callbacks
 * for purged events as well as events published on a specific channel or queue.
 *
 * The purge callback is called when an event has been purged from the channel or queue.
 */

class nChannelWatcher : public nEventListener {
  public:
    DLL nChannelWatcher(void);
    virtual DLL ~nChannelWatcher(void);

    /**
     * This method is called when events are purged from the channel or queue
     *
     * @param startEID The starting range of the purge event
     * @param endEID The ending range of the purge event
     * @param filter A filter if supplied
     */
    virtual DLL void purge(longlong startEID, longlong endEID, std::string& filter) = 0;
    virtual int getType() = 0;
};

}
}
}
}
