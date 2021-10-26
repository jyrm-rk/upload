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
using namespace foundation::fbase;

/**
 * Provides a context when peeking on the queue.
 * Useful when multiple calls are required to traverse the entire queue.
 */
class nQueuePeekContext : public CountableObject {
  public:

    /**
    * Creates a queue peek context with the specified window size and message
    * selector to filter events with.
    *
    * @param windowSize Number of events which will be delivered to the client per lookup
    * @param selector Message selector to apply to the events
    */

    DLL nQueuePeekContext(int windowSize = 0, const std::string selector = "");

    virtual ~nQueuePeekContext(void);

    /**
    * Returns a boolean indicating if there are any more events in the queue.
    * @return true if more
    */

    DLL bool hasMore();

    /**
    * Returns the index into the queue that the context is up to.
    *
    * @return current index
    */

    DLL int getIndex();

    /**
    * @param idx Index value to set
    */

    DLL void setIndex(int idx);

    /**
    * Retrieves the size of the window used by this queue peek context.
    *
    * @return The size of the window
    */

    DLL int getWindowSize();

    /**
    * Sets the size of the window.
    *
    * @param size A size greater than 0
    */

    DLL void setWindowSize(int size);

    /**
    * Sets the flag to true if more events in the queue. (Server specific).
    *
    * @param flag to specify whether there are more events to come
    */

    DLL void setHasMore(bool flag);

    /**
    * Retrieves the message selector (if any) set to filter events on this peek context.
    *
    * @return the selector used by this context
    */

    DLL const std::string getSelector();

  private:
    const std::string m_filter;
    int m_currentIdx;
    bool m_bHasMore;
    int m_windowSize;
};

}
}
}
}
