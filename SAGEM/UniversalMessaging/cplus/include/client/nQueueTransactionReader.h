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
 * Provides the basic interface for transactional queue operations, used by the synchronous and asynchronous transactional queue readers.
 */
class nQueueTransactionReader {
  public:
    virtual ~nQueueTransactionReader(void);

    /**
    * Commits all received events so far.
    *
    * @throws nSessionNotConnectedException Client is not currently connected to the server
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    * @throws nRequestTimedOutException The server failed to respond with the specified timeout
    */
    virtual void commit() = 0;

    /**
    * Commits all events up to the event id specified. This means you can partially commit received events.
    *
    * @param eventId Event ID to commit to, inclusive
    * @throws nSessionNotConnectedException Client is not currently connected to the server
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    * @throws nRequestTimedOutException The server failed to respond with the specified timeout
    */
    virtual void commit(longlong eventId) = 0;

    /**
    * Rolls back all received events that have not been committed or rolled back previously. These events are then pushed back onto
    * the queue for redelivery.
    *
    * @throws nSessionNotConnectedException Client is not currently connected to the server
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    * @throws nRequestTimedOutException The server failed to respond with the specified timeout
    */
    virtual void rollback() = 0;

    /**
    * Rolls back all events up to the specified event id that have not been committed or rolled back previously. These events are then pushed back onto
    * the queue for redelivery.
    *
    * @param eventId Event Id to rollback to, inclusive
    * @throws nSessionNotConnectedException Client is not currently connected to the server
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    * @throws nRequestTimedOutException The server failed to respond with the specified timeout
    */
    virtual void rollback(longlong eventId) = 0;

  protected:
    DLL nQueueTransactionReader(void);

    friend class nQueue;
};

}
}
}
}
