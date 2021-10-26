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

/**
 * This interface should be implemented by classes wishing to register to receive asynchronous notifications from the internal connection queue
 * <p>
 * Such notifications include:
 * <p><KBD>
 *    Reaching high water mark <br>
 *    Reaching low water mark <br>
 *    Exceeding the time it should take to access the queue object <br>
 *    Exceeding the time it should take to push an event onto the queue <br>
 *    Exceeding the time for a queue to be blocked due to reaching its high water mark <br>
 *    </KBD>
 * <p>
 * These limits are configurable under the ClientTimeoutValues section in the Config tab of the Enterprise Manager
 *
 */
class nConnectionQueueListener {
  public:
    DLL nConnectionQueueListener(void);
    virtual DLL ~nConnectionQueueListener(void);

    /**
    * This method is called by the nirvana API to notify a registered connection queue listener that the connection has hit it's low water mark
    *
    * @param lwm the current low water mark setting
    * @param queueSize the current queue size
    */
    virtual DLL void reachedLWM(long lwm, int queueSize) = 0;

    /**
    * This method is called by the nirvana API to notify a registered connection queue listener that the connection has hit it's high water mark
    *
    * @param hwm the current high water mark setting
    * @param queueSize the current queue size
    */
    virtual DLL void reachedHWM(long hwm, int queueSize) = 0;

    /**
    * This method is called by the nirvana API to notify a registered connection queue listener that the connection queue was unable to access the queue for a period longer than that defined by the QueueAccessWaitLimit
    *
    * @param waitTime the amount of time it took to gain access to the queue
    * @param queueSize the current queue size
    * @param eventsTx the amount of events pushed by the connection
    * @param eventsRx the amount of events received by the connection
    */
    virtual DLL void reachedAccessWaitLimit(long waitTime, int queueSize, long eventsTx, long eventsRx) = 0;

    /**
    * This method is called by the nirvana API to notify a registered connection queue listener that the connection queue was unable to push an event to the queue for a period longer than that defined by the QueuePushWaitLimit
    *
    * @param waitTime the amount of time it took to push the event to the queue
    * @param queueSize the current queue size
    * @param eventsTx the amount of events pushed by the connection
    * @param eventsRx the amount of events received by the connection
    */
    virtual DLL void reachedPushWaitLimit(long waitTime, int queueSize, long eventsTx, long eventsRx) = 0;

    /**
    * This method is called by the nirvana API to notify a registered connection queue listener that the connection queue was blocked due to reaching it's high water mark for a period longer than that defined by the QueueBlockLimit
    *
    * @param waitTime the amount of time it took before the queue reached it's low water mark
    * @param queueSize the current queue size
    * @param eventsTx the amount of events pushed by the connection
    * @param eventsRx the amount of events received by the connection
    */
    virtual DLL void reachedQueueBlockLimit(long waitTime, int queueSize, long eventsTx, long eventsRx) = 0;

    /**
    * This method is called by the nirvana API to notify a registered connection queue listener that the connection queue was blocked due to reaching it's high water mark for a period longer than that defined by the QueueBlockLimit but is now unblocked
    *
    * @param waitTime the amount of time it took before the queue was unblocked
    * @param queueSize the current queue size
    * @param eventsTx the amount of events pushed by the connection
    * @param eventsRx the amount of events received by the connection
    */
    virtual DLL void queueUnBlocked(long waitTime, long queueSize, longlong eventsTx, longlong eventsRx) = 0;
};

}
}
}
}

