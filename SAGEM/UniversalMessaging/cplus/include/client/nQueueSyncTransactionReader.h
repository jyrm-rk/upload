/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nQueueSyncReader.h"
#include "nQueueTransactionReader.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nQueue;
class nQueueReaderContext;

/**
 * This reader provides a synchronous queue reader model. Where the client can <code>pop()</code> events from the queue and then decide
 * either to commit the event, i.e. successfully processed it or to rollback, i.e. unable to process this event.
 *
 * When the window size is reached and the client has yet to call commit or rollback the server will raise an exception
 * on the <code>pop()</code> command until the client has called either method.
 */
class nQueueSyncTransactionReader :
    public nQueueSyncReader, public nQueueTransactionReader {
  public:
    virtual ~nQueueSyncTransactionReader(void);

    /**
    * Commits all received events so far.
    *
    * @throws nSessionNotConnectedException Client is not currently connected to the server
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    */
    virtual void commit();

    /**
    * Commits all events up to the event id specified. This means you can partially commit received events.
    *
    * @param eventId Event ID to commit to, inclusive
    * @throws nSessionNotConnectedException Client is not currently connected to the server
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    */
    virtual void commit(longlong eventId);

    /**
    * Rolls back all received events that have not been committed or rolled back previously. These events are then pushed back onto
    * the queue for redelivery.
    *
    * @throws nSessionNotConnectedException Client is not currently connected to the server
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    */
    virtual void rollback();

    /**
    * Rolls back all events up to the specified event id that have not been committed or rolled back previously. These events are then pushed back onto
    * the queue for redelivery.
    *
    * @param eventId Event Id to rollback to, inclusive
    * @throws nSessionNotConnectedException Client is not currently connected to the server
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    */
    virtual void rollback(longlong eventId);

  protected:
    DLL nQueueSyncTransactionReader(nQueue *pQueue, nQueueReaderContext *pContext);

    friend class nQueue;

};

}
}
}
}
